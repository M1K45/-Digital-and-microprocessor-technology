#include <splash.h>
#include <FastLED.h>
#include <Wire.h>
#include <Adafruit_SH110X.h>

#define NUM_LEDS 24
#define DATA_PIN 3
CRGB leds[NUM_LEDS];

void zad_1(){
    for(uint8_t i=0;i<24;i++) {
   leds[i] = CRGB::Green; FastLED.show(); delay(100);
   FastLED.clear(); delay(100);
  }  

  for(uint8_t i=0;i<24;i++) {
   leds[i] = CRGB::Red; FastLED.show(); delay(100);
   FastLED.clear(); delay(100);
  } 

    for(uint8_t i=0;i<24;i++) {
   leds[i] = CRGB::Blue; FastLED.show(); delay(100);
   FastLED.clear(); delay(100);
  } 
}

void zad_2(){
    for (uint8_t i=0; i<24; i++){
    if (i%4 <= 1){
      tone(PD4, 1000);
      leds[i] = CRGB::OrangeRed; FastLED.show(); delay(100);
      noTone(PD4);
    } else if (i%4 == 2){
      tone(PD4, 1500);
      leds[i] = CRGB::Green; FastLED.show(); delay(100);
      noTone(PD4);

    } else {
      leds[i] = CRGB::Black; FastLED.show(); delay(100);
    }
  }
  for (uint8_t i=0; i<24; i++){
     tone(PD4, 500);
      leds[i] = CRGB::Blue; FastLED.show(); delay(100);
      leds[23-i] = CRGB::Blue; FastLED.show(); delay(100);
      noTone(PD4);

  }
  FastLED.clear();
}

#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define NUMFLAKES 5
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

const unsigned char egg [] PROGMEM = {
0x00, 0x00, 0xF0, 0xF8, 0xFE, 0xFE, 0xFE, 0xFC, 0xF0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x01, 
};


void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
 Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(i2c_Address, true); // Address 0x3C default
  // init done


  // Clear the buffer.
  display.clearDisplay();


  
  display.clearDisplay();
  testdrawbitmap(egg, LOGO16_GLCD_HEIGHT, LOGO16_GLCD_WIDTH);

}
void loop() {
  zad_2();

}
void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icons[NUMFLAKES][3];

  // initialize
  for (uint8_t f = 0; f < NUMFLAKES; f++) {
    icons[f][XPOS] = random(display.width());
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random(5) + 1;

    Serial.print("x: ");
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(" y: ");
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(" dy: ");
    Serial.println(icons[f][DELTAY], DEC);
  }

  while (1) {
    zad_2();
    // draw each icon
    for (uint8_t f = 0; f < NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SH110X_WHITE);
    }
    display.display();
    delay(200);

    // then erase it + move it
    for (uint8_t f = 0; f < NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SH110X_BLACK);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > display.height()) {
        icons[f][XPOS] = random(display.width());
        icons[f][YPOS] = 0;
        icons[f][DELTAY] = random(5) + 1;
      }
    }
  }
}
