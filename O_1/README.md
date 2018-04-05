# Opdracht 1

> Blink once to accept

Maak	een	‘Blink	led’	programma,	waar	twee	leds	omen-om
aan	 en	 uit	 gaan.	 Het	 knipperen	 van	 de	 leds	
moet	traag	verlopen,	zodat	het	knippereffect	zichtbaar	
is	met	het	blote	oog.

## Aanpak en Uitvoering

Deze opdracht was nog wel erg simpel. De lessen van IMTHE1 hebben ervoor gezorgd, dat ik deze opdracht zonder problemen kon oplossen. Daarnaast stond er in het boek "Make: AVR Programming" een goed voorbeeld. Dit is op bladzijde 44.

## Afbeelding

![Opdracht 1 - Blink Once To Accept - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_1/assets/plaatje1.jpg)

## Video

https://www.dropbox.com/s/msih59a1nqraati/Opdracht1.mp4?dl=0

## Breadboard schema

![Schematic opdracht 1 - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_1/assets/Frit1.png)

## Code
```c
/*
 * main.c
 *
 *  Created on: 14 feb. 2018
 *      Author: jande_000
 */
#include <avr/io.h>
#include <util/delay.h>

int main(void){

    DDRC = 0b00000011; //Zet PC0 en PC1 als output

    while(1){
        //programma

        PORTC = 0b00000001; //PC0 is aan
        _delay_ms(2000); //Wacht 2 seconden
        PORTC = 0b00000010; //PC1 is aan
        _delay_ms(2000);
    }
    return 0;

}
```

## Datasheets

![Schematic Arduino Nano - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_1/assets/nano.png)

