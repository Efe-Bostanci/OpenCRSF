# Hardware

OpenCRSF has two hardware revisions that must be considered separately.

## V1

V1 is the first working prototype.

It demonstrated the core concept:

- ELRS receiver input
- ESP32-C3 processing
- six PWM outputs
- servo control
- ESC control

The V1 power section used:

- PTC fuse
- TVS diode
- bulk capacitors

The main limitation identified during testing was insufficient isolation of the sensitive electronics from the high-current power path.

## V2

V2 is a redesign of the power and protection section.

The current design separates the shared servo power path from the protected electronics branch.

Known V2 elements:

| Reference | Part / function |
|---|---|
| VBUS | Shared servo power bus |
| F1 | PTC protection |
| D1 | P6KE6.8CA bidirectional TVS |
| Q1 | AO3401A P-channel MOSFET |
| F2 | Additional protection |
| D2 | Additional protection / USB backfeed isolation |
| SYS_5V | Protected electronics rail |

The V2 schematic should be read from the actual EasyEDA project. This document does not replace the schematic.

## V3

V3 is planned to use a dedicated buck regulator for the electronics rail.

The objective is to reduce the dependency of the ESP32 and ELRS receiver on the external BEC's regulation quality.

## Important

Do not merge V1 and V2 component lists.

V1 describes the hardware that was actually built and tested.

V2 describes the redesigned power/protection architecture.

The firmware is shared between these revisions unless a later firmware change is explicitly documented.
