
#include <avr/io.h>

#include "Motor.h"

#define set_bit(value, bit) ( _SFR_BYTE(value) |=  _BV(bit))
#define clear_bit(value, bit) ( _SFR_BYTE(value) &= ~_BV(bit))
#define L_PWM OCR0A
#define R_PWM OCR2A

#define L_BACK      (set_bit(PORTB, 6));\
                    (clear_bit(PORTB, 5));

#define L_FORWARD   (set_bit(PORTB, 5));\
                    (clear_bit(PORTB, 6));
                    
#define R_BACK      (set_bit(PORTH, 6));\
                    (clear_bit(PORTH, 5));

#define R_FORWARD   (set_bit(PORTH, 5));\
                    (clear_bit(PORTH, 6));
            
static void Stop();
static void Forward();

void MotorInit() {
  DDRB = 0xF0;
  DDRH = 0x60;

  TCCR0A |= (1 << WGM01) | (1 << WGM00);
  TCCR0A |= (1 << COM0A1) | (0 << COM0A0);
  TCCR0B |= (0 << CS02) | (0 << CS01) | (1 << CS00);

  TCCR2A |= (1 << WGM01) | (1 << WGM00);
  TCCR2A |= (1 << COM2A1) | (0 << COM2A0);
  TCCR2B |= (0 << CS02) | (0 << CS01) | (1 << CS00);
  
  L_FORWARD;
  R_FORWARD;
}



void MotorIn(int L_speed, int R_speed) {
  if(L_speed == 125) L_speed = 0;
  else if(L_speed > 255)L_speed = 255;
  else if(L_speed < 125){ //역회전
    if(L_speed < 0) L_speed = 0;
    L_BACK;
    L_speed = 255 - L_speed;
  }
  else L_FORWARD;
  
  if(R_speed == 125) R_speed = 0;
  else if(R_speed > 255) R_speed = 255;
  else if(R_speed < 125){
    if(R_speed < 0) R_speed = 0;
    R_BACK;
    R_speed = 255 - R_speed;
  }
  else R_FORWARD;
   
  L_PWM = L_speed;
  R_PWM = R_speed;
}
