/* Copyright 2017 Joseph Wasson
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
#include "process_steno.h"
#include "quantum_keycodes.h"
#include "eeprom.h"
#include "keymap_steno.h"
#include "virtser.h"
#include <string.h>

// TxBolt Codes
#define TXB_NUL 0
#define TXB_S_L 0b00000001
#define TXB_T_L 0b00000010
#define TXB_K_L 0b00000100
#define TXB_P_L 0b00001000
#define TXB_W_L 0b00010000
#define TXB_H_L 0b00100000
#define TXB_R_L 0b01000001
#define TXB_A_L 0b01000010
#define TXB_O_L 0b01000100
#define TXB_STR 0b01001000
#define TXB_E_R 0b01010000
#define TXB_U_R 0b01100000
#define TXB_F_R 0b10000001
#define TXB_R_R 0b10000010
#define TXB_P_R 0b10000100
#define TXB_B_R 0b10001000
#define TXB_L_R 0b10010000
#define TXB_G_R 0b10100000
#define TXB_T_R 0b11000001
#define TXB_S_R 0b11000010
#define TXB_D_R 0b11000100
#define TXB_Z_R 0b11001000
#define TXB_NUM 0b11010000

#define TXB_GRP0 0b00000000
#define TXB_GRP1 0b01000000
#define TXB_GRP2 0b10000000
#define TXB_GRP3 0b11000000
#define TXB_GRPMASK 0b11000000

#define TXB_GET_GROUP(code) ((code & TXB_GRPMASK) >> 6)

#define BOLT_STATE_SIZE 4
#define GEMINI_STATE_SIZE 6
#define MAX_STATE_SIZE GEMINI_STATE_SIZE

static uint8_t      state[MAX_STATE_SIZE] = {0};
static uint8_t      chord[MAX_STATE_SIZE] = {0};
#ifdef STENO_1UP
static uint8_t      ignore[MAX_STATE_SIZE] = {0};
static bool         trigger               = false;
#endif
static int8_t       pressed               = 0;
//static steno_mode_t mode;

#ifdef STENO_REPEAT
#define MAX_REPEAT 8
#define BREAK_PERCENT 50
#define REPEAT_SPEED_PERCENT 400
#define STENO_MAX_AUTO_CHORDS_PER_SEC 50
#define STENO_MIN_MS_PER_AUTO_CHORD (1000 / STENO_MAX_AUTO_CHORDS_PER_SEC)
static uint8_t old_chords[MAX_REPEAT][MAX_STATE_SIZE];
static uint16_t press_times[MAX_REPEAT], per_repeat;
static uint16_t last_change, last_press;
static uint8_t o_first, o_count, o_last, o_repeat;

// Get the index of the nth entry in the circular buffer.
// (assumes n < MAX_REPEAT)
static uint8_t o_next(uint8_t n) {
    n += o_first;
    if(n >= MAX_REPEAT) {
        n -= MAX_REPEAT;
    }
    return n;
}

static void save_chord(void) {
    if (o_count == MAX_REPEAT) {
        o_last = o_first;
        o_first = o_next(1);
    } else {
        o_last = o_next(o_count);
        ++o_count;
    }
    memcpy(old_chords[o_last], chord, sizeof(chord));
    press_times[o_last] = last_press;
}

// Remove any history before a timing gap that's more than
// +/-BREAK_PERCENT off from the timing of the most recent
// two chords.
static void forget_before_pause(void) {
    const uint16_t per_stroke = last_press - press_times[o_last];
    // You have to have pressed another key after sending.
    if (per_stroke == 0) return;
    const uint16_t margin = per_stroke * BREAK_PERCENT / 100;
    for (uint8_t i=o_count; i>0; --i) {
        uint8_t c = o_next(i-1);
        uint16_t dt = last_press - press_times[c];
        if (dt < per_stroke - margin || dt > per_stroke + margin) {
            o_first = o_next(i);
            o_count -= i;
            break;
        }
        last_press = press_times[c];
    }
}

static bool find_loop(void) {
    for(uint8_t i=0; i<o_count; ++i) {
        uint8_t c = o_next(i);
        if(memcmp(state, old_chords[c], sizeof(state)) == 0) {
            o_first = c;
            o_count = o_count - i;
            return true;
        }
    }
    return false;
}
#endif

//static const uint8_t boltmap[64] PROGMEM = {TXB_NUL, TXB_NUM, TXB_NUM, TXB_NUM, TXB_NUM, TXB_NUM, TXB_NUM, TXB_S_L, TXB_S_L, TXB_T_L, TXB_K_L, TXB_P_L, TXB_W_L, TXB_H_L, TXB_R_L, TXB_A_L, TXB_O_L, TXB_STR, TXB_STR, TXB_NUL, TXB_NUL, TXB_NUL, TXB_STR, TXB_STR, TXB_E_R, TXB_U_R, TXB_F_R, TXB_R_R, TXB_P_R, TXB_B_R, TXB_L_R, TXB_G_R, TXB_T_R, TXB_S_R, TXB_D_R, TXB_NUM, TXB_NUM, TXB_NUM, TXB_NUM, TXB_NUM, TXB_NUM, TXB_Z_R};

static void steno_clear_state(void) {
    memset(state, 0, sizeof(state));
    memset(chord, 0, sizeof(chord));
}

static void send_steno_state(uint8_t size, bool send_empty) {
    for (uint8_t i = 0; i < size; ++i) {
        if (chord[i] || send_empty) {
#ifdef VIRTSER_ENABLE
            virtser_send(chord[i]);
#endif
        }
    }
}

void steno_init() {
    /*
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }
    mode = eeprom_read_byte(EECONFIG_STENOMODE);
    */
}

void steno_set_mode(steno_mode_t new_mode) {
    //steno_clear_state();
#ifdef STENO_1UP
    memset(ignore, 0, sizeof(ignore));
#endif
#ifdef STENO_REPEAT
    o_first = 0;
    o_count = 0;
    o_last = 0;
    o_repeat = 0;
    per_repeat = 0;
#endif
    //mode = new_mode;
    //eeprom_update_byte(EECONFIG_STENOMODE, mode);
}

/* override to intercept chords right before they get sent.
 * return zero to suppress normal sending behavior.
 */
__attribute__((weak)) bool send_steno_chord_user(steno_mode_t mode, uint8_t chord[6]) { return true; }

__attribute__((weak)) bool postprocess_steno_user(uint16_t keycode, keyrecord_t *record, steno_mode_t mode, uint8_t chord[6], int8_t pressed) { return true; }

__attribute__((weak)) bool process_steno_user(uint16_t keycode, keyrecord_t *record) { return true; }

static void send_steno_chord(void) {
    /*if (send_steno_chord_user(mode, chord)) {
        switch (mode) {
            case STENO_MODE_BOLT:
                send_steno_state(BOLT_STATE_SIZE, false);
#ifdef VIRTSER_ENABLE
                virtser_send(0);  // terminating byte
#endif
                break;
            case STENO_MODE_GEMINI:
                chord[0] |= 0x80;  // Indicate start of packet
                send_steno_state(GEMINI_STATE_SIZE, true);
                break;
        }
    }*/

    if (send_steno_chord_user(STENO_MODE_GEMINI, chord)) {
        chord[0] |= 0x80;  // Indicate start of packet
        send_steno_state(GEMINI_STATE_SIZE, true);
    }
    memset(chord, 0, sizeof(chord));
#ifdef STENO_1UP
    memcpy(ignore, state, sizeof(state));
#endif
steno_clear_state();
}

uint8_t *steno_get_state(void) { return &state[0]; }

uint8_t *steno_get_chord(void) { return &chord[0]; }

/*
static bool update_state_bolt(uint8_t key, bool press) {
    uint8_t boltcode = pgm_read_byte(boltmap + key);
    if (press) {
        state[TXB_GET_GROUP(boltcode)] |= boltcode;
        chord[TXB_GET_GROUP(boltcode)] |= boltcode;
    } else {
#ifdef STENO_1UP
        memcpy(chord, state, sizeof(state));
        trigger = !(ignore[TXB_GET_GROUP(boltcode)] & boltcode);
        ignore[TXB_GET_GROUP(boltcode)] &= ~boltcode;
#endif
        state[TXB_GET_GROUP(boltcode)] &= ~boltcode;
    }
    return false;
}
*/

static bool update_state_gemini(uint8_t key, bool press) {
    int     idx = key / 7;
    uint8_t bit = 1 << (6 - (key % 7));
    if (press) {
        state[idx] |= bit;
        chord[idx] |= bit;
    } else {
#ifdef STENO_1UP
        memcpy(chord, state, sizeof(state));
        trigger = !(ignore[idx] & bit);
        ignore[idx] &= ~bit;
#endif
        state[idx] &= ~bit;
    }
    return false;
}

bool process_steno(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        /*
        case QK_STENO_BOLT:
            if (!process_steno_user(keycode, record)) {
                return false;
            }
            if (IS_PRESSED(record->event)) {
                steno_set_mode(STENO_MODE_BOLT);
            }
            return false;
        */
        case QK_STENO_GEMINI:
            if (!process_steno_user(keycode, record)) {
                return false;
            }
            if (IS_PRESSED(record->event)) {
                steno_set_mode(STENO_MODE_GEMINI);
            }
            return false;

        case STN__MIN ... STN__MAX:
            if (!process_steno_user(keycode, record)) {
                return false;
            }

#ifdef STENO_REPEAT
            last_change = timer_read();
            if (IS_PRESSED(record->event)) {
                last_press = last_change;
            }
            per_repeat = 0;
#endif

            /*
            switch (mode) {
                case STENO_MODE_BOLT:
                    update_state_bolt(keycode - QK_STENO, IS_PRESSED(record->event));
                    break;
                case STENO_MODE_GEMINI:
                    update_state_gemini(keycode - QK_STENO, IS_PRESSED(record->event));
                    break;
            }
            */
            update_state_gemini(keycode - QK_STENO, IS_PRESSED(record->event));

            // allow postprocessing hooks
         // if (postprocess_steno_user(keycode, record, mode, chord, pressed)) {
            if (postprocess_steno_user(keycode, record, STENO_MODE_GEMINI, chord, pressed)) {
                if (IS_PRESSED(record->event)) {
                    ++pressed;
                } else {
                    --pressed;
                    if (pressed <= 0) {
                        pressed = 0;
#ifndef STENO_1UP
#ifdef STENO_REPEAT
                        save_chord();
#endif
                        send_steno_chord();
#endif
                    }
#ifdef STENO_1UP
                    if (trigger) {
#ifdef STENO_REPEAT
                        save_chord();
#endif
                        send_steno_chord();
                    }
                    if (trigger) {
                        send_steno_chord();
                    }
#endif
                }
            }
            return false;
    }
    return true;
}

#ifdef STENO_REPEAT
void steno_task(void) {
    if (pressed > 0 && o_count > 0) {
        const uint16_t hold = timer_elapsed(last_change);
        const uint16_t gap = last_press - press_times[o_last];
        if (per_repeat == 0 && hold >= gap) {
            // Not repeating: should we start?
            forget_before_pause();
            if (find_loop()) {
                o_repeat = 0;
                per_repeat = gap * 100 / REPEAT_SPEED_PERCENT;
                if (per_repeat < STENO_MIN_MS_PER_AUTO_CHORD) {
                    per_repeat = STENO_MIN_MS_PER_AUTO_CHORD;
                }
#ifdef STENO_1UP
                memcpy(ignore, state, sizeof(state));
#endif
            }
        }
        if (per_repeat != 0 && hold >= per_repeat) {
            // Repeating: time to send the next chord.
            memcpy(chord, old_chords[o_next(o_repeat)], sizeof(chord));
            send_steno_chord();
            ++o_repeat;
            if (o_repeat == o_count) {
                o_repeat = 0;
            }
            last_change = timer_read();
        }
    }
}
#endif
