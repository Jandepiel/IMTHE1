# Opdracht 4

> Led there be light

**1. Creëer	een	‘Color	changing	light’	met	het	RGB-led	
op	basis	van	PWM.	De	PWM	moet	in	een	Interrupt	
Service	Routine	(ISR)	worden	afgehandeld.**

2. Maak	 een	 programma	 waarin	 je	 via	 Serial	
communicatie	een	led	aan	 of	 uit	kan	 zetten.	Dit	
mag	 door	 bijvoorbeeld	 het	 karakter	 ‘a’	 of	 ‘u’	 te	
sturen.	 Het	 programma	 geeft	 feedback	 over	 de	
seriële poort	of	het	gelukt	is	ja	of	nee.	Gebruik	niet	
de	 gegeven	 usart.c	 en	 .h	 in	 je	 uitwerking,	 maar	
maak	een	oplossing	in	1	source	bestand.	

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

Tijdens de lessen hebben we geleerd hoe timers werken en hoe je PWM gebruikt op bepaalde pinnen van de arduino. Deze code heb ik gebruikt voor mijn opdracht.

Om 3 pinnen te moeten er 3 PWM pinnen worden gebruikt. Ik wist zelf niet precies hoe dit moest, maar door te kijken naar het boek, kwam ik erachter hoe ik 3 pinnen kon gebruiken. Deze pinnen zijn OCR1a, OCR1b en OCR2a. De waardes voor de timers van deze pinnen waren in het boek te vinden.

In mijn oplossing gebruik ik de timer 0 om het fade effect te krijgen. In deze timer wordt eerst rood omlaag gefade van 255 naar 0 en groen omhoog gefade van 0 naar 255. Ik ga alle mogelijkheden langs. Met 3 kleuren, heb je 6 opties. Deze heb ik verwerkt in mijn code. 




## Afbeelding

![Opdracht 4 - Led there be light - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_4.1/assets/20180404_192132.jpg)

## Video

https://www.dropbox.com/s/o0alc9hhva3xhzj/Opdracht4a.mp4?dl=0

## Breadboard schema

![Opdracht 4 - Led there be light - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_4.1/assets/frit4a.png)

## Code
```c

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>


#define LED_PORT   PORTB
#define LED_PIN    PINB
#define LED_DDR    DDRB

#define LED_RED		OCR2A
#define LED_GREEN	OCR1B
#define LED_BLUE	OCR1A


volatile uint8_t brightness1 = 0;
volatile uint8_t brightness2 = 255;
volatile uint8_t state = 0;


volatile uint8_t red = 0;
volatile uint8_t green = 0;
volatile uint8_t blue = 0;



void rgbState() {
	if (state < 6) { //verander state
		state++;
	} else {
		state = 0; //begin positie
	}
}

void initTimer0(){
	TIMSK0 |= (1 << TOIE0);/* overflow interrupt enable */
	TCCR0B |= (1 << CS00) | (1 << CS02); /* both output compare interrupts */
}

static inline void initTimers(void) {
	// Timer 1 A,B
	TCCR1A |= (1 << WGM10); /* Fast PWM mode, 8-bit */
	TCCR1B |= (1 << WGM12); /* Fast PWM mode, pt.2 */
	TCCR1B |= (1 << CS11); /* PWM Freq = F_CPU/8/256 */
	TCCR1A |= (1 << COM1A1); /* PWM output on OCR1A */
	TCCR1A |= (1 << COM1B1); /* PWM output on OCR1B */

	// Timer 2
	TCCR2A |= (1 << WGM20); /* Fast PWM mode */
	TCCR2A |= (1 << WGM21); /* Fast PWM mode, pt.2 */
	TCCR2B |= (1 << CS21); /* PWM Freq = F_CPU/8/256 */
	TCCR2A |= (1 << COM2A1); /* PWM output on OCR2A */
}

ISR(TIMER0_OVF_vect){
	if (brightness1 == 255) { //wanneer brightness 1 gelijk is aan 255 -> rgbState -> nieuwe state
		rgbState();
	}
	brightness1++; //Brightness 1 telt op
	brightness2--; // Brightness 2 telt af

	switch (state) {
			case 0:
				red = brightness1; //Rood omlaag, groen omhoog
				green = brightness2;
				break;
			case 1:
				green = brightness1; //Groen omhoog, blauw omlaag
				blue = brightness2;
				break;
			case 2:
				red = brightness2; // Rood omlaag , blauw omhoog
				blue = brightness1;
				break;
			case 3:
				red = brightness1; // Rood omhoog, blauw omlaag
				blue = brightness2;
				break;
			case 4:
				green = brightness2; // Groen omlaag, blauw omhoog
				blue = brightness1;
				break;
			case 5:
				red = brightness2; // Rood omlaag, groen omlaag -> Begin state
				green = brightness1;
				break;
		}
	//Kleur naar elke led
	LED_RED = red;
	LED_GREEN = green;
	LED_BLUE = blue;
}

int main(void){
	LED_DDR = 0xff; //alle output aan

	// -------- Inits --------- //
	initTimers();
	initTimer0();
	sei();

	while(1){

	}
	return 0;

}


```

## Datasheets

### Arduino Nano
![Schematic Arduino Nano - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_1/assets/nano.png)

### RGB
![Schematic Arduino Nano - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_4.1/assets/rgb.jpg)


