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

class EdgeDetect {
public:
  enum Edge { None = 0, Rising = 1, Falling = 2 };
  void begin(bool initial_state) {
    _edge = None;
    _last_state = initial_state;
  }
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
  Edge getEdge() { return _edge; }

private:
  Edge _edge;
  bool _last_state;
};
