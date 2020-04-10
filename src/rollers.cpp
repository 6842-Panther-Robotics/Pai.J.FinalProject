#include "main.h"
//Sensors
//Motors
pros::Motor rightRoller(7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftRoller(8, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
//Variables
int THRESHHOLD = 5;
double REDUCTIONFACTOR = 0.8;
int TICSPERROTATION = 360;
//PIDControllers
PIDController rollerP(2,2);
//Helper Functions
void rollers(int speed)
{
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
void lRoller(int speed)
{
  leftRoller.move(speed);
}
void rRoller(int speed)
{
  rightRoller.move(speed);
}
void moveRollers(int time, int speed)
{
  rollers(speed);
  wait(time);
  rollers(0);
  brakeRollers();
}
//Functions
void intake(int rotations)
{
  int time = 0;
  rightRoller.tare_position();
  leftRoller.tare_position();

  while(time<1){

    int speed = rollerP.getMotorSpeed((rotations*TICSPERROTATION), rightRoller.get_position());



    if(rightRoller.get_position() - leftRoller.get_position() <= THRESHHOLD){
      lRoller(speed * REDUCTIONFACTOR);
      rRoller(speed);
    }
    else if(leftRoller.get_position() - rightRoller.get_position() <= THRESHHOLD){
      lRoller(speed);
      rRoller(speed * REDUCTIONFACTOR);
    }
    else{
      lRoller(speed);
      rRoller(speed);
    }


    double error = rollerP.getError();
    if(fabs(error) < 1){
      time++;
      wait(2);
    }
  }
  lRoller(0);
  rRoller(0);
}
void outtake(int rotations)
{
  int time = 0;
  rightRoller.tare_position();
  leftRoller.tare_position();

  while(time<1){

    int speed = rollerP.getMotorSpeed((rotations*TICSPERROTATION), rightRoller.get_position());



    if(rightRoller.get_position() - leftRoller.get_position() <= -THRESHHOLD){
      lRoller(-(speed * REDUCTIONFACTOR));
      rRoller(-speed);
    }
    else if(leftRoller.get_position() - rightRoller.get_position() <= -THRESHHOLD){
      lRoller(-speed);
      rRoller(-(speed * REDUCTIONFACTOR));
    }
    else{
      lRoller(-speed);
      rRoller(-speed);
    }


    double error = rollerP.getError();
    if(fabs(error) < 1){
      time++;
      wait(2);
    }
  }
  lRoller(0);
  rRoller(0);
}
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
