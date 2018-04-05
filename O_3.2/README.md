# Opdracht 3

> ADC baby!

1. Maak	 een	 digitale	 dobbelsteen	
met	9	leds	 (zie	plaatje).	Als	je	op	
een	knop	drukt	geven	de	leds	een	
random	 waarde	 tussen	 1	 en	 6	
weer	op	de	leds zoals	je	dat	kent	
op	een	echte	dobbelsteen.	Hou	bij	
het	 programma	 rekening	 met	
dender-gedrag.

**2. Maak	 een	 programma	 dat	 de	
waarde	 van	 een	 potentiometer	 vertaalt	 in	 een	
geluidssignaal	 tussen	 100	 en	 10.000Hz. Laat	 dit	
signaal	horen	op	de	speaker.**

## Aanpak en Uitvoering

In de les van IMTHE1 hebben wij veel informatie gekregen over deze opdracht. Veel was al gedaan. Daarnaast was de code op bladzijde 136 te vinden. Dit is bijna dezelfde code die ik heb gebruikt. Alleen had ik een andere prescaler gebruikt.
 
De opdracht stelt dat de potentiometer het geluidssignaal bepaalt. Ik lees dus eerst uit wat de waarde is van de potentiometer en vertaal deze hierna naar de speaker. Het geluidssignaal moet tussen de 100 en 10.000Hz zijn. Dit is 0.1ms en 10ms. De divider heeft waardes van 0 tot 1023. Hierdoor delen we de inkomende waarden door 102,3 en hebben we 10ms oftewel 100Hz

Wanneer de inkomende 1 is, wordt er gedeeld 102,3. Dit geeft (samen met de 0.1 beginwaarde) 0,1097ms. Iets uitgebreider dan precies de 100Hz. Maar wanneer de inkomende waarde 0 is, is de waarde 0,1ms. Zo hebben we de waardes tussen de 100 en 10.000 Hz.

De inkomende waardes gaan naar een eigen delay die bepalen hoe vaak hij moet trillen, oftewel hoeveel Hz de speaker heeft.





## Afbeelding

![Opdracht 3 - ADC baby! - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_3.2/assets/20180404_190614.jpg)

## Video

https://www.dropbox.com/s/60sjee34wztxx1f/Opdracht3b.mp4?dl=0

## Breadboard schema

![Opdracht 3 - ADC baby! - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_3.2/assets/frit3b.png)

## Code
```c
/*
 * main.c
 *
 *  Created on: 03 mar. 2018
 *      Author: jande_000
 */
#include <avr/io.h>
#include <util/delay.h>

void initADC(){
    ADMUX |= (1 << REFS0); // Zet op 5V
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); // Zet divider op 128 voor 10 bit precisie
    ADCSRA |= (1 << ADEN); // AD Enable
}

uint16_t readADC(){
    ADCSRA |= (1 << ADSC); //start reading
    loop_until_bit_is_clear(ADCSRA, ADSC); //wait until done
    return ADC; //Geef de ADC waarde
}

void delay(uint16_t value)
{
    for(uint16_t i=0;i<value;i++){ // eigen delay functie voor Hz
        _delay_ms(1);
    }
}

int main(void){
    DDRB = (1 << PB5); //input op PB5
    initADC(); //Start initADC

    while(1){
        //programma
        uint16_t pwm = readADC(); //Lees de waarde van de potentiometer PC0
        PORTB = (1 << PB5); //Speaker maakt geluid
        _delay_ms(0.1); //Beginwaarde delay
        PORTB = 0; //Speaker gaat uit
        delay(pwm / 102.4);//Eigen delay functie, om waarde pwm door te geven
    }
    return 0;

}

```

## Datasheets

### Arduino Nano
![Schematic Arduino Nano - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_1/assets/nano.png)


