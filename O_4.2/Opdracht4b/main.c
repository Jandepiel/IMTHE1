#ifndef BAUD
#define BAUD 9600
#endif

#include <avr/io.h>
#include <avr/delay.h>
#include <util/setbaud.h>

void initUSART(void) {
 /* requires BAUD */
	UBRR0H = UBRRH_VALUE; /* defined in setbaud.h */
	UBRR0L = UBRRL_VALUE;
	#if USE_2X
	UCSR0A |= (1 << U2X0);
	#else
	UCSR0A &= ~(1 << U2X0);
	#endif
	/* Enable USART transmitter/receiver */
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); /* 8 data bits, 1 stop bit */
}

void transmitByte(uint8_t data) {
	/* Wait for empty transmit buffer */
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = data; /* send data */
}

uint8_t receiveByte(void) {
	loop_until_bit_is_set(UCSR0A, RXC0); /* Wait for incoming data */
	return UDR0; /* return register value */
}

// Example of a useful printing command
void printString(const char myString[]) {
	uint8_t i = 0;
	while (myString[i]) {
		transmitByte(myString[i]);
		i++;
	}
}

int main(void){

	initUSART();
	DDRB = (1 << PB1);
	printString("Type 'a' om het lampje te laten branden en 'u' om het lampje uit te doen \n\r");

	while(1){

		uint8_t state = receiveByte();


		if (state == 'a') {
			PORTB = (1 << PB1);

			printString("De lamp is nu aan \n\r");
		} else if (state == 'u') {
			PORTB = (0 << PB1);
			printString("De lamp is nu uit \n\r");

		}

	} return 0;

}
