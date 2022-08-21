// Copyright 2022 Mark Hellewell (@markhellewell)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _RSE,
    _FN,
    _LWR,
    _SCROLLMOD
};

enum custom_keycodes {
    KVMSWITCH_1,
    KVMSWITCH_2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BACKSPACE,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BACKSLASH,
        KC_ESCAPE, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SEMICOLON, KC_QUOTE,
        KC_LEFT_SHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_SFTENT,
        KC_LEFT_CTRL, KC_LEFT_GUI, KC_LEFT_ALT, MO(_FN), MO(_LWR), KC_SPACE, MO(_RSE), KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,
        KC_AUDIO_MUTE, MO(_SCROLLMOD)
    ),
    [_RSE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DELETE,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, KC_MINUS, KC_EQUAL, KC_LEFT_BRACKET, KC_RIGHT_BRACKET, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,     _______     , _______, KC_HOME, KC_PAGE_DOWN, KC_PAGE_UP, KC_END,
        _______, _______
    ),
    [_FN] = LAYOUT(
        _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
        KC_F12,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,     _______     , _______, _______, _______, _______, _______,
        _______, _______
    ),
    [_LWR] = LAYOUT(
        _______, KVMSWITCH_1, KVMSWITCH_2, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        RESET, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,     _______     , _______, _______, _______, _______, _______,
        _______, _______
    ),
    [_SCROLLMOD] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,     _______     , _______, _______, _______, _______, _______,
        _______, _______
    ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            if (IS_LAYER_ON(_SCROLLMOD)) {
                tap_code_delay(KC_MS_WH_RIGHT, 10);
            } else {
                tap_code_delay(KC_MS_WH_UP, 10);
            }
        } else {
            if (IS_LAYER_ON(_SCROLLMOD)) {
                tap_code_delay(KC_MS_WH_LEFT, 10);
            } else {
                tap_code_delay(KC_MS_WH_DOWN, 10);
            }
        }
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KVMSWITCH_1:
            if (record->event.pressed) {
                // when keycode KVMSWITCH_1 is pressed
                SEND_STRING(SS_TAP(X_LCTRL) SS_DELAY(80) SS_TAP(X_LCTRL) SS_DELAY(80) SS_TAP(X_KP_1));
            }
            break;

        case KVMSWITCH_2:
            if (record->event.pressed) {
                // when keycode KVMSWITCH_2 is pressed
                SEND_STRING(SS_TAP(X_LCTRL) SS_DELAY(80) SS_TAP(X_LCTRL) SS_DELAY(80) SS_TAP(X_KP_2));
            }
            break;
    }
    return true;
};

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    render_logo();
    switch (get_highest_layer(layer_state)) {
        case _SCROLLMOD:
            oled_write_ln_P(PSTR("\n\n\n        SCROLLMOD"), false);
            break;
        case _LWR:
            oled_write_ln_P(PSTR("\n\n\n        LWR"), false);
            break;
        case _FN:
            oled_write_ln_P(PSTR("\n\n\n        FN"), false);
            break;
        case _RSE:
            oled_write_ln_P(PSTR("\n\n\n        RSE"), false);
            break;
        default:
            oled_write_ln_P(PSTR("\n\n\n        DEFAULT"), false);
    }
    return false;
}
#endif