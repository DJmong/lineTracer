#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "Signal.h"
void ControlInit(int* L_speed, int* R_speed);
int Control(int sensorVal);

#endif
