#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

#include "LCDI2C.h"

#ifndef _BV
#define _BV(bit)        (1<<(bit))
#endif
#ifndef sbi
#define sbi(reg,bit)    reg |= (_BV(bit))
#endif

#ifndef cbi
#define cbi(reg,bit)    reg &= ~(_BV(bit))
#endif

#ifndef tbi
#define tbi(reg,bit)    reg ^= (_BV(bit))
#endif



int main() {
  //0x27 - adres urzadzenia na I2C
  LCD_I2C Lcd = LCD_I2C(0x27);
  _delay_ms(100);
  Lcd.backLightOn();

    PORTB = 1;
  DDRB = 0;
  // to ma chyba kontekst przycisków 
  // Na laboratoryjnym Arduino działa z DDRD i PORTD
// Na wokwi z DDRB i PORTB
  uint8_t i = 0;
  char text[20];
  while (1) {
     sprintf(text, "%d", i);
     Lcd.writeText(text);
    _delay_ms(100);
    
     if (bit_is_set(PINB, 0)){
        if (i != 100){
          
      
          i++;
          Lcd.clear();
          _delay_ms(50);
              Lcd.goTo(0, 1);
          sprintf(text, "%d", i);
          Lcd.writeText(text);
        }
          
      } 
          if (bit_is_set(PINB, 1)){
            if( i != -100){
          i--;
                    Lcd.clear();
          _delay_ms(50);
              Lcd.goTo(0, 1);
          sprintf(text, "%d", i);
          Lcd.writeText(text);
          }
      } 
  
    Lcd.clear();

    Lcd.goTo(0, 1);
    sprintf(text, "%d", i);
    Lcd.writeText(text);
    _delay_ms(100);
  }

  
}
