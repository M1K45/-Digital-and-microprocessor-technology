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

// przerwanie wewnetrzne
void timerInit() {
  //Wybranie trybu pracy CTC z TOP OCR1A
  cbi (TCCR1A, WGM10);
  cbi (TCCR1A, WGM11);
  sbi (TCCR1B, WGM12);
  cbi (TCCR1B, WGM13);


  //Wybranie dzielnika czestotliwosci - częstotliwość Atmega328: 16 MHz
  //  (16 MHz / 256 = 62500 Hz)
  cbi (TCCR1B, CS10);
  cbi (TCCR1B, CS11);
  sbi (TCCR1B, CS12);

  // 5 ms to 0,005 s - 1/200 s
  //Zapisanie do OCR1A wartosci odpowiadajacej 0,005s (62500 / 200 ~ 312)

  OCR1A = 312;

  //Uruchomienie przerwania OCIE1A
  sbi (TIMSK1, OCIE1A);
}


//volatile -informacja dla kompilatora aby nie optymalizował zmiennej,
//zmienna bezpieczna do wykorzystania w przerwaniach
volatile int zmienna = 0;

uint8_t number[10] = {
  0b0111111,
  0b0000110,
  0b1011011,
  0b1001111,
  0b1100110,
  0b1101101,
  0b1111101,
  0b0000111,
  0b1111111,
  0b1101111,
};

char liczba[4] = {"00"};


int main() {
  DDRC = 0xff;

  DDRD = 0xff;
  DDRB = 0xff;
  _delay_ms(500);
  timerInit();
  sei(); //Uruchamia przerwania globalne
  //
  //  sbi(DDRD,PD0);
  //  sbi(DDRD,PD1);
  //
  //  // pin do przelaczanej diody
  //  sbi(DDRD,PD5);
  //
  //  //piny do obsługi przysicków
  //  cbi(DDRD,PD2);
  //  sbi(PORTD, PD2);
  //
  //  // konfiguracja reakcji na zbocze opadające
  //  cbi(EICRA,ISC00);
  //  sbi(EICRA,ISC01);

  //  sbi(EIMSK,INT0);
  while (1) {
    //kod programu przełączajacy diodę LED na pinie PD0
    //    tbi(PORTD, PD0);

    //    _delay_ms(5000);

  } // dioda ma migać pd0 1 hz
}
uint8_t licznik = 1;
ISR(TIMER1_COMPA_vect) {
  //
  //  tbi(PORTD, PD1);
  // kod programu przełączajacy diodę LED na pinie PD1
  switch (licznik) {


    case 1:
      {
        if (liczba[1] != 0)
        {
        cbi (PORTC, 0);
        sbi (PORTC, 1);
        PORTD = number[liczba[1] - '0'];
        licznik ++;
        }
        break;
      }

    case 2:
      {
        if (liczba[2] != 0)
        {
        cbi (PORTC, 1);
        sbi (PORTC, 2);
        PORTD = number[liczba[2] - '0'];
        licznik ++;
        }
        break;
      }

    case 3:
      {
        cbi (PORTC, 2);
        sbi (PORTC, 3);
        PORTD = number[liczba[3] - '0'];
        licznik ++;
        break;
      }

    case 4:
      {
        cbi (PORTC, 3);
        licznik = 1;
        break;
      }
  }
}
//      sbi (PORTC, 0);
//    PORTD = number[liczba[0] - '0'];
//    _delay_ms(5);
//    cbi (PORTC, 0);
//
//    sbi (PORTC, 1);
//    PORTD = number[liczba[1] - '0'];
//    _delay_ms(5);
//    cbi (PORTC, 1);
//
//    sbi (PORTC, 2);
//    PORTD = number[liczba[2] - '0'];
//    _delay_ms(5);
//    cbi (PORTC, 2);
//
//    sbi (PORTC, 3);
//    PORTD = number[liczba[3] - '0'];
//    _delay_ms(5);
//    cbi (PORTC, 3);


//ISR(INT0_vect){
//    sbi (PORTC, 0);
//    PORTD = number[liczba[0] - '0'];
//    _delay_ms(5);
//    cbi (PORTC, 0);
//}
