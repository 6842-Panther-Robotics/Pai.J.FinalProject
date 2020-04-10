#include "main.h"
//Sensors
pros::ADIPotentiometer tilterPot('B'); //4095 ticks in 265 degrees
//Motors
pros::Motor tilterMotor(6, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);

//Variables
//PIDControllers
PIDController tilterP(2,2);
//Helper Functions
void tilter(int speed)
{
  tilterMotor.move(speed);
}
void brakeTilter()
{
  tilterMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}
void coastTilter()
{
  tilterMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}
void moveTilter(int time, int speed)
{
  tilter(speed);
  wait(time);
  tilter(0);
  brakeTilter();
}
//Functions
void score()
{
  int time = 0;

  while(time<1){

    int speed = tilterP.getMotorSpeed(3000, tilterPot.get_value());

    tilter(speed);

    double error = tilterP.getError();
    if(fabs(error) < 1){
      time++;
      wait(5);
    }
  }
  tilter(0);
}
void tilterBack()
{
  int time = 0;

  while(time<1){

    int speed = tilterP.getMotorSpeed(200, tilterPot.get_value());

    tilter(speed);

    double error = tilterP.getError();
    if(fabs(error) < 1){
      time++;
      wait(5);
    }
  }
  tilter(0);
}
//Driver Control
void liftOP()
{
  brakeTilter();
  if(master.get_digital(DIGITAL_LEFT)) {
    score();
    }
  else if(master.get_digital(DIGITAL_Y)){
    tilterBack();
  }
  else{
    tilter(0);
  }

}
