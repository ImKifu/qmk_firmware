#include QMK_KEYBOARD_H

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _COLEMAK,
    _QWERTY,
    _LOWER,
    _RAISE,
};

enum custom_keycodes {
    KC_COLEMAK = SAFE_RANGE,
    KC_QWERTY,
    KC_PRVWD,
    KC_NXTWD,
    KC_LSTRT,
    KC_LEND,
    KC_DLINE
};

// Define a type for as many tap dance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    /*
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD,
    TD_TRIPLE_SINGLE_TAP, // Send three single taps
    */
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum tap_dance_codes {
    Q_ESC = 0,
    SCLN,
    //J_CW, 
    BSPC_LAYR,
    LPRN_LABK,
    RPRN_RABK,
    GRV_TILD,
};

// Function associated with all tap dances
td_state_t cur_dance(tap_dance_state_t *state);

// Functions associated with individual tap dances
void bl_finished(tap_dance_state_t *state, void *user_data);
void bl_reset(tap_dance_state_t *state, void *user_data);
void dance_jcw_finished(tap_dance_state_t *state, void *user_data);
void dance_jcw_reset (tap_dance_state_t *state, void *user_data);

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),           ENCODER_CCW_CW(KC_PGDN, KC_PGUP) },
    [1] = { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______) },
    [2] = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI),           ENCODER_CCW_CW(RGB_SAD, RGB_SAI) },
    [3] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI),           ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)}
};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * COLEMAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   Q  |   W  |   F  |   P  |   B  |                    |   J  |   L  |   U  |   Y  |   ;  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   A  |   R  |   S  |   T  |   G  |-------.    ,-------|   M  |   N  |   E  |   I  |   O  |      |
 * |------+------+------+------+------+------|  MUTE |    | MACWN |------+------+------+------+------+------|
 * |      |   Z  |   X  |   C  |   D  |   V  |-------|    |-------|   K  |   H  |   ,  |   .  |   /  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |LOWER | / Enter /       \Space \  |RAISE |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *             `----------------------------------'           '------''---------------------------'
 */
[_COLEMAK] = LAYOUT(
  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
  KC_NO,   TD(Q_ESC), KC_W, KC_F,    KC_P,    KC_B,                               KC_J,    KC_L,    KC_U,    KC_Y,    TD(SCLN),KC_NO,  
  KC_NO,   KC_A,   KC_R,    KC_S,    KC_T,    KC_G,                               KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_NO,  
  KC_NO,   MT(MOD_LSFT, KC_Z), KC_X, KC_C,    KC_D, KC_V,  KC_MUTE,     CG_TOGG,  KC_K,    KC_H,    KC_COMM, KC_DOT,  MT(MOD_LSFT, KC_SLSH), KC_NO,  
           KC_QWERTY, KC_NO,   KC_NO,   LT(2, KC_TAB), MT(MOD_LCTL, KC_ENT), KC_SPC, TD(BSPC_LAYR), KC_NO,   KC_NO,   KC_NO
),
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   5  |   1  |   2  |   3  |   4  |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   P  |   J  |   Q  |   W  |   E  |   R  |                    |      |   7  |   8  |   9  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   G  |   T  |   A  |   S  |   D  |   F  |-------.    ,-------|      |   4  |   5  |   6  |      |      |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |   M  | LCTR |   Z  |   X  |   C  |   V  |-------|    |-------|   0  |   1  |   2  |   3  |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | CLMK | WIN  |   L  | Tab  | / Space /       \      \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *             `----------------------------------'           '------''---------------------------'
 */
[_QWERTY] = LAYOUT(
  KC_ESC,  KC_5,    KC_1,    KC_2,    KC_3,    KC_4,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
  KC_P  ,  KC_J,    KC_Q,    KC_W,    KC_E,    KC_R,                              KC_NO,   KC_7,    KC_8,    KC_9,    KC_NO,   KC_NO,  
  KC_G,    KC_T,    KC_A,    KC_S,    KC_D,    KC_F,                              KC_NO,   KC_4,    KC_5,    KC_6,    KC_NO,   KC_NO,  
  KC_M,    KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,     KC_MUTE,       KC_NO,    KC_0,    KC_1,    KC_2,    KC_3,    KC_NO,   KC_NO,  
                    KC_COLEMAK, KC_LGUI, KC_ENT, KC_TAB, KC_SPC,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   $  |  (<  |  >)  |   '  |   +  |                    |   *  |   7  |   8  |   9  |   %  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   @  |   {  |  }   |   "  |   =  |-------.    ,-------|   !  |   4  |   5  |   6  |   ^  |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |   #  |   [  |  ]   |   |  |   &  |-------|    |-------|   0  |   1  |   2  |   3  |   \  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |LOWER | /  ~`   /       \   _  \  |   -  |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *             `----------------------------------'           '------''---------------------------'
 */
[_LOWER] = LAYOUT(
  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
  KC_NO,   KC_DLR,  TD(LPRN_LABK), TD(RPRN_RABK), KC_QUOT, KC_PLUS,               KC_ASTR, KC_7,    KC_8,    KC_9,    KC_PERC, KC_NO,  
  KC_NO,   KC_AT,   KC_LCBR, KC_RCBR, KC_DQUO, KC_EQL,                            KC_EXLM, KC_4,    KC_5,    KC_6,    KC_CIRC, KC_NO,  
  KC_NO,   KC_HASH, KC_LBRC, KC_RBRC, KC_PIPE, KC_AMPR,  KC_NO,         KC_NO,    KC_0   , KC_1,    KC_2,    KC_3,    KC_BSLS, KC_NO,  
                    KC_NO,   KC_NO,   KC_NO,   KC_NO,   TD(GRV_TILD),    KC_UNDS, KC_MINS, KC_NO,   KC_NO,   KC_NO
),
/* RAISE
 * ,----------------------------------------.                     ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | F10  |  F7  |  F4  |  F1  |                    | PGUP | PWrd |  Up  | NWrd |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | F11  |  F8  |  F5  |  F2  |-------.    ,-------| PGDN | Left | Down | Rigth|      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      | F12  |  F9  |  F6  |  F3  |-------|    |-------|      | LStr |      | LEnd |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |CtrlWN| /       /       \      \  | RAISE|      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *             `----------------------------------'           '------''---------------------------'
 */
[_RAISE] = LAYOUT(
  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
  KC_NO,   KC_NO,   KC_F10,  KC_F7,   KC_F4,   KC_F1,                             KC_PGUP, KC_PRVWD,  KC_UP, KC_NXTWD,KC_NO,   KC_NO,  
  KC_NO,   KC_NO,   KC_F11,  KC_F8,   KC_F5,   KC_F2,                             KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_NO,  
  KC_NO,   KC_NO,   KC_F12,  KC_F9,   KC_F6,   KC_F3,  KC_NO,           KC_NO,    KC_NO,   KC_LSTRT,KC_NO,   KC_LEND, KC_NO,   KC_NO,  
                    KC_NO,   KC_NO,   KC_NO, MT(MOD_LCTL | MOD_LGUI, KC_NO), KC_NO,           KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
),
};

#ifdef OLED_ENABLE
/*
static void render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,128,  0,  0,  0,192,224,240,240,240,240,240,240,240,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,112,112,112,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,224,240,  0,  0,240,252,254,255,255,255,  1,240,252,255,255,255,255,255,255,255,255,127, 31,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,254,254,  0,  0,240,248,252, 30, 14, 14, 14, 14, 14, 14, 30,252,248,240,  0,  0,254,254,252, 28, 14, 14, 14, 14,  0,  0,254,254,252, 28, 14, 14, 14, 14, 30,252,248,240,  0,  0,240,248,252,222,206,206,206,206,206,206,222,252,248,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,255,255,254,240,255,255,255,255,255,255,248,255,255,255,255,255,255,255,255,255,193,128,128,128,192,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,255,255,255,  0,  0, 15, 31, 63,120,112,112,112,112,112,112,120, 63, 31, 15,  0,  0,127,127,127,  0,  0,  0,  0,  0,  0,  0,127,127,127,  0,  0,  0,  0,  0,  0,127,127,127,  0,  0, 15, 31, 63,121,113,113,113,113,113,113,121, 61, 29, 13,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  3,  3,  3,  3,  1,  1,  3,  3,  7,  7,  7,  3,  3,  1,  3,  7,  7,  7,  7,  7,  7,  7,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7,  7,  7,  7,  7,  7,  7,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}
*/
static void render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,252,254,255, 15,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  0,  0,  0,  0,  0,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,255,255,255,  7,  7,  7,  7,  7,  7,  7,  7,255,255,255,  0,  0,  0,  0,  0,255,255,255,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,255,255,255,  0,  0,  0,  0,  0,  7,  7,  7,  7,135,199,231,247,255,127, 63, 31, 15, 31, 63,127,247,231,199,135,  7,  7,  7,  7,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0, 31, 63,127,120,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15, 15, 15,  0,  0,  0,  0,  0,  0,  0,  0,127,127,127,  0,  0,  0,  0,  0,  7,  7,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7,  7,  0,  0,  0,  0,  0,248,124, 62, 31, 15,  7,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  3,  7, 15, 30, 60,120,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}


static void print_status_narrow(void) {
    // Print current mode
    //oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("MODE"), false);
    oled_write_ln_P(PSTR(""), false);
    if (keymap_config.swap_lctl_lgui) {
        oled_write_ln_P(PSTR("Mac"), false);
    } else {
        oled_write_ln_P(PSTR("Win"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    switch (get_highest_layer(default_layer_state)) {
        case _COLEMAK:
            oled_write_ln_P(PSTR("KIFU"), false);
            break;
        case _QWERTY:
            oled_write_ln_P(PSTR("GAME"), true);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
        case _COLEMAK:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
    return false;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case KC_COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
        case KC_PRVWD:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_LEFT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                }
            }
            break;
        case KC_NXTWD:
             if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_RIGHT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                }
            }
            break;
        case KC_LSTRT:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                     //CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                } else {
                    register_code(KC_HOME);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_code(KC_HOME);
                }
            }
            break;
        case KC_LEND:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    //CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                } else {
                    register_code(KC_END);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_code(KC_END);
                }
            }
            break;
        case KC_DLINE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_BSPC);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_BSPC);
            }
            break;
        case KC_COPY:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_C);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_C);
            }
            return false;
        case KC_PASTE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_V);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_V);
            }
            return false;
        case KC_CUT:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_X);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_X);
            }
            return false;
            break;
        case KC_UNDO:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_Z);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_Z);
            }
            return false;
    }
    return true;
}

/*
    * Custom Macros
    * Check here to generate your own macros: https://codepen.io/mvaneijgen/full/LYEVQXp
*/
enum combos { 
  W_F_P_LGUI,
  L_U_Y_RGUI,
  A_R_S_LALT,
  T_A_S_LALT,
  E_I_O_RALT,
  R_S_T_DEL,
  N_E_I_BSPC,
  
};

const uint16_t PROGMEM w_f_p_lgui[] = { KC_W, KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM l_u_y_rgui[] = { KC_L, KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM a_r_s_lalt[] = { KC_A, KC_R, KC_S, COMBO_END};
const uint16_t PROGMEM t_a_s_lalt[] = { KC_T, KC_A, KC_S, COMBO_END};
const uint16_t PROGMEM e_i_o_ralt[] = { KC_E, KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM r_s_t_del[] = { KC_R, KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM n_e_i_bspc[] = { KC_N, KC_E, KC_I, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [W_F_P_LGUI] = COMBO(w_f_p_lgui, KC_LGUI),
  [L_U_Y_RGUI] = COMBO(l_u_y_rgui, KC_RGUI),
  [A_R_S_LALT] = COMBO(a_r_s_lalt, KC_LALT),
  [T_A_S_LALT] = COMBO(t_a_s_lalt, KC_LALT),
  [E_I_O_RALT] = COMBO(e_i_o_ralt, KC_RALT),
  [R_S_T_DEL] = COMBO(r_s_t_del, KC_DEL),
  [N_E_I_BSPC] = COMBO(n_e_i_bspc, KC_BSPC),
  
};
/*
    End Custom Macros
*/




/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */

// Determine the current tap dance state
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } /*else if (state->count == 2) return TD_DOUBLE_TAP;*/
    else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t bl_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does

// Send 'Ctrl Backspace' on Single Tap, 'Raise Layer' on Single Hold, 'Toggle Raise Layer' on Double Tap
void bl_finished(tap_dance_state_t *state, void *user_data) {
    bl_tap_state.state = cur_dance(state);
    switch (bl_tap_state.state) {
        case TD_UNKNOWN:
            tap_code16(C(KC_BSPC));
            break;
        case TD_SINGLE_TAP:
            tap_code16(C(KC_BSPC));
            break;
        case TD_SINGLE_HOLD:
            layer_on(_RAISE);
            break;
        /*
        case TD_DOUBLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(_RAISE)) {
                // If already set, then switch it off
                layer_off(_RAISE);
            } else {
                // If not already set, then switch the layer on
                layer_on(_RAISE);
            }
            break;
        */
        default:
            break;
    }
}

void bl_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (bl_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_RAISE);
    }
    bl_tap_state.state = TD_NONE;
}
// End send 'Ctrl Backspace' on Single Tap, 'Raise Layer' on Single Hold, 'Toggle Raise Layer' on Double Tap


// Send 'J' on Single Tap, 'Caps Word' on Double Tap (currently not working) (issue can be found here: https://github.com/qmk/qmk_firmware/issues/19574)
/*
void dance_jcw_finished (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_J);
  } else {
    caps_word_toggle();
  }
}

void dance_jcw_reset (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_J);
  } else {
    caps_word_toggle();
  }
}
*/
// End send 'J' on Single Tap, 'Caps Word' on Double Tap





// Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    [Q_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC),
    [SCLN]  = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, S(KC_SCLN)),
    //[J_CW]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_jcw_finished, dance_jcw_reset), // currently not working
    [BSPC_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, bl_finished, bl_reset),
    [LPRN_LABK] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_LABK),
    [RPRN_RABK] = ACTION_TAP_DANCE_DOUBLE(KC_RPRN, KC_RABK),
    [GRV_TILD] = ACTION_TAP_DANCE_DOUBLE(KC_GRV, KC_TILD),
};

// Set a long-ish tapping term for tap-dance keys
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            return 275;
        default:
            return TAPPING_TERM;
    }
}

