#ifndef _SWERVE_MODULE_
#define _SWERVE_MODULE_

#include "pros/motors.hpp"
#include "main.h"

class SwerveModule
{
private:
  pros::Motor& drive_motor;
  pros::Motor& dir_motor;
  pros::motor_gearset_e_t drive_gearset;
  pros::motor_gearset_e_t direction_gearset;

  int max_rpm_drive;
  int max_rpm_direction;

  // 25 teeth on the motor, 50 teeth on the output
  float direction_gear_ratio=50.0/25.0;

  // 19 teeth on the motor, 13 meshed and connected to a shaft,
  // 10 on that same shaft, and 30 on the wheel.
  float drive_gear_ratio=(19.0/13.0)*(10.0/30.0);
  float direction_motor_speed = max_rpm_direction;

  int drive_direction=1;

public:
  void stop(void);
  void set_module(float drive_percent, float direction_degrees);
  void set_speed(float speed);
  bool set_angle(int degrees);
  void reset_angle(void);

  /**
  * Create the SwerveModule object. There will be four of these per
  * drivetrain, one on each corner.
  * \param direction
  *        The motor involved with rotating the wheel
  * \param drive
  *        The motor involved with driving the wheel
  * \param dir_gear_ratio
  *        The gearing core inserted into the direction motor
  * \param drive_gear_ratio
  *        The gearing core inserted into the drive motor
  */
  SwerveModule(pros::Motor& direction, pros::Motor& drive,
               pros::motor_gearset_e_t dir_gear_ratio,
               pros::motor_gearset_e_t drive_gear_ratio):
                drive_motor(drive), dir_motor(direction)
  {
    dir_motor.set_gearing(dir_gear_ratio);
    drive_motor.set_gearing(drive_gear_ratio);

    drive_gearset=drive_gear_ratio;

    direction_gearset=dir_gear_ratio;
    dir_motor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);

    max_rpm_drive=(drive_gearset == pros::E_MOTOR_GEARSET_06) ? 600 : (drive_gearset == pros::E_MOTOR_GEARSET_18) ? 200 : 100;
    max_rpm_direction=(direction_gearset == pros::E_MOTOR_GEARSET_06) ? 600 : (direction_gearset == pros::E_MOTOR_GEARSET_18) ? 200 : 100;
  }
};

#endif
