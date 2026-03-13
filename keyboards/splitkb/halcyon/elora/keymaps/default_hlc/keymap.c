#include QMK_KEYBOARD_H

// Layer names
enum layers {
    _L0,
    _L1,
    _L2,
    _L3,
    _L4,
    _L5,
    _L6,
    _L7
};

// Hold-tap and mod-tap aliases
#define CTL_CAP LCTL_T(KC_CAPSLOCK)
#define CTL_QUO RCTL_T(KC_QUOTE)
#define CTL_MIN RCTL_T(KC_MINUS)
#define ALT_ENT LALT_T(KC_ENTER)

// Macro keycodes
enum custom_keycodes {
    M0 = SAFE_RANGE,
    M1,
    M2,
    M3,
    M4,
    M5
};

// Tap dance declarations
enum {
    TD_ESC = 0,
    TD_C,
    TD_V,
    TD_T,
    TD_S,
    TD_SLASH
};

// Tap dance actions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC]   = ACTION_TAP_DANCE_DOUBLE(KC_ESCAPE, M0),
    [TD_C]     = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, td_c_finished, NULL, 224),
    [TD_V]     = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, td_v_finished, NULL, 224),
    [TD_T]     = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, td_t_finished, NULL, 201),
    [TD_S]     = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, td_s_finished, NULL, 224),
    [TD_SLASH] = ACTION_TAP_DANCE_DOUBLE(KC_SLASH, KC_BSLASH)
};

// Tap dance functions for C, V, T, S
void td_c_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(KC_C);
    } else if (state->count == 2) {
        tap_code16(M1);
    }
}
void td_v_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(KC_V);
    } else if (state->count == 2) {
        tap_code16(M2);
    }
}
void td_t_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(KC_T);
    } else if (state->count == 2) {
        tap_code16(M5);
    }
}
void td_s_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(KC_S);
    } else if (state->count == 2) {
        tap_code16(M4);
    }
}

// Macros M0-M5
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case M0:
            if (record->event.pressed) {
                tap_code16(KC_LGUI);
                tap_code16(KC_F12);
            }
            return false;
        case M1:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                tap_code16(KC_C);
                unregister_code(KC_LGUI);
            }
            return false;
        case M2:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                tap_code16(KC_V);
                unregister_code(KC_LGUI);
            }
            return false;
        case M3:
            if (record->event.pressed) {
                register_code(KC_LCTRL);
                tap_code16(KC_SPACE);
                unregister_code(KC_LCTRL);
            }
            return false;
        case M4:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                tap_code16(KC_S);
                unregister_code(KC_LGUI);
            }
            return false;
        case M5:
            if (record->event.pressed) {
                register_code(KC_LCTRL);
                wait_ms(15);
                tap_code16(KC_SPACE);
                wait_ms(15);
                unregister_code(KC_LCTRL);
            }
            return false;
    }
    return true;
}

// Combo stub (none defined in Vial JSON)
__attribute__((weak))
combo_t key_combos[1] = {};

// Keymaps (from Vial JSON, with tap-dance and hold-tap behaviors)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_L0] = LAYOUT_elora_hlc(
TD(TD_ESC),KC_1,KC_2,KC_3,KC_4,KC_5,                       KC_6,KC_7,KC_8,KC_9,KC_0,KC_MINUS,
KC_TAB,KC_Q,KC_W,KC_E,KC_R,TD(TD_T),                       KC_Y,KC_U,KC_I,KC_O,KC_P,KC_BSPC,
CTL_CAP,KC_A,TD(TD_S),KC_D,KC_F,KC_G,                      KC_H,KC_J,KC_K,KC_L,KC_SCLN,CTL_QUO,
KC_LSHIFT,KC_Z,KC_X,TD(TD_C),TD(TD_V),KC_B,KC_LBRC,KC_RBRC,   MO(1),KC_UP,KC_N,KC_M,KC_COMM,KC_DOT,TD(TD_SLASH),KC_ENT,
KC_LCTRL,KC_LALT,KC_LGUI,KC_SPACE,KC_GRAVE,                KC_LEFT,KC_DOWN,KC_RIGHT,KC_SPACE,KC_EQUAL,
KC_MUTE,KC_NO,KC_NO,KC_NO,KC_NO,                           KC_MUTE,KC_NO,KC_NO,KC_NO,KC_NO
),

[_L1] = LAYOUT_elora_hlc(
KC_ESC,KC_1,KC_2,KC_3,KC_4,KC_5,                           KC_6,KC_7,KC_8,KC_9,KC_0,KC_ESC,
KC_TAB,KC_QUOTE,KC_COMM,KC_DOT,KC_P,KC_Y,                  KC_F,KC_G,KC_C,KC_R,KC_L,KC_BSPC,
LCTL_T(KC_ESC),KC_A,KC_O,KC_E,KC_U,KC_I,                   KC_D,KC_H,KC_T,KC_N,KC_S,CTL_MIN,
KC_LSHIFT,KC_SCLN,KC_Q,KC_J,KC_K,KC_X,KC_LBRC,KC_CAPS,    MO(5),KC_RBRC,KC_B,KC_M,KC_W,KC_V,KC_Z,KC_RSHIFT,
MO(6),KC_LGUI,ALT_ENT,KC_SPACE,MO(3),                      MO(4),KC_SPACE,KC_RALT,KC_RGUI,KC_APP,
KC_MUTE,KC_NO,KC_NO,KC_NO,KC_NO,                           KC_MUTE,KC_NO,KC_NO,KC_NO,KC_NO
),

[_L2] = LAYOUT_elora_hlc(
KC_ESC,KC_1,KC_2,KC_3,KC_4,KC_5,                           KC_6,KC_7,KC_8,KC_9,KC_0,KC_ESC,
KC_TAB,KC_Q,KC_W,KC_F,KC_P,KC_B,                           KC_J,KC_L,KC_U,KC_Y,KC_SCLN,KC_BSPC,
LCTL_T(KC_ESC),KC_A,KC_R,KC_S,KC_T,KC_G,                   KC_M,KC_N,KC_E,KC_I,KC_O,CTL_QUO,
KC_LSHIFT,KC_Z,KC_X,KC_C,KC_D,KC_V,KC_LBRC,KC_CAPS,       MO(5),KC_RBRC,KC_K,KC_H,KC_COMM,KC_DOT,KC_SLSH,KC_RSHIFT,
MO(6),KC_LGUI,ALT_ENT,KC_SPACE,MO(3),                      MO(4),KC_SPACE,KC_RALT,KC_RGUI,KC_APP,
KC_MUTE,KC_NO,KC_NO,KC_NO,KC_NO,                           KC_MUTE,KC_NO,KC_NO,KC_NO,KC_NO
),

[_L3] = LAYOUT_elora_hlc(
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,          KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,          KC_PGUP,KC_HOME,KC_UP,KC_END,KC_VOLU,KC_DEL,
KC_TRNS,KC_LGUI,KC_LALT,KC_LCTRL,KC_LSHIFT,KC_TRNS,       KC_PGDN,KC_LEFT,KC_DOWN,KC_RIGHT,KC_VOLD,KC_INS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_SCRL,   KC_TRNS,KC_TRNS,KC_PAUSE,KC_MPRV,KC_MPLY,KC_MNXT,KC_MUTE,KC_PSCR,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS
),

[_L4] = LAYOUT_elora_hlc(
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,          KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_GRAVE,KC_1,KC_2,KC_3,KC_4,KC_5,                         KC_6,KC_7,KC_8,KC_9,KC_0,KC_EQUAL,
LSFT(KC_GRAVE),LSFT(KC_1),LSFT(KC_2),LSFT(KC_3),LSFT(KC_4),LSFT(KC_5),   LSFT(KC_6),LSFT(KC_7),LSFT(KC_8),LSFT(KC_9),LSFT(KC_0),LSFT(KC_EQUAL),
LSFT(KC_BSLS),KC_BSLS,LSFT(KC_SCLN),KC_SCLN,KC_MINUS,KC_LBRC,LSFT(KC_LBRC),KC_TRNS,   KC_TRNS,LSFT(KC_RBRC),KC_RBRC,LSFT(KC_MINUS),KC_COMM,KC_DOT,KC_SLSH,LSFT(KC_SLSH),
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS
),

[_L5] = LAYOUT_elora_hlc(
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,          KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_F9,KC_F10,KC_F11,KC_F12,KC_TRNS,                KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_F5,KC_F6,KC_F7,KC_F8,KC_TRNS,                   KC_TRNS,KC_RSHIFT,KC_RCTRL,KC_LALT,KC_RGUI,KC_TRNS,
KC_TRNS,KC_F1,KC_F2,KC_F3,KC_F4,KC_TRNS,KC_TRNS,KC_TRNS,  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS
),

[_L6] = LAYOUT_elora_hlc(
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,          KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,DF(0),KC_TRNS,KC_TRNS,            KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,DF(1),KC_TRNS,KC_TRNS,            RM_TOGG,RM_SATU,RM_HUEU,RM_VALU,RM_NEXT,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,DF(2),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,RM_SATD,RM_HUED,RM_VALD,RM_PREV,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS
),

[_L7] = LAYOUT_elora_hlc(
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,          KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,          KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,          KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS
),

};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
[_L0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
[_L1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
[_L2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
[_L3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
[_L4] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
[_L5] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
[_L6] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
[_L7] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif
