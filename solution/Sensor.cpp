#include "Sensor.h"

#define PIN_IN PINF
#define DDR_IN DDRF


int val[5]={0,0,0,0,0};
int num=0;

void SensorInit(){
  DDR_IN=0xE0;
  ADMUX= (1 << REFS0);
  ADMUX |= 0<<MUX2 | 0<<MUX1||0<<MUX0;
  ADCSRA = 1 << ADEN;
  ADCSRA |= 1 << ADSC;
  ADCSRA |= 1<< ADIE;
  ADCSRA |= (1<<ADPS2) |(0<<ADPS1) | (0<<ADPS0); 


  sei();
}
int SensorRead(){

  int way=0;
  for(int i=0;i<5;i++){
    way<<=1;
    way |=val[i];
  }

  return way;

}

ISR(ADC_vect){
  val[num]=ADCW;
  if(val[num]>500){
    val[num]=0;
  }
  else{
    val[num]=1;
  }
  
  if((ADMUX&0x04)==0x04){
    ADMUX^=0x04;
    num=0;
  }
  else{
    ADMUX+=0x01;
    num++;
  }
  
  ADCSRA |= 0x40;
}
