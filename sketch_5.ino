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

#ifndef tbi
#define tbi(reg,bit)    reg ^= (_BV(bit))
#endif

void USART_Transmit (unsigned char data) {
  while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = data;
}

void send_text(String text) {
  for (uint8_t i = 0; i < text.length() ; i++) {
    USART_Transmit(text[i]);
  }
}

void send_char(char ch) {
  USART_Transmit(ch);
}

unsigned char USART_receive(void) {

  while (!(UCSR0A & (1 << RXC0)));
  return UDR0;

}

//char USART_Recieve(){
//  while (!(UCSR0A & (1<<UDRE0)));
//  char data = UDR0;
//  return data;
//}
//
//String get_data(){
//  USART_Recieve();
//}

int main() {
    sbi(DDRD, PD2);
//    PORTD =0;
    cbi (PORTD, PD2);
  DDRB = 0;
  PORTB = 1;
  UBRR0 = 51;
  UCSR0B = 0b00011000;
  //  String hello = "Hello world";
    int counter = 1;
  char foo;

  while (1) {
    //    send_text(hello);
    //    send_text(String(number));
    //    USART_Transmit(10);
    //    _delay_ms(1000);
    //    number++;
    foo = USART_receive();
//    send_char(foo);
    USART_Transmit(10);
    String mess;

    switch (foo) {
      case 'a': 
          sbi (PORTD, PD2);
          mess = "LED1 ON";
          send_text(mess);
          break;
        
      case 'b': 
          cbi (PORTD, PD2);
          mess = "LED1 OFF";
          send_text(mess);
          break;
        

      case 'c': 
          if (bit_is_clear(PINB, PB0)) {
            mess = "przycisk  wcisniety";
            send_text(mess);
          }
          else {
            mess = "przycisk nie wcisniety";
            send_text(mess);
          }
          break;

      case 'd': 
          send_char(char(counter));
          break;

        


      default: 
          mess = "zla liczba";
          send_text (mess);
          break;

        
    }

  }

  return 0;
}
