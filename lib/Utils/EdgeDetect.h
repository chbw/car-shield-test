/**
 * @file EdgeDetect.h
 * @author Christoph B. Wurzinger (wu@htlweiz.at)
 * @brief A simple edge detection library for Arduino
 * @version 0.1
 * @date 2022-12-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <stdint.h>

/**
 * @brief Detect rising or falling edges.
 *
 */
class EdgeDetect {
public:
  /**
   * @brief Edge types. Rising, falling or none.
   *
   */
  enum Edge { None = 0, Rising = 1, Falling = 2 };
  /**
   * @brief Initialize
   *
   * @param initial_state The initial input state. Set to the real signal value
   * upon initialization to avoid spurious edges on the first call to update.
   */
  void begin(bool initial_state) {
    _edge = None;
    _last_state = initial_state;
  }
  /**
   * @brief Update. Call periodically with current signal value to make edge
   * detection work.
   *
   * @param current_state Current signal value.
   */
  void update(bool current_state) {
    if (current_state && !_last_state) {
      _edge = Rising;
    } else if (!current_state && _last_state) {
      _edge = Falling;
    } else {
      _edge = None;
    }
    _last_state = current_state;
  }
  /**
   * @brief Get the last detected edge.
   * 
   * @return Edge Rising, falling or none.
   */
  Edge getEdge() { return _edge; }

private:
  /**
   * @brief The last detected edge.
   * 
   */
  Edge _edge;
  /**
   * @brief The previous input/signal value.
   * 
   */
  bool _last_state;
};
