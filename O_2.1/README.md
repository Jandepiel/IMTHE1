# Opdracht 2

> Count	me	in

**1. Maak	een	programma	dat	op	het	7-segment	LED	
display	 herhalend	telt	 van	 0	t/m	 9.	 Gebruik het	
rechter	display	van	de	 twee	en	verwerk functies	
en	bit-shifting	in	je	oplossing.**


2. Breidt	de	eerste	deel-opdracht	uit	zodat	de	twee	
segmenten	samen	van	0	t/m	99	tellen.

## Aanpak en Uitvoering

Bij deze opdracht was heel wat anders dan de vorige opdracht. Zo was de vorige opdracht nog heel simpel en wordt en nu meer van mij gevraagd.
Het plan van aanpak van mij, was eerst uitzoeken hoe een 7 segment display werkt. Volgens de website (https://e-radionica.com/productdata/LD3361BS.pdf) bevond ook hier dezelfde 7 segment display, die ik ook bezit. Trial and Error hebbe ervoor gezorgd dat ik een Common Cathode 7 Segment display heb (Zie bladzijde 29). Nu was het een kwestie onderzoeken hoe elk segment moet worden aangestuurd.
In de lessen is mij geleerd, dat niet elke pin op de Arduino Nano bruikbaar is. Zo kwam ik erachter dat bank B en C beide de pinnen 0 tot 5 hebben. Bank D heeft de pinnen 2 tot 7 die bruikbaar zijn. Een 7 segment display heeft 6 pinnen die ik moet aansturen; A t/m G. Het segment DP is overbodig en neemt alleen pin ruimte in beslag (zie Figuur 1) .

Bij de volgende deel opdracht werd gevraagd om beide 7 segment displays aan te sturen. Voor mij was de beste keuze dus om Bank B of C te gebruiken. Hierdoor hoef ik er maar één werkend te krijgen en bij de tweede alleen de Poort nummer te wijzigen. Mijn keuze was om de bank C te gebruiken. 

Hier ontstond een probleem. 5 pinnen om 6 pinnen aan te sturen. Ik koos ervoor om segment G op bank D te gebruiken. Volgens de eerder benoemde website, sloot ik de A segment op de PC0 en B segment op PC1 enzovoort.

![Opdracht 2 - Count me in - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_2.1/assets/kladblok1.jpg)

Hier is te zien, dat wanneer een 1 moet worden weergegeven, segment C en B hoog moeten zijn. Elk getal is hierop te zien. Segment G staat apart want die staat op de D bank. In de uitwerking van mij, moesten alle pin inverted staan. Hierdoor staan vaak een ~voor een byte. 

Het programma is één for loop, die constant wordt doorgelopen. In deze for loop wordt van 0 tot 9 geteld en opnieuw. Bij elk getal wordt de functie digitalNumber aangeroepen. In deze functie wordt het juiste getal weergegeven. Daarnaast in de functie wordt gebruikt van operatoren en bitshifting, wanneer mogelijk is.


## Afbeelding

![Opdracht 2 - Count me in - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_2.1/assets/plaatje2a.jpg)

## Video

https://www.dropbox.com/s/02pp09xg2zdyi13/Opdracht2a.mp4?dl=0

## Breadboard schema

![Opdracht 2 - Count me in - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_2.1/assets/frit2a.png)

## Code
```c
/*
 * main.c
 *
 *  Created on: 20 feb. 2018
 *      Author: jande_000
 */

#include <avr/io.h>
#include <util/delay.h>


void digitalNumber(uint8_t number){

    //Switch om elk cijfer van 0 t/m 9 te kunnen maken
  switch(number){
    case 0:
      PORTC = (0 << 0);
      PORTD ^= (1 << 7);
      break;
    case 1:
      PORTC = ~0b00000110;
      PORTD |= (1 << 7);
      break;
    case 2:
      PORTC = (111001 << 2);
      PORTD &= ~(1 << 7);
      break;
    case 3:
      PORTC = (1111 << 4);
      PORTD &= ~(1 << 7);
      break;
    case 4:
      PORTC = ~(1011 << 1);
      PORTD &= ~(1 << 7);
      break;
    case 5:
      PORTC = ~(101101 << 0);
      PORTD &= ~(1 << 7);
      break;
    case 6:
      PORTC = ~(111101 << 0);
      PORTD &= ~(1 << 7);
      break;
    case 7:
      PORTC = (11 << 3);
      PORTD ^= (1 << 7);
      break;
    case 8:
      PORTC = (0 << 0);
      PORTD &= ~(1 << 7);
      break;
    case 9:
      PORTC = (1 << 4);
      PORTD &= ~(1 << 7);
      break;
  }
}

int main(void){
  //setup
  DDRC = 0b00111111; //output voor buitenstrepen
  DDRD = 0b10000000; //output voor middenstreep

  digitalNumber(8); //Zet eerst alle pinnen omhoog

  while(1){
    //programma
      for(uint8_t i=0;i<10;i++) //For loop van 0 tot 9
      {
       digitalNumber(i); //Tel van 0 tot 9 en begin opnieuw
       _delay_ms(1000);
      }
  }
  return 0;
}

```

## Datasheets

### Arduino Nano
![Schematic Arduino Nano - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_1/assets/nano.png)


### 7 Segment Display
![Opdracht 2 - Count me in - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_2.1/assets/7segment.png)


Het 7 segment display is hier te vinden https://e-radionica.com/productdata/LD3361BS.pdf