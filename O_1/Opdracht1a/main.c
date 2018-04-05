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
