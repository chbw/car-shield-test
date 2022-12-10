/**
 * @file Blink.h
 * @author Christoph B. Wurzinger (wu@htlweiz.at)
 * @brief Peridially togggle a boolean value
 * @version 0.1
 * @date 2022-12-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <Arduino.h>

class Blink {
public:
  void begin(unsigned long period_ms) {
    _blinking = false;
    _state = false;
    _t_on = period_ms / 2;
    _t_off = period_ms - _t_on;
  }
  void begin(unsigned long t_on_ms, unsigned long t_off_ms) {
    _blinking = false;
    _state = false;
    _t_on = t_on_ms;
    _t_off = t_off_ms;
  }
  void start(bool initial_value = true) {
    _blinking = true;
    _state = initial_value;
    _start_time = millis();
  }
  void stop() {
    _blinking = false;
    _state = false;
  }
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
  void setBlinking(bool blinking) {
    if (!blinking) {
      stop();
    } else if (blinking && !_blinking) {
      start();
    }
  }
  bool isBlinking() { return _blinking; }
  bool getState() { return _state; }

private:
  bool _blinking, _state;
  unsigned long _start_time;
  unsigned long _t_on, _t_off;
};
