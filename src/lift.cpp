#include "main.h"
//Sensors
pros::ADIPotentiometer liftPot('A'); //4095 ticks in 265 degrees
//Motors
pros::Motor liftMotor(5, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);

//Variables
//PIDControllers
PIDController liftP(2,2);
//Helper Functions
void lift(int speed)
{
  liftMotor.move(speed);
}
void brakeLift()
{
  liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}
void coastLift()
{
  liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}
void moveLiftTime(int time, int speed)
{
  lift(speed);
  wait(time);
  lift(0);
  brakeLift();
}
//Functions
void moveLift(int target)
{
  int time = 0;

  while(time<1){

    int speed = liftP.getMotorSpeed(target, liftPot.get_value());

    lift(speed);

    double error = liftP.getError();
    if(fabs(error) < 1){
      time++;
      wait(5);
    }
  }
  lift(0);
}
//Driver Control
void liftOP()
{
  brakeLift();
  if(master.get_digital(DIGITAL_L1)) {
    liftMotor.move_velocity(100);
    }
  else if(master.get_digital(DIGITAL_L2)){
    liftMotor.move_velocity(-100);
  }
  else{
    lift(0);
  }

}
