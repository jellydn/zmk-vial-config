#pragma once

// Same UID as the stock Silakka54 Vial keymap, so .vil files load across both.
#define VIAL_KEYBOARD_UID {0x97, 0xD0, 0xA5, 0x97, 0x57, 0x48, 0xD0, 0x4F}
#define VIAL_UNLOCK_COMBO_ROWS {0, 0}
#define VIAL_UNLOCK_COMBO_COLS {0, 1}

// The keyboard definition sets no layer count (QMK default: 4); the layout has 6.
#define DYNAMIC_KEYMAP_LAYER_COUNT 6

// Bootmagic: hold the outer top key of a half while plugging it in to enter the
// bootloader. Left: (0,0), set by the keyboard; right: (5,0), its mirror.
#define BOOTMAGIC_ROW_RIGHT 5
#define BOOTMAGIC_COLUMN_RIGHT 0

// Defaults for Vial's QMK Settings after an EEPROM reset; they match
// silakka54-graphite.vil. Loading the .vil also sets permissive hold and
// chordal hold, which Vial resets to off. Flow Tap stays off, as on the Corne:
// it turned home-row Shift into a letter right after typing.
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
