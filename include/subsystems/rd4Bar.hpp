#ifndef _RD_4_BAR_
#define _RD_4_BAR_
#include "okapi/impl/device/motor/motorGroup.hpp"
#include "logging.hpp"

class rd4Bar{

private:
  //Two MotorGroups
  okapi::MotorGroup lift_motors1;
  okapi::MotorGroup lift_motors2;

  //Position it is currently holding, -1 if none
  float holdingPos = -1;

  //The minimum motor velocity needed to hold the lift in a certain position
  int holdingPower;  //This is a guess, will need to be adjusted

public:
//Constructor
  rd4Bar(okapi::MotorGroup lift_motors1, okapi::MotorGroup lift_motors2, int holdingPower) : lift_motors1(lift_motors1), lift_motors2(lift_motors2){
    this -> holdingPower = holdingPower;
    lift_motors2.setReversed(false);
    lift_motors1.setReversed(true);
    lift_motors1.setEncoderUnits(okapi::AbstractMotor::encoderUnits::rotations);
    lift_motors2.setEncoderUnits(okapi::AbstractMotor::encoderUnits::rotations);
  }

//Set all motors to a positive velcity to raise the lift indefinitely
  void raise(int power){
    lift_motors1.moveVelocity(power);
    lift_motors2.moveVelocity(power);
  }

//Set all motors to a negative velocity to lower the lift indefinitely
  void lower(int power){
    power *= -1;
    lift_motors1.moveVelocity(power);
    lift_motors2.moveVelocity(power);
  }

//Set all motors to a zero velocity to stop the lift from moving
  void stop(){
    lift_motors1.moveVelocity(0);
    lift_motors2.moveVelocity(0);
  }

//Raise/Lower the lift to a specified point and have it keep that poisition
  void moveTo(float encoderVal, bool hold){

    //While it is too high, lower it
    while(fabs(lift_motors1.getPosition()) < encoderVal){
      lift_motors1.moveVelocity(-100);
      lift_motors2.moveVelocity(-100);
    }

    //While it is too low, raise it
    while(fabs(lift_motors1.getPosition()) < encoderVal){
      lift_motors1.moveVelocity(100);
      lift_motors2.moveVelocity(100);
    }

    //if the lift should maintain this position
    if(hold){
      holdingPos = encoderVal;
      hold_pos();
    }
    else{
      lift_motors1.moveVelocity(0);
      lift_motors2.moveVelocity(0);
    }
  }

  void hold_pos(){
    if(fabs(lift_motors1.getPosition()) < holdingPos - 0.05 || fabs(lift_motors2.getPosition()) < holdingPos - 0.05){
      //lift_motors1.moveVoltage(lift_motors1.getVoltage() - 1);
      //lift_motors2.moveVoltage(lift_motors2.getVoltage() - 1);
      holdingPower -= 2;
    }
    else if(fabs(lift_motors1.getPosition()) > holdingPos + 0.05 || fabs(lift_motors2.getPosition()) > holdingPos + 0.05){
      //lift_motors1.moveVoltage(lift_motors1.getVoltage() + 1);
      //lift_motors2.moveVoltage(lift_motors2.getVoltage() + 1);
      holdingPower++;
    }
    lift_motors1.moveVelocity(holdingPower);
    lift_motors2.moveVelocity(holdingPower);
  }

  bool is_holding(){ return holdingPos > -1; }

  float getHoldingPos(){ return holdingPos; }

  float getCurrPos(){ return lift_motors1.getPosition(); }

  void release_hold(){
    holdingPos = -1;
  }

  //void start_hold_pos(int pos){
    //pros::Task hold_pos_task(void (*hold_pos)(int));
  //}

//  bool isDown(){
//  }

  //Logging function
  void log_lift(){
      while(true){
        logging::log(lift_motors1.getCurrentDraw(), lift_motors1.getPosition());
        logging::log(lift_motors2.getCurrentDraw(), lift_motors2.getPosition());
        pros::delay(50);
        //TODO: Log individual motors?
      }
    }


//TODO: broken??
//Checks if there is voltage going to the lift motors
  bool isMoving(){
    return lift_motors1.getVoltage() > 0 || lift_motors2.getVoltage() > 0;
  }

  float getEncoderVal(){
    return lift_motors1.getPosition();
  }

};

#endif
