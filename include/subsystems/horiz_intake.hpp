#ifndef _HORIZ_INTAKE_
#define _HORIZ_INTAKE_

#include "pros/motors.hpp"

using namespace pros;

class HorizIntake
{
private:

  Motor left, right;

  int motor_speed = 1;

public:

  void run_intake(bool in_button, bool out_button)
  {
    int direction = (in_button == true) ? 1 : (out_button == true) ? -1 : 0;

    left.move_voltage(12000 * direction * motor_speed);
    right.move_voltage(12000 * direction * motor_speed);

  }

  HorizIntake(Motor left_motor, Motor right_motor):
  left(left_motor), right(right_motor)
  {

  }

};

#endif
