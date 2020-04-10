#include "main.h"

double Kp = 0;
int minSpeed = 0;

PIDController::PIDController(double inkP, int inMinSpeed){
  kP= inkP;
  minspeed = inMinSpeed;
}

int PIDController::getMotorSpeed(int target, int current){
  error = target - current;
  int speed = error * kP;
  if(speed<=minspeed && speed>=0){
    int speed = minspeed;
  }
  else if(speed>= minspeed && speed<0){
    int speed = -minspeed;
  }
  return speed;
}

double PIDController::getError(){
  return error;
}
