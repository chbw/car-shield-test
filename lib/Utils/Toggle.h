/**
 * @file Toggle.h
 * @author Christoph B. Wurzinger (wu@htlweiz.at)
 * @brief Toggle on Edge
 * @version 0.1
 * @date 2022-12-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <EdgeDetect.h>

class Toggle {
public:
  void begin() { begin(false, EdgeDetect::Falling); }
  void begin(bool initial_state) { begin(initial_state, EdgeDetect::Falling); }
  void begin(bool initial_state, EdgeDetect::Edge edge) {
    _state = initial_state;
    _edge = edge;
  }
  void update(EdgeDetect::Edge edge) {
    if (edge == _edge) {
      _state = !_state;
    }
  }
  void setState(bool state) { _state = state; }
  bool getState() { return _state; }

private:
  bool _state;
  EdgeDetect::Edge _edge;
};
