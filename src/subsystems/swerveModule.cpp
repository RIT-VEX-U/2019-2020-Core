#include "subsystems/swerveModule.hpp"
#include "utils/BAMAngles.h"

/**
* Stops all motors associated with this module
*/
void SwerveModule::stop(void)
{
  dir_motor.move_velocity(0);
  drive_motor.move_velocity(0);
}

/**
* Set the direction and speed at the same time, taking into account that the
* drive motor will move if the direction motor moves.
*/
void SwerveModule::set_module(float drive_percent, float direction_degrees)
{

  int current_pos = dir_motor.get_position();
  float velocity = (drive_percent * max_rpm_drive) - (dir_motor.get_actual_velocity()/direction_gear_ratio);

  bamAngle_t currentBAM = floatToBAM(current_pos / direction_gear_ratio);
  bamAngle_t tgtBAM = floatToBAM(direction_degrees);

  float delta = bamToFloat(tgtBAM - currentBAM);
  float normalizedDelta = delta + (fabs(delta) > 90 ? (delta > 0 ? -180 : 180) : 0);

  int drive_multiplier = abs(delta) > 90 ? -1 : 1;

  velocity *= pow(1 - (fabs(normalizedDelta) / 90.0), 3);

  //pros::lcd::print(0, "delta: %f\n", normalizedDelta);
  //pros::lcd::print(1, "speed: %f\n", drive_multiplier * velocity);

  dir_motor.move_absolute(current_pos + (normalizedDelta * direction_gear_ratio), max_rpm_direction);
  drive_motor.move_velocity(velocity * drive_multiplier);
}

/**
* Sets the speed of the drive motor, between -1.0 and 1.0
*/
void SwerveModule::set_speed(float percent)
{
  drive_motor.move_velocity(percent * max_rpm_drive);
}

/**
* Sets the angle of the wheel by setting the "direction" motor
* to the angle, taking into account the gear ratio for the
* direction motor. Also compensates for the direction motor turning the wheel.
*/
bool SwerveModule::set_angle(int degrees)
{
  dir_motor.move_absolute(degrees * direction_gear_ratio, max_rpm_direction);
  drive_motor.move_velocity(-dir_motor.get_actual_velocity() / direction_gear_ratio);
}

/**
* Reset the position of the direction motor. Do not use unless in an emergency
* situation, this might ruin the drivetrain for the match.
*/
void SwerveModule::reset_angle(void)
{
  dir_motor.tare_position();
}
