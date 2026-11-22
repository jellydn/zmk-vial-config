// Corne v4.1 (crkbd/rev4_1/standard): Graphite Miryoku layout, synced with the
// Silakka54 keymap. Generated from corne-v4.1-graphite.vil; keep both in sync.
// keymap.c writes the .vil combos, key overrides, macro M0 and QMK Settings on
// first boot.
#include QMK_KEYBOARD_H
#include "qmk_settings.h"

enum layers { _BASE, _NAV, _MOUSE, _SYM, _NUM, _FN };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3_ex2(
              KC_LBRC,          KC_B,          KC_L,          KC_D,          KC_W,          KC_Z,       KC_LEFT,         KC_RIGHT,       KC_QUOT,          KC_F,          KC_O,          KC_U,          KC_J,       KC_RBRC,
               KC_ESC,  LGUI_T(KC_N),  LALT_T(KC_R),  LCTL_T(KC_T),  LSFT_T(KC_S),          KC_G,       KC_MPLY,          KC_MNXT,          KC_Y,  RSFT_T(KC_H),  RCTL_T(KC_A),  RALT_T(KC_E),  RGUI_T(KC_I),       KC_COMM,
               KC_F13,          KC_Q,          KC_X,          KC_M,          KC_C,          KC_V,                                            KC_K,          KC_P,        KC_DOT,       KC_MINS,       KC_SLSH,        KC_DEL,
                                                            KC_EQL, LT(_NAV, KC_SPC), LT(_MOUSE, KC_TAB),    LT(_SYM, KC_ENT), LT(_NUM, KC_BSPC),       KC_SCLN
    ),

    [_NAV] = LAYOUT_split_3x6_3_ex2(
              XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       KC_VOLD,          KC_VOLU,        KC_TAB,       KC_BSPC,         KC_UP,        KC_DEL,       XXXXXXX,       XXXXXXX,
               KC_ESC,       KC_LGUI,       KC_LALT,       KC_LCTL,       KC_LSFT,       XXXXXXX,       KC_MUTE,          KC_MNXT,        KC_ENT,       KC_LEFT,       KC_DOWN,      KC_RIGHT,       KC_CAPS,       XXXXXXX,
              XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,                                          KC_ESC,        KC_TAB,       KC_HOME,        KC_END,       XXXXXXX,       XXXXXXX,
                                                           XXXXXXX,       XXXXXXX,       XXXXXXX,          KC_PGUP,       KC_PGDN,       QK_LLCK
    ),

    [_MOUSE] = LAYOUT_split_3x6_3_ex2(
              XXXXXXX,       XXXXXXX,    LGUI(KC_W),    LGUI(KC_C),    LGUI(KC_V),    LGUI(KC_X),       KC_VOLD,          KC_VOLU,        KC_TAB,       XXXXXXX,         MS_UP,       XXXXXXX,       XXXXXXX,       XXXXXXX,
               KC_ESC,       KC_LGUI,       KC_LALT,       KC_LCTL,       KC_LSFT,    QK_MACRO_0,       KC_MUTE,          KC_MNXT,        KC_ENT,       MS_LEFT,       MS_DOWN,       MS_RGHT,       XXXXXXX,       XXXXXXX,
              XXXXXXX,       XXXXXXX,    LGUI(KC_Q),    LGUI(KC_S),    LGUI(KC_A),      OSL(_FN),                                          KC_ESC,       MS_WHLL,       MS_WHLD,       MS_WHLU,       MS_WHLR,       XXXXXXX,
                                                           XXXXXXX,       XXXXXXX,       XXXXXXX,          MS_BTN1,       MS_BTN2,       QK_LLCK
    ),

    [_SYM] = LAYOUT_split_3x6_3_ex2(
              XXXXXXX, LSFT(KC_LBRC),    LSFT(KC_7),    LSFT(KC_8),    LSFT(KC_9), LSFT(KC_RBRC),       XXXXXXX,          XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
              XXXXXXX, LSFT(KC_SCLN),    LSFT(KC_4),    LSFT(KC_5),    LSFT(KC_6),  LSFT(KC_EQL),       XXXXXXX,          XXXXXXX,        KC_ENT,       KC_RSFT,       KC_RCTL,       KC_RALT,       KC_RGUI,       XXXXXXX,
              XXXXXXX,  LSFT(KC_GRV),    LSFT(KC_1),    LSFT(KC_2),    LSFT(KC_3), LSFT(KC_BSLS),                                          KC_ESC, LSFT(KC_COMM),  LSFT(KC_DOT), LSFT(KC_SLSH),       XXXXXXX,       XXXXXXX,
                                                        LSFT(KC_9),    LSFT(KC_0), LSFT(KC_MINS),          XXXXXXX,       XXXXXXX,       XXXXXXX
    ),

    [_NUM] = LAYOUT_split_3x6_3_ex2(
              XXXXXXX,       KC_LBRC,          KC_7,          KC_8,          KC_9,       KC_RBRC,       KC_VOLD,          KC_VOLU,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
              XXXXXXX,       KC_SCLN,          KC_4,          KC_5,          KC_6,        KC_EQL,       KC_MUTE,          KC_MNXT,        KC_ENT,       KC_RSFT,       KC_RCTL,       KC_RALT,       KC_RGUI,       XXXXXXX,
              XXXXXXX,        KC_GRV,          KC_1,          KC_2,          KC_3,       KC_BSLS,                                          KC_ESC,       KC_COMM,        KC_DOT,       KC_SLSH,       XXXXXXX,       XXXXXXX,
                                                              KC_9,          KC_0,       KC_MINS,          XXXXXXX,       XXXXXXX,       XXXXXXX
    ),

    [_FN] = LAYOUT_split_3x6_3_ex2(
              XXXXXXX,        KC_F12,         KC_F7,         KC_F8,         KC_F9,       KC_MUTE,       XXXXXXX,          XXXXXXX,       XXXXXXX,       KC_MPRV,       KC_MPLY,       KC_MNXT,       XXXXXXX,       XXXXXXX,
              XXXXXXX,        KC_F11,         KC_F4,         KC_F5,         KC_F6,       KC_VOLU,       XXXXXXX,          XXXXXXX,       XXXXXXX,       KC_RSFT,       KC_RCTL,       KC_RALT,       KC_RGUI,       XXXXXXX,
              XXXXXXX,        KC_F10,         KC_F1,         KC_F2,         KC_F3,       KC_VOLD,                                         XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
                                                            KC_F13,        KC_SPC,        KC_TAB,          XXXXXXX,       XXXXXXX,       QK_LLCK
    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD) },
    [_NAV] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD) },
    [_MOUSE] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD) },
    [_SYM] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD) },
    [_NUM] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_FN] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
};
#endif

// Combos fire only on the base layer, like the Silakka54 ZMK combos. Without
// this, "." and "-" on the Num layer would trigger the sticky Meh combo.
bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    return get_highest_layer(layer_state) == _BASE;
}

// Chordal Hold (on in the .vil) makes a tap-hold key a tap when the next key is
// on the same hand. The thumb layer-taps count as neither hand, so they turn
// their layer on also with keys on their own hand (Esc and the mods on Nav and
// Mouse). A home-row mod plus a thumb key is then a chord too, as on the
// Silakka54, whose home-row mods take all thumbs as hold-trigger keys.
// Vial's QMK Settings owns get_chordal_hold, so the per-key rule goes here.
char chordal_hold_handedness(keypos_t key) {
    if (IS_QK_LAYER_TAP(keymap_key_to_keycode(_BASE, key))) {
        return '*';
    }
    return (char)pgm_read_byte(&chordal_hold_layout[key.row][key.col]);
}

// Vial erases its combos, key overrides and macros on the first boot of every
// new build.
// Write the ones from corne-v4.1-graphite.vil back then, so they work without
// loading the .vil.
// Keep this list in the same order as the .vil.
static const vial_combo_entry_t default_combos[] PROGMEM = {
    {{KC_B, KC_L, KC_NO, KC_NO}, KC_ESC},
    {{KC_L, KC_D, KC_NO, KC_NO}, OSM(MOD_LGUI)},
    {{KC_B, KC_L, KC_D, KC_NO}, LGUI(KC_Q)},
    {{KC_L, KC_W, KC_NO, KC_NO}, KC_ENT},
    {{KC_D, KC_W, KC_NO, KC_NO}, OSM(MOD_HYPR)},
    {{KC_Q, KC_X, KC_NO, KC_NO}, LGUI(KC_X)},
    {{KC_X, KC_M, KC_NO, KC_NO}, LGUI(KC_C)},
    {{KC_F, KC_O, KC_NO, KC_NO}, OSM(MOD_MEH)},
    {{KC_F, KC_U, KC_NO, KC_NO}, KC_ESC},
    {{KC_O, KC_U, KC_NO, KC_NO}, KC_QUOT},
    {{KC_DOT, KC_MINS, KC_NO, KC_NO}, OSM(MOD_MEH)},
};

// The Graphite shift pairs, also from the .vil and in the same order: Shift
// (either side) on the base layer changes the shifted symbol of ' , / -.
#define GRAPHITE_SHIFT(trigger, replacement) \
    {trigger, replacement, 1 << _BASE, MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT), 0, 0, \
     vial_ko_enabled | vial_ko_option_activation_trigger_down | \
     vial_ko_option_activation_required_mod_down | vial_ko_option_activation_negative_mod_up}

static const vial_key_override_entry_t default_key_overrides[] PROGMEM = {
    GRAPHITE_SHIFT(KC_QUOT, LSFT(KC_MINS)), // Shift+' gives _
    GRAPHITE_SHIFT(KC_COMM, LSFT(KC_SLSH)), // Shift+, gives ?
    GRAPHITE_SHIFT(KC_SLSH, LSFT(KC_COMM)), // Shift+/ gives <
    GRAPHITE_SHIFT(KC_MINS, LSFT(KC_QUOT)), // Shift+- gives "
};

// Macro M0 from the .vil, in Vial's macro buffer format: hold Shift, Gui and
// Ctrl, tap 4, release them (macOS area screenshot to the clipboard). Each
// step is SS_QMK_PREFIX, the action, then the keycode; the macro ends with 0.
static const uint8_t default_macros[] PROGMEM = {
    SS_QMK_PREFIX, SS_DOWN_CODE, KC_LSFT,
    SS_QMK_PREFIX, SS_DOWN_CODE, KC_LGUI,
    SS_QMK_PREFIX, SS_DOWN_CODE, KC_LCTL,
    SS_QMK_PREFIX, SS_TAP_CODE,  KC_4,
    SS_QMK_PREFIX, SS_UP_CODE,   KC_LSFT,
    SS_QMK_PREFIX, SS_UP_CODE,   KC_LGUI,
    SS_QMK_PREFIX, SS_UP_CODE,   KC_LCTL,
    0,
};

// QMK Settings from the .vil that differ from Vial's reset defaults, by QSID.
// Written with qmk_settings_set, as Vial does when it loads the .vil, so they
// show in Vial's QMK Settings tab and can still be changed there.
static void write_default_qmk_settings(void) {
    const uint8_t  on             = 1;
    const uint16_t tap_code_delay = 0; // QSID 18, reset default 10 ms
    qmk_settings_set(18, &tap_code_delay, sizeof(tap_code_delay));
    qmk_settings_set(22, &on, sizeof(on)); // Permissive Hold
    qmk_settings_set(26, &on, sizeof(on)); // Chordal Hold
}

// Detect the first boot of a new build, before Vial resets its EEPROM.
static bool vial_eeprom_was_reset;

void via_init_kb(void) {
    vial_eeprom_was_reset = !via_eeprom_is_valid();
}

void keyboard_post_init_user(void) {
    if (vial_eeprom_was_reset) {
        for (uint8_t i = 0; i < ARRAY_SIZE(default_combos); ++i) {
            vial_combo_entry_t combo;
            memcpy_P(&combo, &default_combos[i], sizeof(combo));
            dynamic_keymap_set_combo(i, &combo);
        }
        for (uint8_t i = 0; i < ARRAY_SIZE(default_key_overrides); ++i) {
            vial_key_override_entry_t ko;
            memcpy_P(&ko, &default_key_overrides[i], sizeof(ko));
            dynamic_keymap_set_key_override(i, &ko);
        }
        vial_init(); // reload from EEPROM; Vial read the empty entries before the reset

        uint8_t macros[sizeof(default_macros)];
        memcpy_P(macros, default_macros, sizeof(macros));
        dynamic_keymap_macro_set_buffer(0, sizeof(macros), macros); // read at each press

        write_default_qmk_settings();

        // The .vil holds no LED settings: start on Typing Heatmap. Changes made
        // in Vial stay until the next new build.
        rgb_matrix_enable(); // the setters below do nothing while RGB is off
        rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP);
        rgb_matrix_sethsv(RGB_MATRIX_DEFAULT_HUE, RGB_MATRIX_DEFAULT_SAT, RGB_MATRIX_DEFAULT_VAL);
    }
}
