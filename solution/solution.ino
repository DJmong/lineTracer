 #define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include "Motor.h"
#include "Sensor.h"
#include "Signal.h"
#include "Control.h"

int main(void){

  int L_speed, R_speed;
  int n=200;
  int d=1;
  MotorInit();
  
  SensorInit();
  //ControlInit(&L_speed, &R_speed);
  while(1){
    //Control(SensorRead(), L_speed, R_speed);
    MotorIn(GO, 180,180);


  }
  
    
  return 0;
}
