#include <Arduino.h>
#include "config.h"
#include "crsf.h"
#include "servo.h"
#include "failsafe.h"

static CrsfParser  g_crsf;
static ServoManager g_servo;
static FailsafeManager g_failsafe;

static constexpr uint32_t DIAG_SERIAL_BAUD = 115200;
static constexpr uint32_t DIAG_PRINT_INTERVAL_MS = 2000;
static uint32_t g_lastDiagMs = 0;

static void applyLiveChannels();
static void applyFailsafeChannels();
static void printDiagnostics();

void setup()
{
    Serial.begin(DIAG_SERIAL_BAUD);

    const uint32_t bootStart = millis();
    while (!Serial && (millis() - bootStart < 1500u)) {
        yield();
    }

    Serial.println(F(""));
    Serial.println(F("╔══════════════════════════════╗"));
    Serial.println(F("║       OpenCRSF v1.0.0        ║"));
    Serial.println(F("║  CRSF → PWM  ESP32-C3        ║"));
    Serial.println(F("╚══════════════════════════════╝"));
    Serial.printf(
        "  CRSF UART : GPIO%d (RX) / GPIO%d (TX) @ %lu baud\r\n",
        PIN_CRSF_RX,
        PIN_CRSF_TX,
        (unsigned long)CRSF_BAUD
    );
    Serial.printf(
        "  Servo CH  : %d channels @ %d Hz\r\n",
        SERVO_CHANNEL_COUNT,
        SERVO_FREQ_HZ
    );
    Serial.printf(
        "  Failsafe  : %d ms timeout\r\n",
        CRSF_TIMEOUT_MS
    );
    Serial.println(F(""));

    g_failsafe.begin();
    g_servo.begin();
    g_crsf.begin();

    g_lastDiagMs = millis();

    Serial.println(F("[OpenCRSF] Boot complete — waiting for receiver..."));
}

void loop()
{
    g_crsf.update();

    if (g_crsf.hasNewFrame()) {
        g_failsafe.onFrameReceived();
        applyLiveChannels();
    }

    g_failsafe.update();

    if (g_failsafe.isFailsafe() || g_failsafe.isNoSignal()) {
        applyFailsafeChannels();
    }

    if ((millis() - g_lastDiagMs) >= DIAG_PRINT_INTERVAL_MS) {
        g_lastDiagMs = millis();
        printDiagnostics();
    }
}

static void applyLiveChannels()
{
    for (uint8_t i = 0; i < SERVO_CHANNEL_COUNT; ++i) {
        const uint8_t crsfCh = CHANNEL_MAP[i];
        const uint16_t us = g_crsf.getChannelUs(crsfCh);
        g_servo.setChannel(i, us);
    }
}

static void applyFailsafeChannels()
{
    for (uint8_t i = 0; i < SERVO_CHANNEL_COUNT; ++i) {
        const uint16_t us = (i == 2u)
            ? FailsafeManager::failsafeThrottleUs()
            : FailsafeManager::failsafeSteeringUs();

        g_servo.setChannel(i, us);
    }
}

static void printDiagnostics()
{
    const char* stateStr = "UNKNOWN";

    switch (g_failsafe.linkState()) {
        case LinkState::NO_SIGNAL:
            stateStr = "NO_SIGNAL";
            break;
        case LinkState::CONNECTED:
            stateStr = "CONNECTED";
            break;
        case LinkState::FAILSAFE:
            stateStr = "FAILSAFE";
            break;
    }

    Serial.printf(
        "[Diag] State=%-10s | Frames=%lu | CRCerr=%lu | LostMs=%lu\r\n",
        stateStr,
        (unsigned long)g_crsf.frameCount(),
        (unsigned long)g_crsf.crcErrorCount(),
        (unsigned long)g_crsf.msSinceLastFrame()
    );

    Serial.print(F("       Servos: "));

    for (uint8_t i = 0; i < SERVO_CHANNEL_COUNT; ++i) {
        Serial.printf("CH%d=%4uus", i + 1, g_servo.getChannel(i));

        if (i < SERVO_CHANNEL_COUNT - 1u) {
            Serial.print(F("  "));
        }
    }

    Serial.println();
}
