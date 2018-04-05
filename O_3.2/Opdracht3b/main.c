
#include <avr/io.h>
#include <util/delay.h>



void initADC(){
	ADMUX |= (1 << REFS0); // Zet op 5V
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); // Zet divider op 128 voor 10 bit precisie
	ADCSRA |= (1 << ADEN); // AD Enable


}

uint16_t readADC(){
	ADCSRA |= (1 << ADSC); //start reading
	loop_until_bit_is_clear(ADCSRA, ADSC);
	return ADC;


}

void delay(uint16_t value)
{
	for(uint16_t i=0;i<value;i++){
		_delay_ms(1);
	}

}

int main(void){


	DDRB = (1 << PB5);

	initADC();

	while(1){
		//programma
		//PORTB = bit_is_clear(PIND, PD2) ? (1 << PB5) : 0;
		//PORTB = (readADC() > 512) ? (1 << PB5) : 0;

		uint16_t pwm = readADC();
		PORTB = (1 << PB5);
		_delay_ms(0.1);
		PORTB = 0;
		delay(pwm / 102.4);



	}
	return 0;

}

