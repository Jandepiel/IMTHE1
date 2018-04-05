# Opdracht 3

> ADC baby!

**1. Maak	 een	 digitale	 dobbelsteen	
met	9	leds	 (zie	plaatje).	Als	je	op	
een	knop	drukt	geven	de	leds	een	
random	 waarde	 tussen	 1	 en	 6	
weer	op	de	leds zoals	je	dat	kent	
op	een	echte	dobbelsteen.	Hou	bij	
het	 programma	 rekening	 met	
dender-gedrag.**

2. Maak	 een	 programma	 dat	 de	
waarde	 van	 een	 potentiometer	 vertaalt	 in	 een	
geluidssignaal	 tussen	 100	 en	 10.000Hz. Laat	 dit	
signaal	horen	op	de	speaker.

## Aanpak en Uitvoering

Op de zijkant van de led-matrix stond 788BS. Deze heb ik opgezocht en ingevoerd in Google. Hier kwam ik bij een 8 x 8 led matrix. Via google afbeeldingen kwam ik een schematic tegen (zie Datasheets LD788BS-SS22)


In de opdracht werd gevraagd om 9 pinnen te gebruiken. De pinnen 5, 2, 7, 11, 15 en 16 maken een 3 x 3 grid, wat ik heb gebruikt. Na alweer trial and error kwam ik erachter dat wanneer het rechts onderste ledje moet branden, pin 5 hoog moet staan en pin 16 laag. Zo is de stroomkring gesloten. 

Wanneer pin 7,11 en 2,15 aan moeten staan, ontstaat er een probleem. Dit kan niet tegelijk. Wanneer dit gebeurd, gaan er 4 pinnen aan. De oplossing is om snel te switchen van 7,11 naar 2,15. 

Een randomgenerator werd in het boek weergegeven (zie Bladzijde 72 Make: AVR Programming). Deze is toegevoegd aan mijn eigen oplossing. In de lessen hebben we oplossing gehad voor het lezen van een button press. Dit is door middel van      if bit_is_clear(PINC, PC0)  Dit heb ik aangepast door, wanneer de button is ingedrukt, de randomgenerator stopt en bitshift, zodat er 8 waardes uitkomen. Wanneer de uitkomst kleiner is dan 7 en groter is dan 0, laat hij een van deze waardes zien. Wanneer dit niet zo is, voert hij opnieuw de randomgenerator uit.




## Afbeelding

![Opdracht 3 - ADC baby! - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_3.1/assets/plaatje3a.jpg)

## Video

https://www.dropbox.com/s/3p139a5y384mdpv/opdracht3a.mp4?dl=0

## Breadboard schema

![Opdracht 3 - ADC baby! - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_3.1/assets/frit3a.png)

## Code
```c
/*
 * main.c
 *
 *  Created on: 28 feb. 2018
 *      Author: jande_000
 */

#include <avr/io.h>
#include <util/delay.h>

uint16_t randomNumber = 0x1234; //random nummer die wordt gebruikt voor een pseudo random number generator
uint8_t cijfer; //Random nummer met 8 waardes

void digitalNumber(uint8_t number){
//Switch voor displayen van de 1 tot 6 ogen van de dobbelsteen
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
      _delay_ms(1.5);//De delay moet overal evenlang duren, anders wordt een getal langer diplayt dan een ander
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
  DDRB = 0b00111111;//Setup van pinnen voor output
  PORTC = (1 << PC0);//Input pin voor button

  while(1){
    //programma
    randomNumber = 1932 * randomNumber + 14253; //Random nummer generator zodat elke keer een gooi wordt gereproduceerd.
    cijfer = (randomNumber >> 8);//Random nummer wordt gebit-shift voor 8 waardes in totaal.

    if (cijfer < 7 && cijfer > 0) //wanneer het getal kleiner is dan 7 en groter is dan 0 ( De getallen 1 t/m 6)
    {
        if bit_is_clear(PINC, PC0) // Wanneer button wordt ingedrukt
        {
            for(uint8_t j=0;j<255;j++) //Laat digitalnumber een aantal seconden zien (tegen dender-gedrag)
            {
                digitalNumber(cijfer); //Display het juiste aantal ogen
                _delay_ms(2);
            }
            digitalNumber(0); //Reset het display
        } else {
            digitalNumber(0); //Wanneer button niet is ingedrukt -> display niks
        }
    } else {
        digitalNumber(0);//Wanneer cijfer gelijk is aan 0 of 7 -> display niks
    }
  }
  return 0;
}


```

## Datasheets

### Arduino Nano
![Schematic Arduino Nano - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_1/assets/nano.png)


### 8 x 8 Led Matrix LD788BS-SS22
![Opdracht 3 - ADC baby! - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_3.1/assets/ledmatrix.png)


De led-matrix is hier te vinden http://www.instructables.com/id/Arduino-LED-Scrolling-Text-Simple-Easy/