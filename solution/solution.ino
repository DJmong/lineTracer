#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include "Motor.h"
#include "Sensor.h"
#include "Signal.h"
#include "Control.h"

void test(int n, int gain, int next_delay);
int nextDelay(int sensor);

int L_speed, R_speed;

void mainInit(){
  MotorInit();
  ControlInit(&L_speed, &R_speed);
  SensorInit();  
  while(SensorRead()!= GO);
  MotorIn(L_speed, R_speed);
}

int nextDelay(int sensor){
  static float time_ms = 3;
  if(sensor & GO){
    time_ms += 3;
    if(time_ms > 10) time_ms = 10;
    return (int) time_ms;
  }
  else{
    time_ms /= 4;
    return (int) time_ms;
  }
}

int main(void){
  int sensor;
  int gain;
  int next_delay;
  mainInit();
  while(1){
    sensor = SensorRead();
    gain = Control(sensor);

    MotorIn(L_speed - gain ,R_speed + gain); 

    next_delay = nextDelay(sensor);
    delay(next_delay);
  }
  return 0;
}
