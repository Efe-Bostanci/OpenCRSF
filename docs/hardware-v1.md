# V1 hardware

V1 is the first working OpenCRSF hardware revision.

The V1 electrical schematic supplied for this project is titled **OpenCRSF (CRSF to PWM converter)**, revision **1.0**, dated **2026-07-11**.

## Electrical design

The V1 schematic is built around an **ESP32-C3 SuperMini** and provides six 3-pin PWM/servo connectors:

- CH1
- CH2
- CH3
- CH4
- CH5
- CH6

The schematic also includes an ELRS receiver connector with:

- 5V
- TX
- RX
- GND

The ESP32-C3 is powered from the 5V / 3.3V arrangement shown in the original schematic.

## Indicators and headers

The V1 schematic contains:

- green LED indicator
- blue LED indicator
- LED resistors
- 100 nF decoupling capacitor
- 10 uF capacitor
- 1x5 2 mm SMD header exposing GPIO / 3.3 V connections

The six PWM channels are associated with ESP32-C3 GPIOs 0, 1, 2, 3, 4 and 5 in the schematic.

## Important revision boundary

This page describes **V1 only**.

Do not use the V2 power/protection component list as a description of this hardware. V2 is a separate redesign of the power/protection section.

The firmware currently in the repository is the V1 firmware and is also intended for V2.

## Source files

The original V1 schematic and board/render files were supplied during development. The repository documentation is intentionally based on those actual design files rather than a simplified replacement drawing.

When the original EasyEDA project/source assets are available in repository-compatible form, they should be stored alongside this documentation so the design can be edited directly.
