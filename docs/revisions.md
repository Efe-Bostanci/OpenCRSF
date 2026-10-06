# Hardware revisions

This page exists to prevent V1 and V2 information from being mixed.

## V1

**Status:** Built and tested

V1 was the first functional OpenCRSF prototype.

It proved that an ESP32-C3 could receive CRSF data from an ELRS receiver and provide six PWM outputs for the RC system.

The prototype was assembled on perfboard and successfully controlled six servos and a motor.

A later power test damaged the ELRS receiver. That failure exposed weaknesses in the power architecture and led directly to the V2 redesign.

## V2

**Status:** Hardware in development

V2 keeps the same basic CRSF-to-PWM application concept but redesigns the power and protection section.

The main objective is to keep the high-current servo path from directly exposing the ESP32 and ELRS receiver to the same power faults.

The current V2 design includes:

- shared VBUS for servo connectors
- PTC protection
- bidirectional TVS protection
- bulk capacitance
- P-channel MOSFET isolation on the electronics branch
- additional protection and USB backfeed isolation
- separate SYS_5V electronics rail

The actual electrical schematic should be used for final component-level interpretation.

## V3

**Status:** Planned

V3 is intended to introduce a dedicated buck regulator for the electronics rail.

## Firmware relationship

The firmware revision is intentionally independent from the hardware revision.

Current state:

```text
V1 hardware ──┐
              ├── V1 firmware
V2 hardware ──┘
```

The V2 power redesign does not require a different CRSF-to-PWM application architecture.
