# Opdracht 5

> ET	Phone	home

1. Elke	IMTHE-Box	bevat	unieke	componenten.	Zoek	
naar	 de	 datasheets	 van	 deze	 componenten en	
maak	 een	 kort	 verslag	 per	 component	 over	 de	
protocollen	 die	 gebruikt	 worden	 en	 hoe	 je	 dit	
moet	gebruiken	vanuit	de	AVR	code.

**2. Zoek	naar	een	library	op	internet	om	het	HD44780	
display	 te	 kunnen	 besturen	 en	 maak	 een	
programma dat	 jouw	 naam	 en	 studentnummer	
op	het	display	laat	zien.**

## Aanpak en Uitvoering

Deze opdracht was gemakkelijker dan de vorige. We mochten gebruik maken van een library. Op google ben ik wezen zoeken naar een library voor de HD44780. Na enige tijd vond ik deze website: https://community.atmel.com/projects/hd44780-library. Precies wat ik zocht. 

Het aankoppelen van de HD44780 deed ik via de volgende link: https://www.arduino.cc/en/Tutorial/LiquidCrystalDisplay. Hier werd precies aangeven hoe ik wat moest aansluiten. Op die website hebben ze een potmeter aangesloten. Voor mijn configuratie is deze overbodig. Deze stelt alleen de scherpte van het scherm. Wanneer deze pin op een ground staat, staat het beeldscherm altijd aan.

De code die ik zelf nog moest schrijven was zeer simpel. Initialiseren van het scherm, het display leegmaken en als laatst mijn naam invoeren. 




## Afbeelding

![Opdracht 5 - ET	Phone	home - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_5.2/assets/20180404_194625.jpg)

## Video

https://www.dropbox.com/s/ce1aicsco2hbtk9/Opdracht5b.mp4?dl=0

## Breadboard schema

![Opdracht 5 - ET	Phone	home - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_5.2/assets/frit5b.png)

## Code
```c
/*
 * hd44780.c
 *
 *  Created on: 15 mrt. 2018
 *      Author: jande_000
 */

/*****************************************************************************
Title  :   HD44780 Library
Author :   SA Development
Version:   1.11
*****************************************************************************/

#include "avr\pgmspace.h"
#include "hd44780.h"
#include "avr\sfr_defs.h"
#if (USE_ADELAY_LIBRARY==1)
  #include "adelay.h"
#else
  #define Delay_ns(__ns) \
    if((unsigned long) (F_CPU/1000000000.0 * __ns) != F_CPU/1000000000.0 * __ns)\
          __builtin_avr_delay_cycles((unsigned long) ( F_CPU/1000000000.0 * __ns)+1);\
    else __builtin_avr_delay_cycles((unsigned long) ( F_CPU/1000000000.0 * __ns))
  #define Delay_us(__us) \
    if((unsigned long) (F_CPU/1000000.0 * __us) != F_CPU/1000000.0 * __us)\
          __builtin_avr_delay_cycles((unsigned long) ( F_CPU/1000000.0 * __us)+1);\
    else __builtin_avr_delay_cycles((unsigned long) ( F_CPU/1000000.0 * __us))
  #define Delay_ms(__ms) \
    if((unsigned long) (F_CPU/1000.0 * __ms) != F_CPU/1000.0 * __ms)\
          __builtin_avr_delay_cycles((unsigned long) ( F_CPU/1000.0 * __ms)+1);\
    else __builtin_avr_delay_cycles((unsigned long) ( F_CPU/1000.0 * __ms))
  #define Delay_s(__s) \
    if((unsigned long) (F_CPU/1.0 * __s) != F_CPU/1.0 * __s)\
          __builtin_avr_delay_cycles((unsigned long) ( F_CPU/1.0 * __s)+1);\
    else __builtin_avr_delay_cycles((unsigned long) ( F_CPU/1.0 * __s))
#endif

#if !defined(LCD_BITS) || (LCD_BITS!=4 && LCD_BITS!=8)
  #error LCD_BITS is not defined or not valid.
#endif

#if !defined(WAIT_MODE) || (WAIT_MODE!=0 && WAIT_MODE!=1)
  #error WAIT_MODE is not defined or not valid.
#endif

#if !defined(RW_LINE_IMPLEMENTED) || (RW_LINE_IMPLEMENTED!=0 && RW_LINE_IMPLEMENTED!=1)
  #error RW_LINE_IMPLEMENTED is not defined or not valid.
#endif

#if (WAIT_MODE==1 && RW_LINE_IMPLEMENTED!=1)
  #error WAIT_MODE=1 requires RW_LINE_IMPLEMENTED=1.
#endif

#if !defined(LCD_DISPLAYS) || (LCD_DISPLAYS<1) || (LCD_DISPLAYS>4)
  #error LCD_DISPLAYS is not defined or not valid.
#endif

// Constants/Macros
#define PIN(x) (*(&x - 2))           // Address of Data Direction Register of Port X
#define DDR(x) (*(&x - 1))           // Address of Input Register of Port X

//PORT defines
#define lcd_rs_port_low() LCD_RS_PORT&=~_BV(LCD_RS_PIN)
#if RW_LINE_IMPLEMENTED==1
  #define lcd_rw_port_low() LCD_RW_PORT&=~_BV(LCD_RW_PIN)
#endif
#define lcd_db0_port_low() LCD_DB0_PORT&=~_BV(LCD_DB0_PIN)
#define lcd_db1_port_low() LCD_DB1_PORT&=~_BV(LCD_DB1_PIN)
#define lcd_db2_port_low() LCD_DB2_PORT&=~_BV(LCD_DB2_PIN)
#define lcd_db3_port_low() LCD_DB3_PORT&=~_BV(LCD_DB3_PIN)
#define lcd_db4_port_low() LCD_DB4_PORT&=~_BV(LCD_DB4_PIN)
#define lcd_db5_port_low() LCD_DB5_PORT&=~_BV(LCD_DB5_PIN)
#define lcd_db6_port_low() LCD_DB6_PORT&=~_BV(LCD_DB6_PIN)
#define lcd_db7_port_low() LCD_DB7_PORT&=~_BV(LCD_DB7_PIN)

#define lcd_rs_port_high() LCD_RS_PORT|=_BV(LCD_RS_PIN)
#if RW_LINE_IMPLEMENTED==1
  #define lcd_rw_port_high() LCD_RW_PORT|=_BV(LCD_RW_PIN)
#endif
#define lcd_db0_port_high() LCD_DB0_PORT|=_BV(LCD_DB0_PIN)
#define lcd_db1_port_high() LCD_DB1_PORT|=_BV(LCD_DB1_PIN)
#define lcd_db2_port_high() LCD_DB2_PORT|=_BV(LCD_DB2_PIN)
#define lcd_db3_port_high() LCD_DB3_PORT|=_BV(LCD_DB3_PIN)
#define lcd_db4_port_high() LCD_DB4_PORT|=_BV(LCD_DB4_PIN)
#define lcd_db5_port_high() LCD_DB5_PORT|=_BV(LCD_DB5_PIN)
#define lcd_db6_port_high() LCD_DB6_PORT|=_BV(LCD_DB6_PIN)
#define lcd_db7_port_high() LCD_DB7_PORT|=_BV(LCD_DB7_PIN)

#define lcd_rs_port_set(value) if (value) lcd_rs_port_high(); else lcd_rs_port_low();
#if RW_LINE_IMPLEMENTED==1
  #define lcd_rw_port_set(value) if (value) lcd_rw_port_high(); else lcd_rw_port_low();
#endif
#define lcd_db0_port_set(value) if (value) lcd_db0_port_high(); else lcd_db0_port_low();
#define lcd_db1_port_set(value) if (value) lcd_db1_port_high(); else lcd_db1_port_low();
#define lcd_db2_port_set(value) if (value) lcd_db2_port_high(); else lcd_db2_port_low();
#define lcd_db3_port_set(value) if (value) lcd_db3_port_high(); else lcd_db3_port_low();
#define lcd_db4_port_set(value) if (value) lcd_db4_port_high(); else lcd_db4_port_low();
#define lcd_db5_port_set(value) if (value) lcd_db5_port_high(); else lcd_db5_port_low();
#define lcd_db6_port_set(value) if (value) lcd_db6_port_high(); else lcd_db6_port_low();
#define lcd_db7_port_set(value) if (value) lcd_db7_port_high(); else lcd_db7_port_low();

//PIN defines
#define lcd_db0_pin_get() (((PIN(LCD_DB0_PORT) & _BV(LCD_DB0_PIN))==0)?0:1)
#define lcd_db1_pin_get() (((PIN(LCD_DB1_PORT) & _BV(LCD_DB1_PIN))==0)?0:1)
#define lcd_db2_pin_get() (((PIN(LCD_DB2_PORT) & _BV(LCD_DB2_PIN))==0)?0:1)
#define lcd_db3_pin_get() (((PIN(LCD_DB3_PORT) & _BV(LCD_DB3_PIN))==0)?0:1)
#define lcd_db4_pin_get() (((PIN(LCD_DB4_PORT) & _BV(LCD_DB4_PIN))==0)?0:1)
#define lcd_db5_pin_get() (((PIN(LCD_DB5_PORT) & _BV(LCD_DB5_PIN))==0)?0:1)
#define lcd_db6_pin_get() (((PIN(LCD_DB6_PORT) & _BV(LCD_DB6_PIN))==0)?0:1)
#define lcd_db7_pin_get() (((PIN(LCD_DB7_PORT) & _BV(LCD_DB7_PIN))==0)?0:1)

//DDR defines
#define lcd_rs_ddr_low() DDR(LCD_RS_PORT)&=~_BV(LCD_RS_PIN)
#if RW_LINE_IMPLEMENTED==1
  #define lcd_rw_ddr_low() DDR(LCD_RW_PORT)&=~_BV(LCD_RW_PIN)
#endif
#define lcd_db0_ddr_low() DDR(LCD_DB0_PORT)&=~_BV(LCD_DB0_PIN)
#define lcd_db1_ddr_low() DDR(LCD_DB1_PORT)&=~_BV(LCD_DB1_PIN)
#define lcd_db2_ddr_low() DDR(LCD_DB2_PORT)&=~_BV(LCD_DB2_PIN)
#define lcd_db3_ddr_low() DDR(LCD_DB3_PORT)&=~_BV(LCD_DB3_PIN)
#define lcd_db4_ddr_low() DDR(LCD_DB4_PORT)&=~_BV(LCD_DB4_PIN)
#define lcd_db5_ddr_low() DDR(LCD_DB5_PORT)&=~_BV(LCD_DB5_PIN)
#define lcd_db6_ddr_low() DDR(LCD_DB6_PORT)&=~_BV(LCD_DB6_PIN)
#define lcd_db7_ddr_low() DDR(LCD_DB7_PORT)&=~_BV(LCD_DB7_PIN)

#define lcd_rs_ddr_high() DDR(LCD_RS_PORT)|=_BV(LCD_RS_PIN)
#if RW_LINE_IMPLEMENTED==1
  #define lcd_rw_ddr_high() DDR(LCD_RW_PORT)|=_BV(LCD_RW_PIN)
#endif
#define lcd_db0_ddr_high() DDR(LCD_DB0_PORT)|=_BV(LCD_DB0_PIN)
#define lcd_db1_ddr_high() DDR(LCD_DB1_PORT)|=_BV(LCD_DB1_PIN)
#define lcd_db2_ddr_high() DDR(LCD_DB2_PORT)|=_BV(LCD_DB2_PIN)
#define lcd_db3_ddr_high() DDR(LCD_DB3_PORT)|=_BV(LCD_DB3_PIN)
#define lcd_db4_ddr_high() DDR(LCD_DB4_PORT)|=_BV(LCD_DB4_PIN)
#define lcd_db5_ddr_high() DDR(LCD_DB5_PORT)|=_BV(LCD_DB5_PIN)
#define lcd_db6_ddr_high() DDR(LCD_DB6_PORT)|=_BV(LCD_DB6_PIN)
#define lcd_db7_ddr_high() DDR(LCD_DB7_PORT)|=_BV(LCD_DB7_PIN)

#define lcd_rs_ddr_set(value) if (value) lcd_rs_ddr_high(); else lcd_rs_ddr_low();
#if RW_LINE_IMPLEMENTED==1
  #define lcd_rw_ddr_set(value) if (value) lcd_rw_ddr_high(); else lcd_rw_ddr_low();
#endif
#define lcd_db0_ddr_set(value) if (value) lcd_db0_ddr_high(); else lcd_db0_ddr_low();
#define lcd_db1_ddr_set(value) if (value) lcd_db1_ddr_high(); else lcd_db1_ddr_low();
#define lcd_db2_ddr_set(value) if (value) lcd_db2_ddr_high(); else lcd_db2_ddr_low();
#define lcd_db3_ddr_set(value) if (value) lcd_db3_ddr_high(); else lcd_db3_ddr_low();
#define lcd_db4_ddr_set(value) if (value) lcd_db4_ddr_high(); else lcd_db4_ddr_low();
#define lcd_db5_ddr_set(value) if (value) lcd_db5_ddr_high(); else lcd_db5_ddr_low();
#define lcd_db6_ddr_set(value) if (value) lcd_db6_ddr_high(); else lcd_db6_ddr_low();
#define lcd_db7_ddr_set(value) if (value) lcd_db7_ddr_high(); else lcd_db7_ddr_low();

#if (WAIT_MODE==1 && RW_LINE_IMPLEMENTED==1)
static unsigned char PrevCmdInvolvedAddressCounter=0;
#endif

#if (LCD_DISPLAYS>1)
static unsigned char ActiveDisplay=1;
#endif

static inline void lcd_e_port_low()
{
  #if (LCD_DISPLAYS>1)
  switch (ActiveDisplay)
    {
      case 2 : LCD_E2_PORT&=~_BV(LCD_E2_PIN);
               break;
      #if (LCD_DISPLAYS>=3)
      case 3 : LCD_E3_PORT&=~_BV(LCD_E3_PIN);
               break;
      #endif
      #if (LCD_DISPLAYS==4)
      case 4 : LCD_E4_PORT&=~_BV(LCD_E4_PIN);
               break;
      #endif
      default :
  #endif
                LCD_E_PORT&=~_BV(LCD_E_PIN);
  #if (LCD_DISPLAYS>1)
    }
  #endif
}

static inline void lcd_e_port_high()
{
  #if (LCD_DISPLAYS>1)
  switch (ActiveDisplay)
    {
      case 2 : LCD_E2_PORT|=_BV(LCD_E2_PIN);
               break;
      #if (LCD_DISPLAYS>=3)
      case 3 : LCD_E3_PORT|=_BV(LCD_E3_PIN);
               break;
      #endif
      #if (LCD_DISPLAYS==4)
      case 4 : LCD_E4_PORT|=_BV(LCD_E4_PIN);
               break;
      #endif
      default :
  #endif
                LCD_E_PORT|=_BV(LCD_E_PIN);
  #if (LCD_DISPLAYS>1)
    }
  #endif
}

static inline void lcd_e_ddr_low()
{
  #if (LCD_DISPLAYS>1)
  switch (ActiveDisplay)
    {
      case 2 : DDR(LCD_E2_PORT)&=~_BV(LCD_E2_PIN);
               break;
      #if (LCD_DISPLAYS>=3)
      case 3 : DDR(LCD_E3_PORT)&=~_BV(LCD_E3_PIN);
               break;
      #endif
      #if (LCD_DISPLAYS==4)
      case 4 : DDR(LCD_E4_PORT)&=~_BV(LCD_E4_PIN);
               break;
      #endif
      default :
  #endif
                DDR(LCD_E_PORT)&=~_BV(LCD_E_PIN);
  #if (LCD_DISPLAYS>1)
    }
  #endif
}

static inline void lcd_e_ddr_high()
{
  #if (LCD_DISPLAYS>1)
  switch (ActiveDisplay)
    {
      case 2 : DDR(LCD_E2_PORT)|=_BV(LCD_E2_PIN);
               break;
      #if (LCD_DISPLAYS>=3)
      case 3 : DDR(LCD_E3_PORT)|=_BV(LCD_E3_PIN);
               break;
      #endif
      #if (LCD_DISPLAYS==4)
      case 4 : DDR(LCD_E4_PORT)|=_BV(LCD_E4_PIN);
               break;
      #endif
      default :
  #endif
                DDR(LCD_E_PORT)|=_BV(LCD_E_PIN);
  #if (LCD_DISPLAYS>1)
    }
  #endif
}


/*************************************************************************
loops while lcd is busy, returns address counter
*************************************************************************/
#if (WAIT_MODE==1 && RW_LINE_IMPLEMENTED==1)
static uint8_t lcd_read(uint8_t rs);

static void lcd_waitbusy(void)
  {
    register uint8_t c;
    unsigned int ul1=0;

    while ( ((c=lcd_read(0)) & (1<<LCD_BUSY)) && ul1<((F_CPU/16384>=16)?F_CPU/16384:16))     // Wait Until Busy Flag is Cleared
      ul1++;
  }
#endif


/*************************************************************************
Low-level function to read byte from LCD controller
Input:    rs     1: read data
                 0: read busy flag / address counter
Returns:  byte read from LCD controller
*************************************************************************/
#if RW_LINE_IMPLEMENTED==1
static uint8_t lcd_read(uint8_t rs)
  {
    uint8_t data;

    #if (WAIT_MODE==1 && RW_LINE_IMPLEMENTED==1)
    if (rs)
      lcd_waitbusy();
      if (PrevCmdInvolvedAddressCounter)
        {
          Delay_us(5);
          PrevCmdInvolvedAddressCounter=0;
        }
    #endif

    if (rs)
      {
        lcd_rs_port_high();                             // RS=1: Read Data
        #if (WAIT_MODE==1 && RW_LINE_IMPLEMENTED==1)
        PrevCmdInvolvedAddressCounter=1;
        #endif
      }
    else lcd_rs_port_low();                           // RS=0: Read Busy Flag


    lcd_rw_port_high();                               // RW=1: Read Mode

    #if LCD_BITS==4
      lcd_db7_ddr_low();                              // Configure Data Pins as Input
      lcd_db6_ddr_low();
      lcd_db5_ddr_low();
      lcd_db4_ddr_low();

      lcd_e_port_high();                              // Read High Nibble First
      Delay_ns(500);

      data=lcd_db4_pin_get() << 4 | lcd_db5_pin_get() << 5 |
           lcd_db6_pin_get() << 6 | lcd_db7_pin_get() << 7;

      lcd_e_port_low();
      Delay_ns(500);

      lcd_e_port_high();                              // Read Low Nibble
      Delay_ns(500);

      data|=lcd_db4_pin_get() << 0 | lcd_db5_pin_get() << 1 |
            lcd_db6_pin_get() << 2 | lcd_db7_pin_get() << 3;

      lcd_e_port_low();

      lcd_db7_ddr_high();                             // Configure Data Pins as Output
      lcd_db6_ddr_high();
      lcd_db5_ddr_high();
      lcd_db4_ddr_high();

      lcd_db7_port_high();                            // Pins High (Inactive)
      lcd_db6_port_high();
      lcd_db5_port_high();
      lcd_db4_port_high();
    #else //using 8-Bit-Mode
      lcd_db7_ddr_low();                              // Configure Data Pins as Input
      lcd_db6_ddr_low();
      lcd_db5_ddr_low();
      lcd_db4_ddr_low();
      lcd_db3_ddr_low();
      lcd_db2_ddr_low();
      lcd_db1_ddr_low();
      lcd_db0_ddr_low();

      lcd_e_port_high();
      Delay_ns(500);

      data=lcd_db7_pin_get() << 7 | lcd_db6_pin_get() << 6 |
           lcd_db5_pin_get() << 5 | lcd_db4_pin_get() << 4 |
           lcd_db3_pin_get() << 3 | lcd_db2_pin_get() << 2 |
           lcd_db1_pin_get() << 1 | lcd_db0_pin_get();

      lcd_e_port_low();

      lcd_db7_ddr_high();                             // Configure Data Pins as Output
      lcd_db6_ddr_high();
      lcd_db5_ddr_high();
      lcd_db4_ddr_high();
      lcd_db3_ddr_high();
      lcd_db2_ddr_high();
      lcd_db1_ddr_high();
      lcd_db0_ddr_high();

      lcd_db7_port_high();                            // Pins High (Inactive)
      lcd_db6_port_high();
      lcd_db5_port_high();
      lcd_db4_port_high();
      lcd_db3_port_high();
      lcd_db2_port_high();
      lcd_db1_port_high();
      lcd_db0_port_high();
    #endif

    lcd_rw_port_low();

    #if (WAIT_MODE==0 || RW_LINE_IMPLEMENTED==0)
    if (rs)
      Delay_us(40);
    else Delay_us(1);
    #endif
    return data;
  }

uint8_t lcd_getc()
  {
    return lcd_read(1);
  }

#endif

/*************************************************************************
Low-level function to write byte to LCD controller
Input:    data   byte to write to LCD
          rs     1: write data
                 0: write instruction
Returns:  none
*************************************************************************/
static void lcd_write(uint8_t data,uint8_t rs)
  {
    #if (WAIT_MODE==1 && RW_LINE_IMPLEMENTED==1)
      lcd_waitbusy();
      if (PrevCmdInvolvedAddressCounter)
        {
          Delay_us(5);
          PrevCmdInvolvedAddressCounter=0;
        }
    #endif

    if (rs)
      {
        lcd_rs_port_high();                            // RS=1: Write Character
        #if (WAIT_MODE==1 && RW_LINE_IMPLEMENTED==1)
        PrevCmdInvolvedAddressCounter=1;
        #endif
      }
    else
      {
        lcd_rs_port_low();                          // RS=0: Write Command
        #if (WAIT_MODE==1 && RW_LINE_IMPLEMENTED==1)
        PrevCmdInvolvedAddressCounter=0;
        #endif
      }

    #if LCD_BITS==4
      lcd_db7_port_set(data&_BV(7));                  //Output High Nibble
      lcd_db6_port_set(data&_BV(6));
      lcd_db5_port_set(data&_BV(5));
      lcd_db4_port_set(data&_BV(4));

      Delay_ns(100);
      lcd_e_port_high();

      Delay_ns(500);
      lcd_e_port_low();

      lcd_db7_port_set(data&_BV(3));                  //Output High Nibble
      lcd_db6_port_set(data&_BV(2));
      lcd_db5_port_set(data&_BV(1));
      lcd_db4_port_set(data&_BV(0));

      Delay_ns(100);
      lcd_e_port_high();

      Delay_ns(500);
      lcd_e_port_low();

      lcd_db7_port_high();                            // All Data Pins High (Inactive)
      lcd_db6_port_high();
      lcd_db5_port_high();
      lcd_db4_port_high();

    #else //using 8-Bit_Mode
      lcd_db7_port_set(data&_BV(7));                  //Output High Nibble
      lcd_db6_port_set(data&_BV(6));
      lcd_db5_port_set(data&_BV(5));
      lcd_db4_port_set(data&_BV(4));
      lcd_db3_port_set(data&_BV(3));                  //Output High Nibble
      lcd_db2_port_set(data&_BV(2));
      lcd_db1_port_set(data&_BV(1));
      lcd_db0_port_set(data&_BV(0));

      Delay_ns(100);
      lcd_e_port_high();
      Delay_ns(500);
      lcd_e_port_low();

      lcd_db7_port_high();                            // All Data Pins High (Inactive)
      lcd_db6_port_high();
      lcd_db5_port_high();
      lcd_db4_port_high();
      lcd_db3_port_high();
      lcd_db2_port_high();
      lcd_db1_port_high();
      lcd_db0_port_high();
    #endif

    #if (WAIT_MODE==0 || RW_LINE_IMPLEMENTED==0)
      if (!rs && data<=((1<<LCD_CLR) | (1<<LCD_HOME))) // Is command clrscr or home?
        Delay_us(1640);
      else Delay_us(40);
    #endif
  }

/*************************************************************************
Send LCD controller instruction command
Input:   instruction to send to LCD controller, see HD44780 data sheet
Returns: none
*************************************************************************/
void lcd_command(uint8_t cmd)
  {
    lcd_write(cmd,0);
  }

/*************************************************************************
Set cursor to specified position
Input:    pos position
Returns:  none
*************************************************************************/
void lcd_goto(uint8_t pos)
  {
    lcd_command((1<<LCD_DDRAM)+pos);
  }


/*************************************************************************
Clear screen
Input:    none
Returns:  none
*************************************************************************/
void lcd_clrscr()
  {
    lcd_command(1<<LCD_CLR);
  }


/*************************************************************************
Return home
Input:    none
Returns:  none
*************************************************************************/
void lcd_home()
  {
    lcd_command(1<<LCD_HOME);
  }


/*************************************************************************
Display character
Input:    character to be displayed
Returns:  none
*************************************************************************/
void lcd_putc(char c)
  {
    lcd_write(c,1);
  }


/*************************************************************************
Display string
Input:    string to be displayed
Returns:  none
*************************************************************************/
void lcd_puts(const char *s)
  {
    register char c;

    while ((c=*s++))
      lcd_putc(c);
  }


/*************************************************************************
Display string from flash
Input:    string to be displayed
Returns:  none
*************************************************************************/
void lcd_puts_P(const char *progmem_s)
  {
    register char c;

    while ((c=pgm_read_byte(progmem_s++)))
      lcd_putc(c);
  }

/*************************************************************************
Initialize display
Input:    none
Returns:  none
*************************************************************************/
void lcd_init()
  {
    //Set All Pins as Output
    lcd_e_ddr_high();
    lcd_rs_ddr_high();
    #if RW_LINE_IMPLEMENTED==1
      lcd_rw_ddr_high();
    #endif
    lcd_db7_ddr_high();
    lcd_db6_ddr_high();
    lcd_db5_ddr_high();
    lcd_db4_ddr_high();
    #if LCD_BITS==8
      lcd_db3_ddr_high();
      lcd_db2_ddr_high();
      lcd_db1_ddr_high();
      lcd_db0_ddr_high();
    #endif

    //Set All Control Lines Low
    lcd_e_port_low();
    lcd_rs_port_low();
    #if RW_LINE_IMPLEMENTED==1
      lcd_rw_port_low();
    #endif

    //Set All Data Lines High
    lcd_db7_port_high();
    lcd_db6_port_high();
    lcd_db5_port_high();
    lcd_db4_port_high();
    #if LCD_BITS==8
      lcd_db3_port_high();
      lcd_db2_port_high();
      lcd_db1_port_high();
      lcd_db0_port_high();
    #endif

    //Startup Delay
    Delay_ms(DELAY_RESET);

    //Initialize Display
    lcd_db7_port_low();
    lcd_db6_port_low();
    Delay_ns(100);
    lcd_e_port_high();
    Delay_ns(500);
    lcd_e_port_low();

    Delay_us(4100);

    lcd_e_port_high();
    Delay_ns(500);
    lcd_e_port_low();

    Delay_us(100);

    lcd_e_port_high();
    Delay_ns(500);
    lcd_e_port_low();

    Delay_us(40);

    //Init differs between 4-bit and 8-bit from here
    #if (LCD_BITS==4)
      lcd_db4_port_low();
      Delay_ns(100);
      lcd_e_port_high();
      Delay_ns(500);
      lcd_e_port_low();
      Delay_us(40);

      lcd_db4_port_low();
      Delay_ns(100);
      lcd_e_port_high();
      Delay_ns(500);
      lcd_e_port_low();
      Delay_ns(500);

      #if (LCD_DISPLAYS==1)
        if (LCD_DISPLAY_LINES>1)
          lcd_db7_port_high();
      #else
        unsigned char c;
        switch (ActiveDisplay)
          {
            case 1 : c=LCD_DISPLAY_LINES; break;
            case 2 : c=LCD_DISPLAY2_LINES; break;
            #if (LCD_DISPLAYS>=3)
            case 3 : c=LCD_DISPLAY3_LINES; break;
            #endif
            #if (LCD_DISPLAYS==4)
            case 4 : c=LCD_DISPLAY4_LINES; break;
            #endif
          }
        if (c>1)
          lcd_db7_port_high();
      #endif

      Delay_ns(100);
      lcd_e_port_high();
      Delay_ns(500);
      lcd_e_port_low();
      Delay_us(40);
    #else
      #if (LCD_DISPLAYS==1)
        if (LCD_DISPLAY_LINES<2)
          lcd_db3_port_low();
      #else
        unsigned char c;
        switch (ActiveDisplay)
          {
            case 1 : c=LCD_DISPLAY_LINES; break;
            case 2 : c=LCD_DISPLAY2_LINES; break;
            #if (LCD_DISPLAYS>=3)
            case 3 : c=LCD_DISPLAY3_LINES; break;
            #endif
            #if (LCD_DISPLAYS==4)
            case 4 : c=LCD_DISPLAY4_LINES; break;
            #endif
          }
        if (c<2)
          lcd_db3_port_low();
      #endif

      lcd_db2_port_low();
      Delay_ns(100);
      lcd_e_port_high();
      Delay_ns(500);
      lcd_e_port_low();
      Delay_us(40);
    #endif

    //Display Off
    lcd_command(_BV(LCD_DISPLAYMODE));

    //Display Clear
    lcd_clrscr();

    //Entry Mode Set
    lcd_command(_BV(LCD_ENTRY_MODE) | _BV(LCD_ENTRY_INC));

    //Display On
    lcd_command(_BV(LCD_DISPLAYMODE) | _BV(LCD_DISPLAYMODE_ON));
  }

#if (LCD_DISPLAYS>1)
void lcd_use_display(int ADisplay)
  {
    if (ADisplay>=1 && ADisplay<=LCD_DISPLAYS)
      ActiveDisplay=ADisplay;
  }
#endif




int main(void){


	lcd_init();
	lcd_clrscr();
	lcd_puts("JanZwaan 1090202");



	while(1){


	return 0;
	}
}
```

## Datasheets

### Arduino Nano
![Schematic Arduino Nano - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_1/assets/nano.png)

### HD44780
![Schematic HD44780 - Afbeelding](https://raw.githubusercontent.com/Jandepiel/Imthe1/master/O_5.2/assets/scherm.png)



