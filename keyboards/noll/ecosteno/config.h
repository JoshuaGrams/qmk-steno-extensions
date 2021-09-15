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

#define STENO_1UP
#define STENO_REPEAT

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED // recommended by QMK
#define PRODUCT_ID      0x3621 
#define DEVICE_VER      0x0100
#define MANUFACTURER    Noll Electronics LLC
#define PRODUCT         EcoSteno

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

#define MATRIX_COL_PINS { B15, B14, B13, B12, B1, B0, B9, B8, B7, B6, B5, B4 }
#define MATRIX_ROW_PINS { A15, B3, A7, A6 }
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define COMBO_COUNT 21
#define TAPPING_TERM 137
#define COMBO_TERM 35
#define FORCE_NKRO
