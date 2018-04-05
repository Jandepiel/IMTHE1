/*
 * main.c
 *
 *  Created on: 22 feb. 2018
 *      Author: jande_000
 */
#include <avr/io.h>
#include <util/delay.h>

void digitalNumber(uint8_t number){



//Switch voor elk cijfer van 0 t/m 9 linker en rechter display
  switch(number){

  //Rechterdisplay
  case 0:
      PORTC = (0 << 0);
      PORTD ^= (1 << 7);
      break;
    case 1:
      PORTC = ~(0b11 << 1);
      PORTD |= (1 << 7);
      break;
    case 2:
      PORTC = (0b111001 << 2);
      PORTD &= ~(1 << 7);
      break;
    case 3:
      PORTC = (0b1111 << 4);
      PORTD &= ~(1 << 7);
      break;
    case 4:
      PORTC = ~(1011 << 1);
      PORTD &= ~(1 << 7);
      break;
    case 5:
      PORTC = (0b1001 << 1);
      PORTD &= ~(1 << 7);
      break;
    case 6:
      PORTC = (1 << 1);
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

 //Linkerdisplay
     case 10:
      PORTB = (0 << 0);
      PORTD ^= (1 << 6);
      break;
     case 11:
      PORTB = ~(0b11 << 1);
      PORTD |= (1 << 6);
      break;
     case 12:
      PORTB =  (0b111001 << 2);
      PORTD &= ~(1 << 6);
      break;
     case 13:
      PORTB = (0b1111 << 4);
      PORTD &= ~(1 << 6);
      break;
     case 14:
      PORTB = ~(1011 << 1);
      PORTD &= ~(1 << 6);
      break;
     case 15:
      PORTB = (0b1001 << 1);
      PORTD &= ~(1 << 6);
      break;
     case 16:
      PORTB = (1 << 1);
      PORTD &= ~(1 << 6);
      break;
     case 17:
      PORTB = (11 << 3);
      PORTD ^= (1 << 6);
      break;
     case 18:
      PORTB = (0 << 0);
      PORTD &= ~(1 << 6);
      break;
     case 19:
      PORTB = (1 << 4);
      PORTD &= ~(1 << 6);
      break;
  }
}

int main(void){
  //setup
  DDRC = 0b00111111; //output voor rechterdisplay
  DDRB = 0b00111111; //output voor linkerdisplay
  DDRD = 0b11000000; //output voor middenstrepen op beide displays
  digitalNumber(8); //zet de rechterdisplay op 0
  digitalNumber(18); // zet het linkerdisplay op 0

  while(1){
    //programma
  for(uint8_t i=10;i<20;i++)
    {
      digitalNumber(i); //een for loop voor het bijhouden van de tientallen

      for(uint8_t i=0;i<10;i++)
      {
       digitalNumber(i); //for loop voor het bijhouden van eenheden
       _delay_ms(1000); //wacht 1 seconde voor timer effect
      }
    }
  }
  return 0;
}
