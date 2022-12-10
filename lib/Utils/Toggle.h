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

/**
 * @brief Toggle on rising or falling edge. Uses EdgeDetect.
 * 
 */
class Toggle {
public:
  /**
   * @brief Initialize
   * 
   * @param initial_state State after initialization
   * @param edge Edge to toggle on (Rising or Falling make sense)
   */
  void begin(bool initial_state = false,
             EdgeDetect::Edge edge = EdgeDetect::Falling) {
    _state = initial_state;
    _edge = edge;
  }
  /**
   * @brief Update internal state. Call periodically.
   * 
   * @param edge Current edge value (may be None)
   */
  void update(EdgeDetect::Edge edge) {
    if (edge == _edge) {
      _state = !_state;
    }
  }
  /**
   * @brief Force the current state.
   * 
   * @param state New state
   */
  void setState(bool state) { _state = state; }
  /**
   * @brief Get the current state
   * 
   * @return true 
   * @return false 
   */
  bool getState() { return _state; }

private:
  /**
   * @brief The current state.
   * 
   */
  bool _state;
  /**
   * @brief The edge to toogle on.
   * 
   */
  EdgeDetect::Edge _edge;
};
