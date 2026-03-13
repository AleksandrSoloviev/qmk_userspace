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
KC_5,KC_4,KC_3,KC_2,KC_1,TD(TD_ESC),                         KC_6,KC_7,KC_8,KC_9,KC_0,KC_MINUS,
TD(TD_T),KC_R,KC_E,KC_W,KC_Q,KC_TAB,                        KC_Y,KC_U,KC_I,KC_O,KC_P,KC_BSPC,
KC_G,KC_F,KC_D,TD(TD_S),KC_A,CTL_CAP,                       KC_H,KC_J,KC_K,KC_L,KC_SCLN,CTL_QUO,
KC_RBRC,KC_B,TD(TD_V),TD(TD_C),KC_X,KC_Z,KC_LSHIFT,KC_GRAVE,   MO(1),KC_N,KC_M,KC_COMM,KC_DOT,TD(TD_SLASH),KC_ENT,KC_RSHIFT,
KC_LGUI,KC_LALT,KC_LBRC,KC_LCTRL,KC_SPACE,               KC_LEFT,KC_RIGHT,KC_SPACE,KC_UP,KC_EQUAL,KC_DOWN,
KC_MUTE,KC_NO,KC_NO,KC_NO,KC_NO,                         KC_MUTE,KC_NO,KC_NO,KC_NO,KC_NO
),

[_L1] = LAYOUT_elora_hlc(
KC_5,KC_4,KC_3,KC_2,KC_1,KC_ESC,                         KC_6,KC_7,KC_8,KC_9,KC_0,KC_ESC,
KC_Y,KC_P,KC_DOT,KC_COMM,KC_QUOTE,KC_TAB,                KC_F,KC_G,KC_C,KC_R,KC_L,KC_BSPC,
KC_I,KC_U,KC_E,KC_O,KC_A,LCTL_T(KC_ESC),                 KC_D,KC_H,KC_T,KC_N,KC_S,CTL_MIN,
KC_CAPSLOCK,KC_X,KC_K,KC_J,KC_Q,KC_SCLN,KC_LSHIFT,MO(3), MO(5),KC_B,KC_M,KC_W,KC_V,KC_Z,KC_RSHIFT,MO(4),
LALT_T(KC_ENTER),KC_LGUI,KC_LBRC,MO(6),KC_SPACE,         KC_RALT,KC_RGUI,KC_RBRC,KC_APPLICATION,KC_SPACE,
KC_MUTE,KC_NO,KC_NO,KC_NO,KC_NO,                         KC_MUTE,KC_NO,KC_NO,KC_NO,KC_NO
),

[_L2] = LAYOUT_elora_hlc(
KC_5,KC_4,KC_3,KC_2,KC_1,KC_ESC,                         KC_6,KC_7,KC_8,KC_9,KC_0,KC_ESC,
KC_B,KC_P,KC_F,KC_W,KC_Q,KC_TAB,                         KC_J,KC_L,KC_U,KC_Y,KC_SCLN,KC_BSPC,
KC_G,KC_T,KC_S,KC_R,KC_A,LCTL_T(KC_ESC),                 KC_M,KC_N,KC_E,KC_I,KC_O,CTL_QUO,
KC_CAPSLOCK,KC_V,KC_D,KC_C,KC_X,KC_Z,KC_LSHIFT,MO(3),    MO(5),KC_K,KC_H,KC_COMM,KC_DOT,KC_SLSH,KC_RSHIFT,MO(4),
LALT_T(KC_ENTER),KC_LGUI,KC_LBRC,MO(6),KC_SPACE,         KC_RALT,KC_RGUI,KC_RBRC,KC_APPLICATION,KC_SPACE,
KC_MUTE,KC_NO,KC_NO,KC_NO,KC_NO,                         KC_MUTE,KC_NO,KC_NO,KC_NO,KC_NO
),

[_L3] = LAYOUT_elora_hlc(
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,          KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,          KC_PGUP,KC_HOME,KC_UP,KC_END,KC_VOLU,KC_DEL,
KC_TRNS,KC_LSHIFT,KC_LCTRL,KC_LALT,KC_LGUI,KC_TRNS,       KC_PGDN,KC_LEFT,KC_DOWN,KC_RIGHT,KC_VOLD,KC_INS,
KC_SCROLLLOCK,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_PAUSE,KC_MPRV,KC_MPLY,KC_MNXT,KC_MUTE,KC_PSCR,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS
),

[_L4] = LAYOUT_elora_hlc(
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,          KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_GRAVE,KC_1,KC_2,KC_3,KC_4,KC_5,                       KC_6,KC_7,KC_8,KC_9,KC_0,KC_EQUAL,
LSFT(KC_GRAVE),LSFT(KC_1),LSFT(KC_2),LSFT(KC_3),LSFT(KC_4),LSFT(KC_5),
                                                       LSFT(KC_6),LSFT(KC_7),LSFT(KC_8),LSFT(KC_9),LSFT(KC_0),LSFT(KC_EQUAL),
KC_TRNS,KC_LBRC,KC_MINUS,KC_SCLN,LSFT(KC_SCLN),KC_BSLASH,LSFT(KC_BSLASH),KC_TRNS,
KC_TRNS,KC_RBRC,LSFT(KC_MINUS),KC_COMM,KC_DOT,KC_SLSH,LSFT(KC_SLSH),KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS
),

[_L5] = LAYOUT_elora_hlc(
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,          KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_F12,KC_F11,KC_F10,KC_F9,KC_TRNS,               KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_F8,KC_F7,KC_F6,KC_F5,KC_TRNS,                  KC_TRNS,KC_RSHIFT,KC_RCTRL,KC_LALT,KC_RGUI,KC_TRNS,
KC_TRNS,KC_TRNS,KC_F4,KC_F3,KC_F2,KC_F1,KC_TRNS,KC_TRNS,  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS
),

[_L6] = LAYOUT_elora_hlc(
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,          KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,DF(0),KC_TRNS,KC_TRNS,KC_TRNS,            KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,DF(1),KC_TRNS,KC_TRNS,KC_TRNS,            RM_TOGG,RM_SATU,RM_HUEU,RM_VALU,RM_NEXT,KC_TRNS,
KC_TRNS,KC_TRNS,DF(2),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,RM_SATD,RM_HUED,RM_VALD,RM_PREV,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS
),

};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
[0] = {
ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
ENCODER_CCW_CW(KC_PGUP, KC_PGDN),
ENCODER_CCW_CW(KC_PGUP, KC_PGDN)
}
};
#endif
