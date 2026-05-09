# Universal-Parachute-Ejection-Timer-Avionics-Build
This repository contains the code, the electical schematics as well as some Layout exemples of an universal parachute ejection timer module for rockets avionics.
The module is made to work with arduino uno, nano, mini pro 3v3 and 5v.

## General requirements :
This setup is made to use :
- An arduino board
- 3 leds (red, yellow, green)
- A buzzer
- A servo
- An alimentation jack
- A MP1584EN Buck convertor
- Various resistances of different values

When the board is powered up and the jack connected, the  green led turns on solid, servo rotates in position 1 and buzzer blinks slowly.
When the jack is disconected, detecting launch, yellow led and buzzer stats to blink fast, green led off and timer start.
At the end of the timer, all three leds and buzzer turns solid, servo rotates in position 1.
If the jack is reconected, the process restarts, green led solid, servo position 1, timer reset and buzzer on slow blink.


## Files :

```text


|
├── Layout exemples/
|  ├── Rectangular/
|  |  ├── Layout.pdf
|  |  ├── Layout.json
|  |  ├── Layout.pcbdoc
|  |  └── Layout_rectangular_gerber.zip
|  └── Round/
|    ├── Layout.pdf
|    ├── Layout.json
|    ├── Layout.pcbdoc
|    └── Layout_round_gerber.zip
├── Schematic/
|  ├── Schematic.pdf
|  ├── Schematic.json
|  └── Schematic.schdoc
├── README.md
└── Sequenceur_Universel.ino

```
### Files types
- **PDF** : meant for quick visualization
- **json** : to be used with EasyEDA PCB editor
- **SCHDOC** : to be used with Altium Designer

