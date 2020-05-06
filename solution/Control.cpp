
#include "Control.h"
#include "Signal.h"

#define S 1
#define F 4

int base_speed = 160;

void ControlInit(int *L_speed, int* R_speed){
  *L_speed = base_speed;
  *R_speed = base_speed;
}


int Control(int sensor){
  static int pre_sensor = 0;
  int weight[5] = {F,S,0,-S,-F};

  //pid
  float Kp = 9.8;
  float Ki = 0.78;
  float Kd = 0.5;
  
  // err_sum, err
  static float err_sum = 0;
  static int pre_err = 0;
  static int count = 0;
  int gain = 0;
  int err = 0;
  
  //예외처리
  if(sensor == INTERSECTION) sensor = pre_sensor;
  else if(sensor == NONE) sensor = pre_sensor;
 
  if(!(sensor&GO)){
    base_speed = 160;
    count = 0;
    pre_sensor = sensor;
    //2진비트 디코더 + 가중치 입력  
    for(int i = 0;i < 5;i++){
      if(sensor & 0x01 ){
        err += weight[4-i];
      }
      sensor >>= 1;
    }
  }
  else{
    count++;
    if(count > 10){
      base_speed += 3;
      count = 0;
    }
    pre_sensor = sensor;
    err = 0;
    
    return 0;
  }
  gain = (int)(Kp * err + Ki * err_sum + Kd * (err - pre_err));  
  
  err_sum = (err_sum * 0.5) + err;
  pre_err = err;
  return gain;
} 
