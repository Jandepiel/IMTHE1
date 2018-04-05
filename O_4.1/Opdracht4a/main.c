
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
