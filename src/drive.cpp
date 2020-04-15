#include "main.h"
//Sensors
pros::Imu inertial(9);
//Motors
pros::Motor rightFront(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightBack (2, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftFront (3, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftBack (4, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
//Variables
double WHEELDIAMETER = 12.5;
double PI = 3.1415926535897932384;
int TICSPERROTATION = 360;
int THRESHHOLD = 5;
double REDUCTIONFACTOR = 0.8;
//PIDControllers
PIDController moveP(0.5,30);
PIDController turnP(0.2,30);
//Helper Functions
void brake()
{
  rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}
void coast()
{
  rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}
void left(int speed)
{
  leftFront.move(speed);
  leftBack.move(speed);
}
void right(int speed)
{
  rightFront.move(speed);
  rightBack.move (speed);
}
void timedDrive(int speed, int time)
{
  left(speed);
  right(speed);
  wait(time);
  left(0);
  right(0);
  brake();
}
void initializeInertialSensor()
{
  inertial.reset();

  int time = pros::millis();
  int iter = 0;
  while(inertial.is_calibrating()){
    iter+=10;
    wait(10);
  }
}
//Functions

void move(int inches)
{
  int time = 0;
  rightFront.tare_position();
  leftFront.tare_position();
  int distanceInTics = inches * (1/((WHEELDIAMETER * PI)/TICSPERROTATION));

  while(time<1){

    int speed = moveP.getMotorSpeed(distanceInTics, rightFront.get_position());



    if(rightFront.get_position() - leftFront.get_position() <= THRESHHOLD){
      left(speed * REDUCTIONFACTOR);
      right(speed);
    }
    else if(leftFront.get_position() - rightFront.get_position() <= THRESHHOLD){
      left(speed);
      right(speed * REDUCTIONFACTOR);
    }
    else{
      left(speed);
      right(speed);
    }


    double error = moveP.getError();
    if(fabs(error) < 1){
      time++;
      wait(2);
    }
  }
  left(0);
  right(0);
}

void moveBackward(int inches)
{
  int time = 0;
  rightFront.tare_position();
  leftFront.tare_position();
  int distanceInTics = inches * (1/((WHEELDIAMETER * PI)/TICSPERROTATION));
  //ticsPerRotation * (inches/(wheelDiameter * pi))

  while(time<1){

    int speed = moveP.getMotorSpeed(distanceInTics, rightFront.get_position());


    if(rightFront.get_position() - leftFront.get_position() <= -THRESHHOLD){
      left(-(speed * REDUCTIONFACTOR));
      right(-speed);
    }
    else if(leftFront.get_position() - rightFront.get_position() <= -THRESHHOLD){
      left(-speed);
      right(-(speed * REDUCTIONFACTOR));
    }
    else{
      left(-speed);
      right(-speed);
    }


    double error = moveP.getError();
    if(fabs(error) < 1){
      time++;
      wait(2);
    }
  }
  left(0);
  right(0);
}
void turn(int degree)
{
  int time = 0;

  while(time<1){

    int speed = turnP.getMotorSpeed(degree, inertial.get_rotation());
    left(speed);
    right(-speed);

    double error = turnP.getError();
    if(fabs(error) < 1){
      time++;
      wait(2);
    }
  }
  left(0);
  right(0);
}
//Driver Control
void driveOP()
{

  leftFront.move(master.get_analog(ANALOG_LEFT_Y));
  leftBack.move(master.get_analog(ANALOG_LEFT_Y));
  rightFront.move(master.get_analog(ANALOG_RIGHT_Y));
  rightBack.move(master.get_analog(ANALOG_RIGHT_Y));
}
