#include "subsystems/swerveDrive.hpp"
#include "main.h"
#include "utils/vector2.hpp"
#include <math.h>
#define PI 3.1415926535897932

/**
* Move each wheel based on vector math:
* (lateral vector) + (rotational vector) = (wheel vector)
* /param leftx
*        The controllers left joystick X axis,
*        for moving left/right
* /param lefty
*        The controllers left joystick y axis,
*        for moving forward/backward
* /param rightx
*        The controller's right joystick x value,
*        for rotation control
*/
void SwerveDrive::drive_test(int leftx, int lefty, int rightx)
{
  Vector2 lateralVec;
  lateralVec.setxy(lefty, leftx);

  pros::lcd::print(0, "dir: %f", lateralVec.get_angle_deg());
  pros::lcd::print(1, "mag: %f", lateralVec.get_length());

  Vector2 rot_lf, rot_rf, rot_lr, rot_rr;

  rot_lf.set_length_dir(rightx, PI/4);
  rot_rf.set_length_dir(rightx, (3*PI)/4);
  rot_rr.set_length_dir(rightx, (5*PI)/4);
  rot_lr.set_length_dir(rightx, (7*PI)/4);


  Vector2 lf_out = (lateralVec + rot_lf);
  Vector2 rf_out = (lateralVec + rot_rf);
  Vector2 lr_out = (lateralVec + rot_lr);
  Vector2 rr_out = (lateralVec + rot_rr);

  int lf_l = lf_out.get_length(), rf_l = rf_out.get_length(), lr_l = lr_out.get_length(), rr_l = rr_out.get_length();

  //float max = lf_l>rf_l ? lf_l>lr_l ? lf_l>rr_l ? lf_l : rr_l : lr_l>rr_l ? lr_l : rr_l : lr_l>rr_l ? lr_l : rr_l : rf_l>lr_l ? rf_l>rr_l? rr_l : rf_l : lr_l;

  float max = 127;
  if(lf_l > max)
    max = lf_l;
  if(rf_l > max)
    max = rf_l;
  if(rr_l > max)
    max=rr_l;
  if(lr_l > max)
    max=lr_l;

  lf_out.normalize(max);
  rf_out.normalize(max);
  lr_out.normalize(max);
  rr_out.normalize(max);

  pros::lcd::print(4, "dir: %f", rf_out.get_angle_deg());
  pros::lcd::print(5, "mag: %f", rf_out.get_length());

  frontLeft.set_module(lf_out.get_length(), lf_out.get_angle_deg());
  frontRight.set_module(rf_out.get_length(), rf_out.get_angle_deg());
  backLeft.set_module(lr_out.get_length(), lr_out.get_angle_deg());
  backRight.set_module(rr_out.get_length(), rr_out.get_angle_deg());
}

//Control algorithm based on papers found at this link:
//https://www.chiefdelphi.com/t/paper-4-wheel-independent-drive-independent-steering-swerve/107383

/**
 * Drive swerve drive
 * \param direction
 *  The direction we should drive, in degrees. 0 is straight ahead, and increases
 *  to the right.
 * \param speed
 *  The speed to drive at, -1 to 1.
 * \param rotation
 *  The speed at which to rotate, -1 to 1.  Positive values are clockwise, negative
 *  are counterclockwise.
 */
void SwerveDrive::drive(float direction, float speed, float rotation)
{

  float dirRads = direction * (PI/180);
  //the X axis is defined so the robot strafing towards the starboard direction
  //is positive x
  float x = speed * (cos( dirRads ));
  //The Y axis is defined so the robot traveling in the forward direction is
  //positive y
  float y = speed * (sin( dirRads ));
  //The z axis is defined using the right hand rule relative to the robots rotation
  float z = -rotation;

  //These are just constants from the paper mentioned above, I don't know what they do
  float L = this->wheelbase_mm;
  float W = this->trackwidth_mm;
  float R = sqrt((L * L) + (W * W));
  float A = x + (z * (L/R));
  float B = x - (z * (L/R));
  float C = y + (z * (W/R));
  float D = y - (z * (W/R));

  //Start turning to the angle each wheel has to face
  this->frontRight.set_angle(atan2(B, C) * (180/PI));
  this->frontLeft.set_angle(atan2(B, D) * (180/PI));
  this->backLeft.set_angle(atan2(A, D) * (180/PI));
  this->backRight.set_angle(atan2(A, C) * (180/PI));

  //Calculate the optimal wheel speed
  float frWheelSpeed = sqrt((B * B) + (C * C));
  float flWheelSpeed = sqrt((B * B) + (D * D));
  float rlWheelSpeed = sqrt((A * A) + (D * D));
  float rrWheelSpeed = sqrt((A * A) + (C * C));

  //Find the maximum speed for later
  float max = frWheelSpeed;
  if(flWheelSpeed > max) max = flWheelSpeed;
  if(rlWheelSpeed > max) max = rlWheelSpeed;
  if(rrWheelSpeed > max) max = rrWheelSpeed;

  //Initialize normalized wheel speeds
  float norm_frWheelSpeed = frWheelSpeed;
  float norm_flWheelSpeed = flWheelSpeed;
  float norm_rlWheelSpeed = rlWheelSpeed;
  float norm_rrWheelSpeed = rrWheelSpeed;

  //Normalize the wheel speeds if necessary
  if(max > 1)
  {
    norm_frWheelSpeed = frWheelSpeed / max;
    norm_flWheelSpeed = flWheelSpeed / max;
    norm_rlWheelSpeed = rlWheelSpeed / max;
    norm_rrWheelSpeed = rrWheelSpeed / max;
  }
  //Drive Baby Drive!
  this->frontRight.set_module(norm_frWheelSpeed, atan2(B, C) * (180/PI));
  this->frontLeft.set_module(norm_flWheelSpeed, atan2(B, D) * (180/PI));
  this->backLeft.set_module(norm_rlWheelSpeed, atan2(A, D) * (180/PI));
  this->backRight.set_module(norm_rrWheelSpeed, atan2(A, C) * (180/PI));
}

bool SwerveDrive::set_direction(float direction)
{

}

bool SwerveDrive::set_rotation(float direction)
{

}

bool SwerveDrive::set_speed(float speed)
{

}

bool SwerveDrive::auto_drive_inches(float direction, float speed)
{

}

bool SwerveDrive::auto_rotate_degrees(float degrees, float speed)
{

}
