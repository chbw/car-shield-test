/**
 * @file Integrate.h
 * @author Christoph B. Wurzinger (wu@htlweiz.at)
 * @brief Integrate a signal over time using the Trapezoidal rule.
 * @version 0.1
 * @date 2022-12-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <Arduino.h>

/**
 * @brief Integrate a signal over time using the Trapezoidal rule.
 * All calculations are done using integer maths and milli seconds.
 */
class Integrate {
public:
  /**
   * @brief Initialize.
   *
   * @param value Starting value for the Trapezoidal rule.
   */
  void begin(long value = 0) {
    _state = 0;
    _last_time = millis();
    _last_value = value;
  }
  /**
   * @brief Integrate the signal. If less than 1ms (time base resolution) has
   * passed, it will be ignored.
   *
   * @param value Value to integrate.
   */
  void update(long value = 1) {
    long now = millis();
    if (now == _last_time) {
      return;
    }
    _state += (_factor * (value + _last_value) * (now - _last_time)) / 2;
    _last_time = now;
    _last_value = value;
  }
  /**
   * @brief Coerce the integrated value (optional).
   *
   * @param lower_bound Lower bound in [value units]*[milli seconds]
   * @param upper_bound Upper bound in [value units]*[milli seconds]
   */
  void coerce(long lower_bound = 0, long upper_bound = 65280) {
    if (_state > upper_bound * _factor) {
      _state = upper_bound * _factor;
    }
    if (_state < lower_bound * _factor) {
      _state = lower_bound * _factor;
    }
  }
  /**
   * @brief Get the integrated signal.
   *
   * @return long
   */
  long getState() { return _state / _factor; }

private:
  /**
   * @brief Integrated signal times _factor.
   *
   */
  long _state;
  /**
   * @brief The internal state is kept time this factor (2). If this was 1,
   * integrating a signal of value 1 would yield 0 due to integer round-off.
   *
   */
  const long _factor = 2;
  /**
   * @brief Last call to update(). Used to keep track of elapsed time.
   *
   */
  long _last_time;
  /**
   * @brief Value at last call to update(). Needed for the Trapezoidal rule.
   *
   */
  long _last_value;
};
