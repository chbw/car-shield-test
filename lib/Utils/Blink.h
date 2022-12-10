/**
 * @file Blink.h
 * @author Christoph B. Wurzinger (wu@htlweiz.at)
 * @brief Peridically togggle a boolean value
 * @version 0.1
 * @date 2022-12-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <Arduino.h>

/**
 * @brief Periodically togggle a boolean value.
 *
 */
class Blink {
public:
  /**
   * @brief Initialize
   *
   * @param period_ms The period. The resulting signal is true for period_ms/2
   * and false for the rest of the period.
   */
  void begin(unsigned long period_ms) {
    _blinking = false;
    _state = false;
    _t_on = period_ms / 2;
    _t_off = period_ms - _t_on;
  }
  /**
   * @brief Initialize
   *
   * @param t_on_ms The resulting signal is true for this amount of time.
   * @param t_off_ms The resulting signal is false for this amount of time.
   */
  void begin(unsigned long t_on_ms, unsigned long t_off_ms) {
    _blinking = false;
    _state = false;
    _t_on = t_on_ms;
    _t_off = t_off_ms;
  }
  /**
   * @brief Start the toggling. Calling this method will reset the internal
   * timing.
   *
   * @param initial_value Whether to start with the signal on/true of off/false.
   */
  void start(bool initial_value = true) {
    _blinking = true;
    _state = initial_value;
    _start_time = millis();
  }
  /**
   * @brief Stop the toggling.
   *
   */
  void stop() {
    _blinking = false;
    _state = false;
  }
  /**
   * @brief Update. Call periodically to update the signal.
   *
   */
  void update() {
    if (!_blinking)
      return;
    unsigned long now = millis();
    if (_state && ((now - _start_time) >= _t_on)) {
      _state = false;
      _start_time = _start_time + _t_on;
    }
    if (!_state && ((now - _start_time) >= _t_off)) {
      _state = true;
      _start_time = _start_time + _t_off;
    }
  }
  /**
   * @brief Set the toggling mode. setBlinking(false) is equal to stop().
   * setBlinking(true) after a call to start() will not reset the internal
   * timing.
   *
   * @param blinking Wheter or not the signal should toggle or not.
   */
  void setBlinking(bool blinking) {
    if (!blinking) {
      stop();
    } else if (blinking && !_blinking) {
      start();
    }
  }
  /**
   * @brief Check if the state could be toggling.
   *
   * @return true
   * @return false
   */
  bool isBlinking() { return _blinking; }
  /**
   * @brief Get the (blinking/toggling) signal value.
   *
   * @return true
   * @return false
   */
  bool getState() { return _state; }

private:
  /**
   * @brief Whether or not toggling/blinking is enabled.
   *
   */
  bool _blinking;
  /**
   * @brief Current signal value
   *
   */
  bool _state;
  /**
   * @brief Time of last signal change.
   *
   */
  unsigned long _start_time;
  /**
   * @brief How long the signal should stay high/true.
   *
   */
  unsigned long _t_on;
  /**
   * @brief How long the signal should stay low/false.
   *
   */
  unsigned long _t_off;
};
