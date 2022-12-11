/**
 * @file main.cpp
 * @author Christoph B. Wurzinger (wu@htlweiz.at)
 * @brief Test/demo software for the car-shield
 * @version 0.1
 * @date 2022-12-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <Blink.h>
#include <CarShield.h>
#include <EdgeDetect.h>
#include <Integrate.h>
#include <Toggle.h>

/**
 * @brief How long it takes to full speed.
 *
 */
const long ACCEL_TIME = 1000;

EdgeDetect ed_left;
EdgeDetect ed_right;
EdgeDetect ed_stop;
Blink b_left;
Blink b_right;
EdgeDetect ed_dipped_beam;
EdgeDetect ed_high_beam;
Toggle t_dipped_beam;
Toggle t_high_beam;
EdgeDetect ed_dipped_beam_out;
EdgeDetect ed_high_beam_out;
Integrate i_accel;

void setup() {
  // Enable outputs.
  pinMode(LED_DIPPED_BEAM, OUTPUT);
  pinMode(LED_HIGH_BEAM, OUTPUT);
  pinMode(LED_TURN_RIGHT, OUTPUT);
  pinMode(LED_TURN_LEFT, OUTPUT);
  pinMode(LED_BREAK, OUTPUT);
  pinMode(LED_SPEED_INDICATOR, OUTPUT);

  // Initialize state.
  ed_left.begin(digitalRead(SW_LEFT));
  ed_right.begin(digitalRead(SW_RIGHT));
  ed_stop.begin(digitalRead(SW_STOP));
  b_left.begin(1000);
  b_right.begin(1000);
  ed_dipped_beam.begin(digitalRead(SW_DIPPED_BEAM));
  ed_high_beam.begin(digitalRead(SW_HIGH_BEAM));
  t_dipped_beam.begin();
  t_high_beam.begin();
  ed_dipped_beam_out.begin(t_dipped_beam.getState());
  ed_high_beam_out.begin(t_high_beam.getState());
  i_accel.begin();
}

void loop() {
  // Read inputs and update state.
  ed_left.update(digitalRead(SW_LEFT));
  ed_right.update(digitalRead(SW_RIGHT));
  ed_stop.update(digitalRead(SW_STOP));
  b_left.update();
  b_right.update();
  ed_dipped_beam.update(digitalRead(SW_DIPPED_BEAM));
  ed_high_beam.update(digitalRead(SW_HIGH_BEAM));
  t_dipped_beam.update(ed_dipped_beam.getEdge());
  t_high_beam.update(ed_high_beam.getEdge());
  ed_dipped_beam_out.update(t_dipped_beam.getState());
  ed_high_beam_out.update(t_high_beam.getState());
  // Double pedal drive FTW!
  i_accel.update((digitalRead(SW_ACCEL) ? 0 : 1) +
                 (digitalRead(SW_DECEL) ? 0 : -1));
  // Make sure the integrator stays within reasonable bounds.
  i_accel.coerce(0, ACCEL_TIME);

  // The turn lights need additional attention/logic.
  if (ed_left.getEdge() == EdgeDetect::Falling) {
    b_left.setBlinking(!b_left.isBlinking());
    b_right.stop();
  }
  if (ed_right.getEdge() == EdgeDetect::Falling) {
    b_right.setBlinking(!b_right.isBlinking());
    b_left.stop();
  }
  if (ed_stop.getEdge() == EdgeDetect::Falling) {
    b_left.stop();
    b_right.stop();
  }

  // The head lights need additional attention/logic.
  if (ed_high_beam_out.getEdge() == EdgeDetect::Rising) {
    t_dipped_beam.setState(true);
  }
  if (ed_dipped_beam_out.getEdge() == EdgeDetect::Falling) {
    t_high_beam.setState(false);
  }

  // Write outputs.
  digitalWrite(LED_TURN_LEFT, b_left.getState());
  digitalWrite(LED_TURN_RIGHT, b_right.getState());

  digitalWrite(LED_DIPPED_BEAM, t_dipped_beam.getState());
  digitalWrite(LED_HIGH_BEAM, t_high_beam.getState());

  digitalWrite(LED_BREAK, !digitalRead(SW_DECEL));

  // The speed indicator is actually analog (PWM).
  analogWrite(LED_SPEED_INDICATOR,
              map(i_accel.getState(), 0, ACCEL_TIME, 0, 255));
}
