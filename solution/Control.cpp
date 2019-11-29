#include "Control.h"
#include "Signal.h"

int base_speed=140;

void ControlInit(int *L_speed, int* R_speed){
  *L_speed=base_speed;
  *R_speed=base_speed;
}

static int _stop(){
  static int count=0;
  
}

int Control(int direction, int* L_speed, int* R_speed){

  int L_increase=0;
  int R_increase=0;

  //예외처리
  if(direction==INTERSECTION) return 0;
  else if(direction==NONE) return 0;
  else if(direction ==(GO_LEFT|GO_RIGHT)) return 0;
  //멈추는 경우
  
  else if(direction==STOP){
    if(_stop()){
      *L_speed=0;
      *R_speed=0; 
      return 1;
    }
  }

  else{
    *L_speed+=-5*(direction&GO_LEFT)+5*(direction&GO_RIGHT);
    *R_speed+=-5*(direction&GO_RIGHT)+5*(direction&GO_LEFT);
  
    return 1;
  }
  
}
