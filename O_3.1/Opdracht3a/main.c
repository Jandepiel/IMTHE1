


#include <avr/io.h>
#include <util/delay.h>



uint16_t randomNumber = 0x1234;
uint8_t cijfer;

void digitalNumber(uint8_t number){

  switch(number){
    case 0:
      PORTB = (0 << 0);
      _delay_ms(3);
      break;

    case 1:
      PORTB = 0b00101010;
	   _delay_ms(3);
      break;

    case 2:
      PORTB = 0b00110100;
      _delay_ms(1.5);
      PORTB = 0b00011001;
	   _delay_ms(1.5);
      break;

    case 3:
      PORTB = 0b00110001;
      _delay_ms(1.5);
      PORTB = 0b00101010;
      _delay_ms(1.5);
      PORTB = 0b00011100;
      break;

    case 4:
      PORTB = 0b00011101;
      _delay_ms(1.5);
      PORTB = 0b00110101;
	  _delay_ms(1.5);



      break;

  case 5:
      PORTB = 0b00011101;
      _delay_ms(1);
      PORTB = 0b00110101;
      _delay_ms(1);
      PORTB = 0b00101010;
      _delay_ms(1);
      break;

    case 6:
      PORTB = 0b00000100;
      _delay_ms(1.5);
      PORTB = 0b00000001;
	  _delay_ms(1.5);


      break;


  }



}

int main(void){
  //setup

  DDRB = 0b00111111;
  PORTC = (1 << PC0);



  while(1){
    //programma


	randomNumber = 2053 * randomNumber + 13849;
	cijfer = (randomNumber >> 8);


	if (cijfer < 7 && cijfer > 0)
	{
		if bit_is_clear(PINC, PC0)
		{
			for(uint8_t j=0;j<255;j++)
			{
				digitalNumber(cijfer);
				_delay_ms(2);
			}
			digitalNumber(0);

		} else {
			digitalNumber(0);

		}
	} else {
		digitalNumber(0);

	}



  }
  return 0;


}


