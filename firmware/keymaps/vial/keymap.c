#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_NUM,    KC_CALC,    MO(10),     KC_PSLS,
        KC_P7,      KC_P8,      KC_P9,      KC_PAST,
        KC_P4,      KC_P5,      KC_P6,      KC_PMNS,
        KC_P1,      KC_P2,      KC_P3,      KC_PPLS,
        KC_P0,      KC_BSPC,    KC_PDOT,    KC_PENT
    ),
    [1] = LAYOUT(
        KC_TRNS,    KC_TRNS,    MO(10),     KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
    [2] = LAYOUT(
        KC_TRNS,    KC_TRNS,    MO(10),     KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
    [3] = LAYOUT(
        KC_TRNS,    KC_TRNS,    MO(10),     KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
    [4] = LAYOUT(
        KC_TRNS,    KC_TRNS,    MO(10),     KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
    [5] = LAYOUT(
        KC_TRNS,    KC_TRNS,    MO(10),     KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
    [6] = LAYOUT(
        KC_TRNS,    KC_TRNS,    MO(10),     KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
    [7] = LAYOUT(
        KC_TRNS,    KC_TRNS,    MO(10),     KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
    [8] = LAYOUT(
        KC_TRNS,    KC_TRNS,    MO(10),     KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
    [9] = LAYOUT(
        KC_TRNS,    KC_TRNS,    MO(10),     KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
    [10] = LAYOUT(
        KC_TRNS,    KC_TRNS,    MO(10),     KC_TRNS,
        TO(7),      TO(8),      TO(9),      KC_TRNS,
        TO(4),      TO(5),      TO(6),      KC_TRNS,
        TO(1),      TO(2),      TO(3),      KC_TRNS,
        TO(0),      KC_TRNS,    KC_TRNS,    QK_BOOT
    )
};

void matrix_init_user(void) {
    tap_code(KC_NUM);
}
