#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

#ifndef _BV
#define _BV(bit)        (1<<(bit))
#endif
#ifndef sbi
#define sbi(reg,bit)    reg |= (_BV(bit))
#endif

#ifndef cbi
#define cbi(reg,bit)    reg &= ~(_BV(bit))
#endif

void diodesOn() {
  for (uint8_t i = 0; i < 8; i++) {
    sbi (PORTD, i);
  }
}

void diodesOff() {
  for (uint8_t i = 0; i < 8; i++) {
    cbi (PORTD, i);
  }
}

void zad1_5_1() {
  if (bit_is_clear(PINB, 0)) {
    //zapalenie wszystkich diod
    for (uint8_t i = 0; i < 8; i++) {
      sbi (PORTD, i);
    }
  }
  else {
    for (uint8_t i = 0; i < 8; i++) {
      cbi (PORTD, i);
    }
  }
}

void zad1_5_2() { // nie działa
  bool isLight = true;
  while (1) {
    if (bit_is_clear(PINB, 1) && isLight == false) {
      //zapalenie wszystkich diod
      isLight = true;
      for (uint8_t i = 0; i < 8; i++) {
        sbi (PORTD, i);
      }
    }
    break;
  }
  while (1) {
    if (bit_is_set(PINB, 1)) break;
  }
  while (1) {
    if (bit_is_clear(PINB, 1) && isLight == true ) {
      isLight = false;
      for (uint8_t i = 0; i < 8; i++) {
        cbi (PORTD, i);
      }
    } break;
  }
  while (1) {
    if (bit_is_set(PINB, 1)) break;
  }
}

void zad5_2(){
        if (bit_is_clear(PINB, 1) && isLight == false) {
        _delay_ms(200);
        //zapalenie wszystkich diod
        isLight = true;
        diodesOn();
      } 

      if (bit_is_clear(PINB, 1) && isLight == true ) {
        _delay_ms(200);
        isLight = false;
        diodesOff();
      }
}
int main() {
  DDRD = 0xff;
  DDRB = 0;
  _delay_ms(500);
  bool isLight = false;
  diodesOff();
  PORTB = 2; 
  while (1) {
  
 

  }
}
