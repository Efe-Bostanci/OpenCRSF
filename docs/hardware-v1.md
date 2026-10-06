# V1 hardware

V1 is the first working OpenCRSF hardware revision.

## Original electrical schematic

The original EasyEDA schematic is included directly in the repository:

[OpenCRSF V1 schematic — SVG](../hardware/v1/Schematic_OpenCRSF_2026-10-07.svg)

The schematic title is **OpenCRSF (CRSF to PWM converter)**, revision **1.0**, dated **2026-07-11**.

This is the original schematic export. It is not a recreated or simplified drawing.

## Circuit

The V1 schematic is built around an **ESP32-C3 SuperMini** and includes six PWM output channels:

- CH1
- CH2
- CH3
- CH4
- CH5
- CH6

It also includes an ELRS receiver interface, indicator LEDs, decoupling/bulk capacitors and a 1x5 2 mm SMD header.

The schematic contains the GPIO/net labels used by the original design. The exact electrical connections should be read from the source schematic above rather than inferred from a simplified block diagram.

## Revision boundary

This page describes **V1 only**.

V2 is a separate hardware revision with a redesigned power/protection section. V1 and V2 component lists must not be mixed.

The firmware currently in the repository is the V1 firmware and is also intended for V2.

## Source assets

The repository contains the original V1 schematic export in SVG format. The SVG is the actual schematic export from the project and is linked above.
