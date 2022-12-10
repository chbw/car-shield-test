/**
 * @file CarShield.h
 * @author Christoph B. Wurzinger (wu@htlweiz.at)
 * @brief Car-Shield constants
 * @version 0.1
 * @date 2022-12-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

// LED pins
const int LED_DIPPED_BEAM = 4;
const int LED_HIGH_BEAM = 3;
const int LED_TURN_RIGHT = 5;
const int LED_TURN_LEFT = 6;
const int LED_BREAK = 7;
const int LED_SPEED_INDICATOR = 10;

// Switch pins
const int SW_DIPPED_BEAM = A0;
const int SW_HIGH_BEAM = A2;
const int SW_LEFT = 8;
const int SW_RIGHT = A5;
const int SW_STOP = A4;
const int SW_ACCEL = A3;
const int SW_DECEL = A1;
