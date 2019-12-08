#ifndef _TANK_DRIVE_
#define _TANK_DRIVE_

#include "okapi/impl/device/motor/motorGroup.hpp"
#include "okapi/impl/util/timer.hpp"
#include "okapi/impl/device/rotarysensor/adiGyro.hpp"
#include "utils/pid.hpp"
#include <ctime>
#include "logging.hpp"

#define PI 3.1415926536

class TankDrive
{
  public:

  enum omni_config_t
  {
    front_wheel_dr,
    rear_wheel_dr,
    center_dr
  };

  struct config_t
  {

  //Autonomous control variables
  //As in y=mx+b, deceleration = p * (target - current) + (velocity * d)+ feedforward
  // drive_forward() variables
  PID::config_t *drive_pid;

  // turn_degrees() variables
  PID::config_t *turn_pid;

  float wheel_size;
  omni_config_t omni_config;

  };

private:
  pros::Motor left_front, right_front, left_rear, right_rear;

  int gearset;

  okapi::ADIGyro *gyro;  


  // common variables
  bool initialize_func = false;

  const config_t *config;

  PID *drive_pid;
  PID *turn_pid;

public:

  /**
  Drive the robot with differential drive.
  Left axis is the Y axis on the left joystick, same for the right joystick.

  Inputs are "percentage", between -1.0 and +1.0
  */
  void drive(double left_in, double right_in);

  /**
  Autonomously drive the robot x inches forward (or negative inches for reverse)
  at percent_speed (between 0.0 and 1.0).

  Will stop and return true after reaching the target.
  */
  bool drive_forward(double inches, double percent_speed);

  /**
  Autonomously turn the robot x degrees, using feedback from a gyroscope

  For left turns, use negative degrees, for right, use positive.
  */
  bool turn_degrees(double degrees, double percent_speed);

  /**
  Create the tank drive object from two separate motor groups, what gearset they
  are using, and the size of the wheel.

  Initialize the drive encoders to measure in number of rotations, to make computing
  the distance traveled based on the wheel size easier.
  */
  TankDrive(pros::Motor left_front, pros::Motor right_front, pros::Motor left_rear, pros::Motor right_rear, pros::motor_gearset_e_t gearset, okapi::ADIGyro *gyro, config_t *config, PID::config_t *drive_pid_config, PID::config_t *turn_pid_config):
  left_front(left_front), right_front(right_front), left_rear(left_rear), right_rear(right_rear), gearset((int)gearset == 0 ? 100 : (int)gearset == 1 ? 200 : 600), gyro(gyro), config(config)
  {
    drive_pid = new PID(drive_pid_config);
    turn_pid = new PID(turn_pid_config);

    left_front.set_gearing(gearset);
    right_front.set_gearing(gearset);
    left_rear.set_gearing(gearset);
    right_rear.set_gearing(gearset);

    left_front.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
    right_front.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
    left_rear.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
    right_rear.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
  }

};

#endif
