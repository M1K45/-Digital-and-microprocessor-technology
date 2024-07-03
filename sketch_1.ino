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

int main() {
  DDRD=0xff;
  _delay_ms(500);  

  while (1) {
    for (uint8_t i=0; i<8; i++){
      sbi (PORTD, i);
      _delay_ms(100);  
      cbi (PORTD, i);
      _delay_ms(100);  
    }
    for (uint8_t j=6; j>0; j--){
      sbi (PORTD, j);
      _delay_ms(100);  
      cbi (PORTD, j);
      _delay_ms(100);  
    }
  } 
}
