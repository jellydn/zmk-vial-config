#pragma once

// Same UID as foostan's Corne v4 Vial build, so .vil files load across both.
#define VIAL_KEYBOARD_UID {0x89, 0x36, 0x2A, 0xC7, 0xFA, 0xD8, 0x89, 0x45}
#define VIAL_UNLOCK_COMBO_ROWS {0, 0}
#define VIAL_UNLOCK_COMBO_COLS {0, 1}

// Defaults for Vial's QMK Settings after an EEPROM reset; they match
// corne-v4.1-graphite.vil. Loading the .vil also sets permissive hold and
// chordal hold, which Vial resets to off. Flow Tap stays off, as in the original
// dotfiles .vil: it turned home-row Shift into a letter right after typing.
#define TAPPING_TERM 200
#define COMBO_TERM 50
#define COMBO_SHOULD_TRIGGER // base layer only, see keymap.c
#define ONESHOT_TIMEOUT 5000

#define MOUSEKEY_DELAY 10
#define MOUSEKEY_INTERVAL 20
#define MOUSEKEY_MOVE_DELTA 8
#define MOUSEKEY_MAX_SPEED 10
#define MOUSEKEY_TIME_TO_MAX 30
#define MOUSEKEY_WHEEL_DELAY 10
#define MOUSEKEY_WHEEL_INTERVAL 80
#define MOUSEKEY_WHEEL_MAX_SPEED 8
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40

// LEDs: Typing Heatmap after an EEPROM reset (keymap.c also selects it on the
// first boot of each new build). Brightness stays under the board's cap of 50.
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_TYPING_HEATMAP
#define RGB_MATRIX_DEFAULT_VAL 40
