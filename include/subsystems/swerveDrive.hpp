#ifndef _SWERVE_DRIVE_
#define _SWERVE_DRIVE_

#include "main.h"
#include "swerveModule.hpp"

class SwerveDrive
{
private:
  SwerveModule& frontLeft;
  SwerveModule& frontRight;
  SwerveModule& backLeft;
  SwerveModule& backRight;
  float wheelbase_mm = 0.0;
  float trackwidth_mm = 0.0;

  float turn_angle_rad = atan(wheelbase_mm / trackwidth_mm);

public:

  enum RotVal {LEFT, RIGHT};

  void drive(float direction, float speed, float rotation);

  void drive_test(int leftx, int lefty, int rightx);

  bool set_direction(float direction);

  bool set_rotation(float direction);

  bool set_speed(float speed);

  bool auto_drive_inches(float direction, float speed);

  bool auto_rotate_degrees(float degrees, float speed);

  SwerveDrive(SwerveModule& frontLeft, SwerveModule& frontRight, SwerveModule& backLeft, SwerveModule& backRight):
  frontLeft(frontLeft), frontRight(frontRight), backLeft(backLeft), backRight(backRight)
  {  }

};

#endif
