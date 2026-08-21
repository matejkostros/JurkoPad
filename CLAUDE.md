# MacroNumpad

20-key handwired numpad (5 rows x 4 cols) with Cherry MX 1U switches, soldered to Waveshare RP2040 Zero. ROW2COL wiring with 1N4148 diodes. QMK firmware with Vial support. Builds on Fedora Linux.

## Quick Start

1. Install dependencies: `sudo dnf install make python3 git arm-none-eabi-gcc arm-none-eabi-newlib`
2. Run build script: `./build.sh`
3. Enter bootloader (hold BOOT, replug USB), then flash when prompted
4. Open https://usevia.app to configure layers

See README.md for detailed soldering, firmware setup, and troubleshooting.

## Hardware

- **Microcontroller**: Waveshare RP2040 Zero
- **Switches**: 20x Cherry MX 1U (5 rows x 4 cols)
- **Matrix**: 5 rows x 4 cols, ROW2COL wiring
- **Diodes**: 20x 1N4148 diodes (one per switch, cathode to column)
- **Bootloader**: Tap BOOT button during replug to enter UF2 bootloader

## Firmware Layout

**Layer 0** (default on boot): Standard numpad layout
```
[Num Lock]  [Calc]      [Fn]        [/]
[7 Home]    [8 ↑]       [9 PgUp]    [*]
[4 ←]       [5]         [6 →]       [-]
[1 End]     [2 ↓]       [3 PgDn]    [+]
[0 Ins]     [,]         [. Del]     [Enter]
```

**Layer 10** (momentary when Fn held): Layer selector
- Keys 0-9 lock to Layers 0-9 respectively
- Fn available on all layers to access selector

**Layers 1-9**: User-configurable via Vial UI (no JSON needed)

## Build System

**build.sh** - One-command build and flash:
- Checks for required tools (git, python3, make, arm-none-eabi-gcc)
- Clones/updates vial-qmk (first run only)
- Installs QMK Python dependencies
- Copies firmware config from `firmware/` to vial-qmk
- Compiles macropad:vial target
- Prompts for automatic flashing to RPI-RP2 mount

**Firmware Directory Structure**:
- `firmware/config.h` - Matrix pins, debounce, features
- `firmware/keymap.c` - Layer definitions and key mappings
- `firmware/rules.mk` - Build flags (leave empty, inherits from vial-qmk)
- `firmware/info.json` - Keyboard metadata (unused, vial.json used instead)

**Vial Configuration** (firmware/keymaps/vial/):
- `vial.json` - Matrix layout only (minimal, allows web config)
- `config.h` - Vial UID and unlock combo
- `keymap.c` - Default layer 0 definition

## Environment (Fedora)

Install build chain: `sudo dnf install make python3 git arm-none-eabi-gcc arm-none-eabi-newlib`

Verify: `make --version && python3 --version && arm-none-eabi-gcc --version`

QMK dependencies installed automatically by build.sh via pip.

## Flashing Workflow

1. Hold BOOT on RP2040 Zero
2. Plug USB into computer (while holding BOOT)
3. 'RPI-RP2' drive appears (UF2 bootloader)
4. build.sh detects mount and copies .uf2 automatically (or manually to RPI-RP2 drive)
5. Device reboots as Vial keyboard

Troubleshooting: If RPI-RP2 not detected, manually copy `macropad.uf2` to the drive.

## Vial Configuration

No JSON import needed. Vial auto-detects via vial.json matrix definition:
1. Open https://usevia.app in browser
2. Authorize device when prompted
3. Edit Layers 0-9 directly in web UI
4. Changes saved to keyboard non-volatile storage
