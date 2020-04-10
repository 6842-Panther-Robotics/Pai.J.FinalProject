#include "main.h"
//Sensors
//Motors
pros::Motor rightRoller(7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftRoller(8, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
//Variables
//PIDControllers
//Helper Functions
void rollers(int speed){
  rightRoller.move(speed);
  leftRoller.move(speed);
}
void brakeRollers(){
  rightRoller.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  leftRoller.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}
void coastRollers()
{
  rightRoller.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  leftRoller.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}
void moveRollers(int time, int speed){
  rollers(speed);
  wait(time);
  rollers(0);
  brakeRollers();
}
//Functions

//Driver Control
void rollersOP()
{
  brakeRollers();
  if(master.get_digital(DIGITAL_R1)) {
    leftRoller.move_velocity(100);
    rightRoller.move_velocity(100);
    }
  else if(master.get_digital(DIGITAL_R2)){
    leftRoller.move_velocity(-100);
    rightRoller.move_velocity(-100);
  }
  else{
    rollers(0);
  }

}
