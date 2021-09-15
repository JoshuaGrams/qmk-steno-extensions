/* Copyright 2021 Nathan Olivares
 * 
 * This program is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation, either version 2 of the License, or 
 * (at your option) any later version. 
 * 
 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * GNU General Public License for more details. 
 * 
 * You should have received a copy of the GNU General Public License 
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 */

#include "keymap_steno.h"
#include QMK_KEYBOARD_H

enum layers{
  STENO,
  NKRO,
  QWERTY,
  SYMBOL
};

enum combo_events {
  Q_A,
  Q_S,
  Q_D,
  Q_F,
  Q_G,
  Q_H,
  Q_J,
  Q_K,
  Q_L,
  Q_SCLN,
  Q_ENTER,
  Q_ONE,
  Q_TWO,
  Q_THREE,
  Q_FOUR,
  Q_FIVE,
  Q_SIX,
  Q_SEVEN,
  Q_EIGHT,
  Q_NINE,
  Q_ZERO
};

const uint16_t PROGMEM Qwerty_A[] = {KC_Q, KC_Z, COMBO_END};
const uint16_t PROGMEM Qwerty_S[] = {KC_W, KC_X, COMBO_END};
const uint16_t PROGMEM Qwerty_D[] = {KC_E, KC_C, COMBO_END};
const uint16_t PROGMEM Qwerty_F[] = {KC_R, KC_V, COMBO_END};
const uint16_t PROGMEM Qwerty_G[] = {KC_T, KC_B, COMBO_END};
const uint16_t PROGMEM Qwerty_H[] = {KC_Y, KC_N, COMBO_END};
const uint16_t PROGMEM Qwerty_J[] = {KC_U, KC_M, COMBO_END};
const uint16_t PROGMEM Qwerty_K[] = {KC_I, KC_COMM, COMBO_END};
const uint16_t PROGMEM Qwerty_L[] = {KC_O, KC_DOT, COMBO_END};
const uint16_t PROGMEM Qwerty_SCLN[] = {KC_P, KC_SLASH, COMBO_END};
const uint16_t PROGMEM Qwerty_ENTER[] = {KC_QUOT, KC_RSHIFT, COMBO_END};

const uint16_t PROGMEM Qwerty_ONE[] = {KC_Q, KC_TAB, COMBO_END};
const uint16_t PROGMEM Qwerty_TWO[] = {KC_W, KC_TAB, COMBO_END};
const uint16_t PROGMEM Qwerty_THREE[] = {KC_E, KC_ESC, COMBO_END};
const uint16_t PROGMEM Qwerty_FOUR[] = {KC_R, KC_ESC, COMBO_END};
const uint16_t PROGMEM Qwerty_FIVE[] = {KC_T, KC_ESC, COMBO_END};
const uint16_t PROGMEM Qwerty_SIX[] = {KC_Y, KC_ENTER, COMBO_END};
const uint16_t PROGMEM Qwerty_SEVEN[] = {KC_U, KC_ENTER, COMBO_END};
const uint16_t PROGMEM Qwerty_EIGHT[] = {KC_I, KC_ENTER, COMBO_END};
const uint16_t PROGMEM Qwerty_NINE[] = {KC_O, KC_BSPC, COMBO_END};
const uint16_t PROGMEM Qwerty_ZERO[] = {KC_P, KC_BSPC, COMBO_END};


combo_t key_combos[COMBO_COUNT] = {
  [Q_A] = COMBO_ACTION(Qwerty_A),
  [Q_S] = COMBO_ACTION(Qwerty_S),
  [Q_D] = COMBO_ACTION(Qwerty_D),
  [Q_F] = COMBO_ACTION(Qwerty_F),
  [Q_G] = COMBO_ACTION(Qwerty_G),
  [Q_H] = COMBO_ACTION(Qwerty_H),
  [Q_J] = COMBO_ACTION(Qwerty_J),
  [Q_K] = COMBO_ACTION(Qwerty_K),
  [Q_L] = COMBO_ACTION(Qwerty_L),
  [Q_SCLN] = COMBO_ACTION(Qwerty_SCLN),
  [Q_ENTER] = COMBO_ACTION(Qwerty_ENTER),
  [Q_ONE] = COMBO_ACTION(Qwerty_ONE),
  [Q_TWO] = COMBO_ACTION(Qwerty_TWO),
  [Q_THREE] = COMBO_ACTION(Qwerty_THREE),
  [Q_FOUR] = COMBO_ACTION(Qwerty_FOUR),
  [Q_FIVE] = COMBO_ACTION(Qwerty_FIVE),
  [Q_SIX] = COMBO_ACTION(Qwerty_SIX),
  [Q_SEVEN] = COMBO_ACTION(Qwerty_SEVEN),
  [Q_EIGHT] = COMBO_ACTION(Qwerty_EIGHT),
  [Q_NINE] = COMBO_ACTION(Qwerty_NINE),
  [Q_ZERO] = COMBO_ACTION(Qwerty_ZERO)
};

void process_combo_event(uint16_t combo_index, bool pressed){
  if(pressed){
    switch(combo_index) {
      case Q_A:
        if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_A);
        }
        break;
      case Q_S:
        if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_S);
        }
        break;
      case Q_D:
        if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_D);
        }
        break;
      case Q_F:
        if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_F);
        }
        break;
      case Q_G:
        if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_G);
        }
        break;
      case Q_H:
        if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_H);
        }
        break;
      case Q_J:
        if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_J);
        }
        break;
      case Q_K:
        if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_K);
        }
        break;
      case Q_L:
        if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_L);
        }
        break;
      case Q_SCLN:
        if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_SCLN);
        }
        break;
      case Q_ENTER:
        if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_ENTER);
        }
        break;
      case Q_ONE:
        if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_1);
        }
        break;
      case Q_TWO:
        if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_2);
        }
        break;
      case Q_THREE:
        if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_3);
        }
        break;
      case Q_FOUR:
        if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_4);
        }
        break;
      case Q_FIVE:
        if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_5);
        }
        break;
      case Q_SIX:
        if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_6);
        }
        break;
      case Q_SEVEN:
        if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_7);
        }
        break;
      case Q_EIGHT:
        if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_8);
        }
        break;
      case Q_NINE:
        if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_9);
        }
        break;
      case Q_ZERO:
        if (IS_LAYER_ON(QWERTY)){
          tap_code16(KC_0);
        }
        break;
    }
  }
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [STENO] = LAYOUT(
                STN_N2,         STN_N4,                                     STN_N8,         STN_NA,      
    TO(NKRO),   STN_S1, STN_TL, STN_PL, STN_HL, STN_ST1,   STN_ST3, STN_FR, STN_PR, STN_LR, STN_TR, STN_DR,
    MO(SYMBOL), STN_S2, STN_KL, STN_WL, STN_RL, STN_ST2,   STN_ST4, STN_RR, STN_BR, STN_GR, STN_SR, STN_ZR,
                                        STN_A,  STN_O,     STN_E,  STN_U 
  ),

  [NKRO] = LAYOUT(
                KC_2,       KC_4,                           KC_8,       KC_0,
    TO(QWERTY), KC_Q, KC_W, KC_E, KC_R, KC_T,   KC_Y, KC_U, KC_I, KC_O, KC_P,    KC_LBRC,
    MO(SYMBOL), KC_A, KC_S, KC_D, KC_F, KC_G,   KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
                                  KC_C, KC_V,   KC_N, KC_M 
  ),

  [QWERTY] = LAYOUT(
                KC_TAB,         KC_ESC,                                KC_ENTER,        KC_BSPC,
    TO(STENO),  KC_Q,   KC_W,   KC_E, KC_R,    KC_T,       KC_Y, KC_U, KC_I,    KC_O,   KC_P,     KC_QUOT,
    MO(SYMBOL), KC_Z,   KC_X,   KC_C, KC_V,    KC_B,       KC_N, KC_M, KC_COMM, KC_DOT, KC_SLASH, KC_RSHIFT,
                                      KC_LCTL, KC_SPACE,   KC_SPACE, KC_RALT 
  ),

  [SYMBOL] = LAYOUT(
             KC_HASH,          KC_DOLLAR,                                       KC_LPRN,            KC_RPRN,
    _______, KC_EXLM, KC_AT,   KC_LT,   KC_GT,   KC_BSLASH,  KC_DQT,   KC_PLUS, KC_MINS,  KC_SLASH, KC_ASTR, KC_TAB, 
    _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_GRAVE,   KC_MINS,  KC_AMPR, KC_EQUAL, KC_COMM,  KC_DOT,  KC_RSHIFT,
                                        KC_SCLN, KC_SPACE,   KC_SPACE, KC_SLASH 
  )
};

void matrix_init_user(void) {
  steno_set_mode(STENO_MODE_BOLT); // STENO_MODE_GEMINI or STENO_MODE_BOLT
};

layer_state_t layer_state_set_user(layer_state_t state) {
    // or uint8_t layer = get_highest_layer(state);
    switch (get_highest_layer(state)) {
        case (STENO):
          //green LED on
          palSetPad(GPIOA, 1);
          // red LED off
          palClearPad(GPIOA, 0);
          break;
        case (QWERTY):
          combo_enable();
          // red LED on
          palSetPad(GPIOA, 0);
          // green LED off
          palClearPad(GPIOA, 1);
          break;
        case (NKRO): 
          combo_disable();
          palClearPad(GPIOA, 1);
          palClearPad(GPIOA, 0);
          break;
        case (SYMBOL):
          // both LEDs on for Symbol
          combo_disable();
          palSetPad(GPIOA, 1);
          palSetPad(GPIOA, 0);
          break;
        default:
          // shouldn't happen but just in case
          combo_disable();
          palClearPad(GPIOA, 1);
          palClearPad(GPIOA, 0);
          break;
    }

    return state;
}