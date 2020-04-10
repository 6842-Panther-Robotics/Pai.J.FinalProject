#include "main.h"

void redAuton(){
  move(30);
}
void blueAuton(){
  move(20);
}

void autonomous(){
  switch(autonIndex){

      case 0:
        redAuton();
        break;
      case 1:
        blueAuton();
        break;

    }
}
