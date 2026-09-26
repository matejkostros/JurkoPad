# JurkoPad - Mechanical Numpad

A 5x4 custom mechanical numpad with Cherry MX switches, handwired and soldered to a Waveshare RP2040 Zero. Features QMK firmware with Vial support for runtime layer configuration and macro programming.

*(Looking for the short Slovak version for kids? See [README.md](README.md).)*

## Quick Start

1. **Plug in via USB** - Num Lock toggles on automatically
2. **All keys work out of the box** - Layer 0 is standard numpad layout
3. **Reprogram anytime** - Open https://vial.rocks and edit layers 1-9
4. **Access bootloader** - Hold Fn, press Enter (for firmware updates; see [Enter Bootloader Mode](#enter-bootloader-mode) for the BOOT-button fallback)

## Layout

### Layer 0 (Default - Standard Numpad)

```
🔒 Lock    🧮 Calc      Fn          /
7(Home)    8(↑)         9(PgUp)     *
4(←)       5            6(→)        -
1(End)     2(↓)         3(PgDn)     +
0(Ins)     Backspace    .(Del)      Enter
```

When **Num Lock is ON**: Keys send numbers (0-9, operators)  
When **Num Lock is OFF**: Keys send navigation (arrows, Home, End, PgUp, PgDn, Insert, Delete)

### Layer 10 (Fn Key - Layer Selector)

Hold the **Fn key** to access this layer:

```
Reset      Fn           Fn          Boot
Lock7      Lock8        Lock9       (Boot mode)
Lock4      Lock5        Lock6
Lock1      Lock2        Lock3
Lock0      -            -           Enter+Boot
```

**How to use:**
- Hold **Fn** and press any key to **lock** to that layer (0-9)
- Each numpad key (0-9) corresponds to layer 0-9
- Fn+Enter enters bootloader mode for firmware updates
- Fn+Num Lock (`EE_CLR`) resets the keyboard to factory defaults, wiping any layers/macros saved via Vial

### Layers 1-9 (User Configurable)

All layers 1-9 are empty by default. Configure them via Vial:

1. Open https://vial.rocks in browser
2. Connect your numpad (authorize device when prompted)
3. Click each layer tab and assign keys
4. Changes save automatically to your keyboard

Each layer inherits the Fn key, so you can always access the layer selector.

## Features

**Num Lock Auto-On**  
Num Lock toggles on automatically when you plug in the keyboard. Numbers are ready to use immediately.

**Multi-Layer Support**  
11 layers total (Layer 0 default + Layers 1-9 custom + Layer 10 selector). Switch between layers instantly.

**Bootloader Access Without Button**  
Press Fn+Enter to enter bootloader mode. No need to physically press the BOOT button.

**Factory Reset Without Reflashing**  
Press Fn+Num Lock to clear Vial's saved EEPROM data (custom layers, macros) and restore the layout the firmware ships with.

**Macro Support**  
Layer 1-9 support macros through Vial. Record complex key sequences and assign them to any key.

**USB Identification**  
Appears as "K0S3K JurkoPad" when connected to any computer.

## Reprogram Via Vial

### To Change a Key:

1. Open https://vial.rocks in browser
2. Select the layer you want to edit (Layer 1-9, or Layer 0 for defaults)
3. Click any key in the layout
4. Search for or select a new key code
5. Changes save immediately

### To Create a Macro:

1. In Vial, click on a key and select "Macro" from the key picker
2. Enter the macro sequence (e.g., `Hello World`)
3. Click save

### To Lock to a Layer:

1. Press Fn and hold it
2. Press any key 0-9 to lock to that layer
3. Release Fn
4. You're now on Layer 0-9 (example: Fn+7 locks to Layer 7)

## Update Firmware

If you need to rebuild or update the firmware:

```bash
./setup.sh
```

When prompted, hold the BOOT button, plug USB in, then release. The script will flash automatically.

---

## Build Instructions (for developers)

### Prerequisites (Fedora Linux)

```bash
sudo dnf install make python3 git arm-none-eabi-gcc arm-none-eabi-newlib
```

Verify installation:

```bash
make --version && python3 --version && arm-none-eabi-gcc --version
```

### Build and Flash

```bash
./setup.sh
```

The script will:
1. Check dependencies
2. Clone/update vial-qmk
3. Install QMK dependencies
4. Copy firmware config
5. Compile firmware
6. Wait for bootloader mode
7. Auto-flash when RPI-RP2 drive appears

### Enter Bootloader Mode

**Preferred: from the keyboard, no button needed.** Requires JurkoPad to already have working firmware on it (so it can catch the key combo).

1. Hold **Fn** (top row, 3rd key)
2. While still holding Fn, press **Enter** (bottom-right key)
3. Release both keys
4. RPI-RP2 drive appears in file manager
5. Script detects and flashes automatically

**Fallback: physical BOOT button.** Use this only if Fn+Enter doesn't work (unresponsive pad) or on the very first flash of a blank board, since Fn+Enter needs firmware that isn't there yet to catch the combo.

1. Hold BOOT button on RP2040 Zero
2. Plug USB into computer (keep holding BOOT)
3. Release BOOT button
4. RPI-RP2 drive appears in file manager
5. Script detects and flashes automatically

### Wiring Reference (COL2ROW)

**Row pins (GPIO):** 29, 28, 27, 26, 15  
**Column pins (GPIO):** 10, 11, 12, 13  
**Diode orientation:** Cathode (stripe) toward row, anode toward column

### File Structure

```
├── README.md                    # This file
├── CLAUDE.md                    # Development notes
├── setup.sh                     # Build and flash script
├── layout.json                  # Keyboard Layout Editor JSON
├── firmware/
│   ├── config.h                # Matrix and feature config
│   ├── keyboard.json           # Keyboard metadata (used by build)
│   ├── rules.mk                # Build flags
│   └── keymaps/vial/
│       ├── keymap.c            # Layer definitions
│       ├── config.h            # Vial settings
│       └── vial.json           # Vial matrix definition
└── vial-qmk/                    # QMK fork (auto-created)
```

### Troubleshooting

**Device not recognized in Vial**
- Re-flash using `./setup.sh`
- Ensure bootloader mode was entered correctly

**Build fails with compiler error**
- Verify arm-none-eabi-gcc is installed
- Check Python version: `python3 --version` (should be 3.10+)

**Keys not registering**
- Check matrix wiring continuity
- Verify GPIO pins in firmware match your wiring
- Use Vial's key tester to identify dead zones

## References

- [QMK Docs](https://docs.qmk.fm/)
- [Vial Docs](https://get.vial.today/)
- [RP2040 Datasheet](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)
