# MacroNumpad Build Guide

Custom Numpad with 1U Cherry MX mechanical switches, handwired and soldered to a Waveshare RP2040 Zero microcontroller. QMK firmware with Vial support for online reprogramming.

## Layout

```
[Num Lock]  [Calc]      [Fn]        [/]
[7 Home]    [8 ↑]       [9 PgUp]    [*]
[4 ←]       [5]         [6 →]       [-]
[1 End]     [2 ↓]       [3 PgDn]    [+]
[0 Ins]     [,]         [. Del]     [Enter]
```

## Wiring Diagram (ROW2COL)

**RP2040 Zero Pinout** (viewing from top, USB on right):

```
    Row pins (right side): GPIO29, GPIO28, GPIO27, GPIO26, GPIO15
    Col pins (bottom): GPIO10, GPIO11, GPIO12, GPIO13
```

**Switch Matrix Layout** (5 rows x 4 cols):

```
                    Columns
              GPIO10 GPIO11 GPIO12 GPIO13
              (Col0) (Col1) (Col2) (Col3)
                |      |      |      |
                |      |      |      |
GPIO3 (Row0):  SW0-[|||]-SW1-[|||]-SW2-[|||]-SW3-[|||]
                |      |      |      |
GPIO4 (Row1):  SW4-[|||]-SW5-[|||]-SW6-[|||]-SW7-[|||]
                |      |      |      |
GPIO5 (Row2):  SW8-[|||]-SW9-[|||]-SW10-[|||]-SW11-[|||]
                |      |      |      |
GPIO6 (Row3):  SW12-[|||]-SW13-[|||]-SW14-[|||]-SW15-[|||]
                |      |      |      |
GPIO7 (Row4):  SW16-[|||]-SW17-[|||]-SW18-[|||]-SW19-[|||]

[|||] = 1N4148 diode cathode (-/stripe) toward row, anode toward col
```

**Physical Wiring** (what you already soldered):

```
Column (yellow) ---[Switch]---[Diode|||]--- Row (black)
                       pin1    cathode→     connected
                       pin2                  to GPIO

Flow: Row driven → Switch closes → Diode conducts → Column reads input
Diode blocks backward current (prevents ghosting)
```

## Hardware Assembly

Your handwiring is already correct. Rows and columns are soldered, diodes oriented properly (cathode/stripe toward black row cables).

Now connect to RP2040 Zero:

**Row connections (black cables):**
- Row 0 → GPIO29
- Row 1 → GPIO28
- Row 2 → GPIO27
- Row 3 → GPIO26
- Row 4 → GPIO15

**Column connections (yellow cables):**
- Column 0 → GPIO10
- Column 1 → GPIO11
- Column 2 → GPIO12
- Column 3 → GPIO13

**Power and Ground:**
- Any GND pin on RP2040 → GND reference for your matrix (optional but recommended)

## Build Process

### Prerequisites (Fedora)

```bash
sudo dnf install make python3 git arm-none-eabi-gcc arm-none-eabi-newlib
```

Verify:

```bash
make --version && python3 --version && arm-none-eabi-gcc --version
```

### Step 1: Generate Firmware Config

Edit `firmware/config.h` with your pin mappings (already pre-configured in the script):

```c
#define MATRIX_ROWS 5
#define MATRIX_COLS 4
#define MATRIX_ROW_PINS { GP3, GP4, GP5, GP6, GP7 }
#define MATRIX_COL_PINS { GP10, GP11, GP12, GP13 }
```

### Step 2: Build and Flash

```bash
./setup.sh
```

The script will:
- Check dependencies
- Clone/update vial-qmk
- Install QMK dependencies
- Copy your firmware config
- Compile the firmware
- Wait for bootloader mode
- Automatically flash when RPI-RP2 drive appears

### Step 3: Enter Bootloader (when prompted)

1. Hold BOOT button on RP2040 Zero
2. Plug USB into computer (keep holding BOOT)
3. Release BOOT button
4. RPI-RP2 drive appears in file manager
5. Script detects it and flashes automatically

### Step 4: Test with Vial

Once flashed:

1. Open https://usevia.app in browser
2. Click "Authorize Device"
3. You should see your 5x4 numpad layout
4. Test each key by pressing it
5. Configure layers 1-9 in the web UI
6. Changes save to keyboard automatically

## Troubleshooting

### Device Not Recognized in Bootloader Mode

- Verify USB cable is functional
- Try a different USB port
- Ensure BOOT button is held throughout the replug process

### Build Fails with Compiler Error

- Check that arm-none-eabi-gcc is installed: `arm-none-eabi-gcc --version`
- Verify firmware configuration matches your hardware
- Review the build output for specific errors

### Keys Not Registering

- Check matrix wiring for continuity issues
- Verify GPIO pin assignments in firmware match your wiring
- Test with a simple layer that has known key assignments
- Use Vial's key tester to identify which positions aren't responding

### Vial Device Not Appearing

- Re-flash the firmware with Vial support enabled
- Verify the `.uf2` file was built correctly
- Try replugging the USB cable

## File Structure

```
.
├── README.md              # This file
├── CLAUDE.md              # Build instructions for Claude
├── build.sh               # Compile and flash script
├── firmware/              # QMK keyboard configuration
│   ├── config.h           # Matrix and pin definitions
│   ├── keymap.c           # Key assignments
│   ├── rules.mk           # Build configuration
│   └── info.json          # Keyboard metadata
├── layout/                # Keyboard layout files
├── hardware/              # PCB and wiring documentation
└── vial-qmk/              # Vial-QMK fork (created by build.sh)
```

## Rebuilding

To rebuild the firmware after making changes:

```bash
./build.sh
```

Changes are automatically reflected in the new `.uf2` file. Re-flash using the same bootloader process.

## References

- [QMK Documentation](https://docs.qmk.fm/)
- [Vial Documentation](https://get.vial.today/)
- [RP2040 Datasheet](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)
- [Keyboard Layout Editor](https://keyboard-layout-editor.com/)
