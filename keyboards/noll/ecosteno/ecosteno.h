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
 
#pragma once

#include "quantum.h"

#define LAYOUT( \
	             K02,        K04,                    K08,        K0A,       \
     K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B, \
	 K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B, \
                             K34,  K35,  K36,  K37                          \
) { \
    {KC_NO, KC_NO, K02,   KC_NO, K04, KC_NO, KC_NO, KC_NO, K08,   KC_NO, K0A,   KC_NO}, \
    {K10,   K11,   K12,   K13,   K14, K15,   K16,   K17,   K18,   K19,   K1A,   K1B},   \
    {K20,   K21,   K22,   K23,   K24, K25,   K26,   K27,   K28,   K29,   K2A,   K2B},   \
    {KC_NO, KC_NO, KC_NO, KC_NO, K34, K35,   K36,   K37,   KC_NO, KC_NO, KC_NO, KC_NO}  \
}

// we dont want open drain, we want push pull(?)
// pal.h, 7U is open drain, 6U is push pull
// but it doesn't seem to affect anything here, works in keyboard.c though
//#define GPIOA_PIN0  6U  // open drain 
//#define GPIOA_PIN1  6U  // open drain