# Opdracht 4

> Led there be light

1. Creëer	een	‘Color	changing	light’	met	het	RGB-led	
op	basis	van	PWM.	De	PWM	moet	in	een	Interrupt	
Service	Routine	(ISR)	worden	afgehandeld.

**2. Maak	 een	 programma	 waarin	 je	 via	 Serial	
communicatie	een	led	aan	 of	 uit	kan	 zetten.	Dit	
mag	 door	 bijvoorbeeld	 het	 karakter	 ‘a’	 of	 ‘u’	 te	
sturen.	 Het	 programma	 geeft	 feedback	 over	 de	
seriële poort	of	het	gelukt	is	ja	of	nee.	Gebruik	niet	
de	 gegeven	 usart.c	 en	 .h	 in	 je	 uitwerking,	 maar	
maak	een	oplossing	in	1	source	bestand.**	

3. Verander	 deelopdracht	 2	 zodat	 binnenkomende	
data	 afgehandeld	 wordt	 in	 een	 interrupt	
(USART_RX_vect)	 zodat	 je	 programma	 (zoals	 in	
het	voorbeeld	van	hoofdstuk	5)	niet	‘eeuwig’	op	
input	 wacht.	 Toon	 aan	 dat	 het	 werkt	 door	 via	
seriële	 communicatie	 een	 ‘r’,	 ‘g’	 of	 ‘b’	 door	 te	
geven	 aan	 de	 AVR	 en	 dat	 dan	 de	
corresponderende	kleur	gaat	pulseren	(PWM	op	1	
kleur).

## Aanpak en Uitvoering

In de lessen hebben wij voorbeelden gekregen van serial communication. Dit heeft mij geholpen met het maken van deze opdracht. De code heb ik verder uitgebreid, want we konden alleen dingen verzenden en ontvangen. Met een paar functies erbij konden ook het ledje aan en uit



## Afbeelding

![Opdracht 4 - Led there be light - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_4.2/assets/20180404_192329.jpg)

## Video

https://www.dropbox.com/s/cvb9vvtuu4czgu1/Opdracht4b.mp4?dl=0

## Breadboard schema

![Opdracht 4 - Led there be light - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_4.2/assets/frit4b.png)

## Code
```c
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


```

## Datasheets

### Arduino Nano
![Schematic Arduino Nano - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_1/assets/nano.png)



