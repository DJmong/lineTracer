#include <avr/io.h>
#include "Motor.h"
#include "Signal.h"
#define set_bit(value, bit) ( _SFR_BYTE(value) |=  _BV(bit))
#define clear_bit(value, bit) ( _SFR_BYTE(value) &= ~_BV(bit))
#define L_PWM OCR0A
#define R_PWM OCR2A

#define L_Forward   (set_bit(PORTB, 5));\
                    (clear_bit(PORTB, 6));
                
#define L_BACK      (set_bit(PORTB, 6));\
                    (clear_bit(PORTB, 5));
    
#define R_Forward   (set_bit(PORTH, 6));\
                    (clear_bit(PORTH, 5));

#define R_BACK      (set_bit(PORTH, 5));\
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

  L_PWM = 250;
  R_PWM = 250;
}

static void Forward() {
  L_Forward;
  R_Forward;
}

static void Stop(){
  L_PWM=0;
  R_PWM=0;
}

void MotorIn(int direction, int L_speed, int R_speed) {
  Forward();
  L_PWM=L_speed;
  R_PWM=R_speed;

}
