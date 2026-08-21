#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
VIAL_QMK_DIR="$SCRIPT_DIR/vial-qmk"
FIRMWARE_DIR="$SCRIPT_DIR/firmware"
BUILD_DIR="$VIAL_QMK_DIR/.build"
UF2_FILE="$BUILD_DIR/macropad_vial.uf2"

echo "=== MacroNumpad Build Script ==="
echo

check_tool() {
    if ! command -v "$1" &> /dev/null; then
        echo "ERROR: $1 not found. Install with: sudo dnf install $2"
        exit 1
    fi
}

check_tool "make" "make"
check_tool "python3" "python3"
check_tool "git" "git"
check_tool "arm-none-eabi-gcc" "arm-none-eabi-gcc"

echo "[1/6] All dependencies found ✓"
echo

if [ ! -d "$VIAL_QMK_DIR" ]; then
    echo "[2/6] Cloning vial-qmk (first run, may take a minute)..."
    git clone --depth 1 https://github.com/vial-kb/vial-qmk.git "$VIAL_QMK_DIR"
else
    echo "[2/6] vial-qmk already cloned, updating..."
    cd "$VIAL_QMK_DIR"
    git pull --depth 1
    cd "$SCRIPT_DIR"
fi
echo

echo "[3/6] Installing QMK dependencies..."
cd "$VIAL_QMK_DIR"
pip install -q -r requirements.txt 2>/dev/null || pip3 install -q -r requirements.txt 2>/dev/null
pip install -q qmk 2>/dev/null || pip3 install -q qmk 2>/dev/null
export PATH="$HOME/.local/bin:$PATH"
cd "$SCRIPT_DIR"
echo

echo "[4/6] Copying firmware config..."
mkdir -p "$VIAL_QMK_DIR/keyboards/macropad/keymaps/vial"
cp "$FIRMWARE_DIR/keyboard.json" "$VIAL_QMK_DIR/keyboards/macropad/"
cp "$FIRMWARE_DIR/config.h" "$VIAL_QMK_DIR/keyboards/macropad/"
cp "$FIRMWARE_DIR/keymap.c" "$VIAL_QMK_DIR/keyboards/macropad/"
cp "$FIRMWARE_DIR/rules.mk" "$VIAL_QMK_DIR/keyboards/macropad/"
if [ -d "$FIRMWARE_DIR/keymaps/vial" ]; then
    cp -r "$FIRMWARE_DIR/keymaps/vial"/* "$VIAL_QMK_DIR/keyboards/macropad/keymaps/vial/"
fi
echo

echo "[5/6] Compiling firmware (macropad:vial)..."
cd "$VIAL_QMK_DIR"
make -j4 macropad:vial 2>&1 | grep -E "(^|$|error|warning|\[.*%)" || true
cd "$SCRIPT_DIR"
echo

if [ ! -f "$UF2_FILE" ]; then
    echo "ERROR: Build failed. No .uf2 file generated."
    echo "Check firmware config in $FIRMWARE_DIR/"
    exit 1
fi

echo "[6/6] Build complete! ✓"
echo "Output: $UF2_FILE"
echo

echo "=== Ready to Flash ==="
echo
echo "1. Hold BOOT button on RP2040 Zero"
echo "2. Plug USB into computer (while holding BOOT)"
echo "3. Release BOOT button"
echo
read -p "Press Enter when you've entered bootloader mode..."
echo

RPI_DEVICE=$(lsblk -o NAME,LABEL 2>/dev/null | grep RPI-RP2 | awk '{print $1}' | sed 's/[├└─]//g')
if [ -z "$RPI_DEVICE" ]; then
    echo "ERROR: RPI-RP2 not found."
    echo "Check: USB cable, BOOT button held during replug"
    echo "Try: lsblk"
    exit 1
fi

RPI_DEVICE="/dev/$RPI_DEVICE"
RPI_PATH="/tmp/rpi-rp2-mount"
mkdir -p "$RPI_PATH"

echo "Mounting $RPI_DEVICE to $RPI_PATH..."
sudo mount "$RPI_DEVICE" "$RPI_PATH" || {
    echo "ERROR: Could not mount $RPI_DEVICE"
    exit 1
}

echo "Copying firmware..."
sudo cp "$UF2_FILE" "$RPI_PATH/" || {
    echo "ERROR: Copy failed"
    sudo umount "$RPI_PATH" 2>/dev/null
    exit 1
}

sudo sync
echo "Unmounting..."
sudo umount "$RPI_PATH"
rm -rf "$RPI_PATH"

echo
echo "Flash complete! Device rebooting..."
sleep 3
echo
echo "JurkoPad is ready!"
echo "Next: Unplug and replug USB (normal mode), then open https://usevia.app"
