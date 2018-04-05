/*
 * main.c
 *
 *  Created on: 20 feb. 2018
 *      Author: jande_000
 */

#include <avr/io.h>
#include <util/delay.h>


void digitalNumber(uint8_t number){

    //Switch om elk cijfer van 0 t/m 9 te kunnen maken
  switch(number){
    case 0:
      PORTC = (0 << 0);
      PORTD ^= (1 << 7);
      break;
    case 1:
      PORTC = ~0b00000110;
      PORTD |= (1 << 7);
      break;
    case 2:
      PORTC = (111001 << 2);
      PORTD &= ~(1 << 7);
      break;
    case 3:
      PORTC = (1111 << 4);
      PORTD &= ~(1 << 7);
      break;
    case 4:
      PORTC = ~(1011 << 1);
      PORTD &= ~(1 << 7);
      break;
    case 5:
      PORTC = ~(101101 << 0);
      PORTD &= ~(1 << 7);
      break;
    case 6:
      PORTC = ~(111101 << 0);
      PORTD &= ~(1 << 7);
      break;
    case 7:
      PORTC = (11 << 3);
      PORTD ^= (1 << 7);
      break;
    case 8:
      PORTC = (0 << 0);
      PORTD &= ~(1 << 7);
      break;
    case 9:
      PORTC = (1 << 4);
      PORTD &= ~(1 << 7);
      break;
  }
}

int main(void){
  //setup
  DDRC = 0b00111111; //output voor buitenstrepen
  DDRD = 0b10000000; //output voor middenstreep

  digitalNumber(8); //Zet eerst alle pinnen omhoog

  while(1){
    //programma
      for(uint8_t i=0;i<10;i++) //For loop van 0 tot 9
      {
       digitalNumber(i); //Tel van 0 tot 9 en begin opnieuw
       _delay_ms(1000);
      }
  }
  return 0;
}
