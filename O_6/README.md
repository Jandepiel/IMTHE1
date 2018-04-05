# EX

> Extra	opdracht

De	extra	opdracht kan	je	inzetten	 ter	vervanging	van	
één opdracht	die	je	niet	gelukt	is.	Geef	bij	je	verslag	
aan	welke	opdracht	je	vervangt.

Gebruik	het	‘serialOrgan’	programma	van	hoofdstuk	5	
om	 een	 eigen melodie	 te	 maken.	 Jouw	 programma	
gebruikt	geen	seriële	verbinding,	maar	gaat	zelfstandig	
een	melodie	spelen	wanneer	de	AVR	aangezet	wordt.

## Aanpak en Uitvoering

In het boek was ik naar serial.Organ op zoek. Deze heb ik gevonden en daarna ook het internet opgezocht naar hoe deze precies werkt. De tonen waren niet in het boek meegeven. Dit komt omdat dit een lange lijst is. Om een toon te laten spelen, moet de functie playNote() worden aangeroepen. Hier kan elke noot worden ingevoerd. Daarnaast kan de functie rest() worden aangeroepen om een tussenpauze te krijgen tussen de noten. Door alle seriële communicatie weg te halen, kon ik het programma constant laten loopen en dus constant hetzelfde melodie laten spelen.

Na het onderzoeken hoe het precies werkte, ben ik op zoek gegaan naar een melodie. De melodie die ik wou gebruiken was Funky Town van Lipps Inc. Een heel iconische melodie.  Op youtube kwam ik de piano noten tegen: https://www.youtube.com/watch?v=nbrUq0p-8HM

De tonen zijn c-c-A-c-g-g-c-f-e-c. Deze heb ik vertaald in de tonen van het programma. Dan zijn de tonen c5-c5-Ax4-c5-g4-g4-c5-f5-e5-c5.




## Afbeelding

![Opdracht 5 - ET	Phone	home - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_6/assets/Naamloos.png)

## Video

https://www.dropbox.com/s/l1n3kz11ygmzqih/Opdracht6.mp4?dl=0

## Breadboard schema

![EX - Extra opdracht - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_6/assets/frit6.png)

## Code
```c


#include <avr/io.h>
#include <avr/delay.h>
#include "scale16.h"

void playNote(uint16_t period, uint16_t duration) {
  uint16_t elapsed;
  uint16_t i;
  for (elapsed = 0; elapsed < duration; elapsed += period) {
                     /* For loop with variable delay selects the pitch */
    for (i = 0; i < period; i++) {
      _delay_us(1);
    }
    PORTD ^= (1 << PD6);
  }
}


void rest(uint16_t duration) {
  do {
    _delay_us(1);
  } while (--duration);
}


#define NOTE_DURATION     0xFF00     /* determines long note length */

int main(void) {

  // -------- Inits --------- //
  DDRD |= (1 << PD6);                 /* speaker for output */

  uint16_t currentNoteLength = NOTE_DURATION; /*Lengte van een noot*/


  // ------ Event loop ------ //
  while (1) {

	  //Alle noten die gespeeld moeten worden

	  playNote(C5, currentNoteLength);
	  rest(currentNoteLength);

	  playNote(C5, currentNoteLength);
	  rest(currentNoteLength);

	  playNote(Ax4, currentNoteLength);
	  rest(currentNoteLength);

	  playNote(C5, currentNoteLength);
	  rest(currentNoteLength);

	  playNote(G4, currentNoteLength);
	  rest(currentNoteLength);

	  playNote(G4, currentNoteLength);
	  rest(currentNoteLength);

	  playNote(C5, currentNoteLength);
	  rest(currentNoteLength);

	  playNote(F5, currentNoteLength);
	  playNote(F5, currentNoteLength);
	  rest(currentNoteLength);

	  playNote(E5, currentNoteLength);
	  playNote(E5, currentNoteLength);
	  rest(currentNoteLength);

	  playNote(C5, currentNoteLength);


	  rest(currentNoteLength);
	  rest(currentNoteLength);



  }
  return 0;
}


```

## Datasheets

### Arduino Nano
![Schematic Arduino Nano - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_1/assets/nano.png)



