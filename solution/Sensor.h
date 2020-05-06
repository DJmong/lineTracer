#ifndef _Sensor_H_
#define _Sensor_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Signal.h"

void SensorInit();
int SensorRead();
#endif
