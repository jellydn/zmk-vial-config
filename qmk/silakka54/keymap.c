// Silakka54 (QMK/Vial): Graphite Miryoku layout, the same layers as the ZMK
// keymap (config/base.keymap). Generated together with silakka54-graphite.vil;
// keep both in sync. Combos, key overrides and macro M0 live in Vial (load the .vil).
#include QMK_KEYBOARD_H

enum layers { _BASE, _NAV, _MOUSE, _SYM, _NUM, _FN };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
               KC_GRV,          KC_1,          KC_2,          KC_3,          KC_4,          KC_5,             KC_6,          KC_7,          KC_8,          KC_9,          KC_0,       KC_MFFD,
              KC_LBRC,          KC_B,          KC_L,          KC_D,          KC_W,          KC_Z,          KC_QUOT,          KC_F,          KC_O,          KC_U,          KC_J,       KC_RBRC,
               KC_ESC,  LGUI_T(KC_N),  LALT_T(KC_R),  LCTL_T(KC_T),  LSFT_T(KC_S),          KC_G,             KC_Y,  RSFT_T(KC_H),  RCTL_T(KC_A),  RALT_T(KC_E),  RGUI_T(KC_I),       KC_COMM,
               KC_F13,          KC_Q,          KC_X,          KC_M,          KC_C,          KC_V,             KC_K,          KC_P,        KC_DOT,       KC_MINS,       KC_SLSH,        KC_DEL,
                                                            KC_EQL, LT(_NAV, KC_SPC), LT(_MOUSE, KC_TAB),    LT(_SYM, KC_ENT), LT(_NUM, KC_BSPC),       KC_SCLN
    ),

    [_NAV] = LAYOUT(
              XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,          XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
              XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,           KC_TAB,       KC_BSPC,         KC_UP,        KC_DEL,       XXXXXXX,       XXXXXXX,
               KC_ESC,       KC_LGUI,       KC_LALT,       KC_LCTL,       KC_LSFT,       XXXXXXX,           KC_ENT,       KC_LEFT,       KC_DOWN,      KC_RIGHT,       KC_CAPS,       XXXXXXX,
              XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,           KC_ESC,        KC_TAB,       KC_HOME,        KC_END,       XXXXXXX,       XXXXXXX,
                                                           XXXXXXX,       XXXXXXX,       XXXXXXX,          KC_PGUP,       KC_PGDN,       QK_LLCK
    ),

    [_MOUSE] = LAYOUT(
              XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,          XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
              XXXXXXX,       XXXXXXX,    LGUI(KC_W),    LGUI(KC_C),    LGUI(KC_V),    LGUI(KC_X),           KC_TAB,       XXXXXXX,         MS_UP,       XXXXXXX,       XXXXXXX,       XXXXXXX,
               KC_ESC,       KC_LGUI,       KC_LALT,       KC_LCTL,       KC_LSFT, C(S(G(KC_4))),           KC_ENT,       MS_LEFT,       MS_DOWN,       MS_RGHT,       XXXXXXX,       XXXXXXX,
              XXXXXXX,       XXXXXXX,    LGUI(KC_Q),    LGUI(KC_S),    LGUI(KC_A),      OSL(_FN),           KC_ESC,       MS_WHLL,       MS_WHLD,       MS_WHLU,       MS_WHLR,       XXXXXXX,
                                                           XXXXXXX,       XXXXXXX,       XXXXXXX,          MS_BTN1,       MS_BTN2,       QK_LLCK
    ),

    [_SYM] = LAYOUT(
              XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,          XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
              XXXXXXX, LSFT(KC_LBRC),    LSFT(KC_7),    LSFT(KC_8),    LSFT(KC_9), LSFT(KC_RBRC),          XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
              XXXXXXX, LSFT(KC_SCLN),    LSFT(KC_4),    LSFT(KC_5),    LSFT(KC_6),  LSFT(KC_EQL),           KC_ENT,       KC_RSFT,       KC_RCTL,       KC_RALT,       KC_RGUI,       XXXXXXX,
              XXXXXXX,  LSFT(KC_GRV),    LSFT(KC_1),    LSFT(KC_2),    LSFT(KC_3), LSFT(KC_BSLS),           KC_ESC, LSFT(KC_COMM),  LSFT(KC_DOT), LSFT(KC_SLSH),       XXXXXXX,       XXXXXXX,
                                                        LSFT(KC_9),    LSFT(KC_0), LSFT(KC_MINS),          XXXXXXX,       XXXXXXX,       XXXXXXX
    ),

    [_NUM] = LAYOUT(
              XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,          XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
              XXXXXXX,       KC_LBRC,          KC_7,          KC_8,          KC_9,       KC_RBRC,          XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
              XXXXXXX,       KC_SCLN,          KC_4,          KC_5,          KC_6,        KC_EQL,           KC_ENT,       KC_RSFT,       KC_RCTL,       KC_RALT,       KC_RGUI,       XXXXXXX,
              XXXXXXX,        KC_GRV,          KC_1,          KC_2,          KC_3,       KC_BSLS,           KC_ESC,       KC_COMM,        KC_DOT,       KC_SLSH,       XXXXXXX,       XXXXXXX,
                                                              KC_9,          KC_0,       KC_MINS,          XXXXXXX,       XXXXXXX,       XXXXXXX
    ),

    [_FN] = LAYOUT(
              XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,          XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
              XXXXXXX,        KC_F12,         KC_F7,         KC_F8,         KC_F9,       KC_MUTE,          XXXXXXX,       KC_MPRV,       KC_MPLY,       KC_MNXT,       XXXXXXX,       XXXXXXX,
              XXXXXXX,        KC_F11,         KC_F4,         KC_F5,         KC_F6,       KC_VOLU,          XXXXXXX,       KC_RSFT,       KC_RCTL,       KC_RALT,       KC_RGUI,       XXXXXXX,
              XXXXXXX,        KC_F10,         KC_F1,         KC_F2,         KC_F3,       KC_VOLD,          XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
                                                            KC_F13,        KC_SPC,        KC_TAB,          XXXXXXX,       XXXXXXX,       QK_LLCK
    )
};

// Combos fire only on the base layer, like the ZMK combos. Without this, "."
// and "-" on the Num layer would trigger the sticky Meh combo.
bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    return get_highest_layer(layer_state) == _BASE;
}
