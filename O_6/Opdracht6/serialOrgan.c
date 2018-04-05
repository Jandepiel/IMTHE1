
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
