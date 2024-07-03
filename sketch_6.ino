
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 14

#define LED_R 11
#define LED_G 10
#define LED_B 9

#define WAIT 1000

LiquidCrystal_I2C lcd(0x27, 16, 2);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void ostatnieZadanie() {

  float V = analogRead(A0);

  float temp = V * 0.1;

  lcd.print(temp);
  if (temp < 50) {
    analogWrite(LED_R, 0);
    analogWrite(LED_G, 0);
    analogWrite(LED_B, 0);
    delay(WAIT);
    lcd.setCursor(0, 1);
    lcd.print("zimna");
  }
  else if  (temp >= 50 && temp < 70) {
    // zmien kolor na zielony
    analogWrite(LED_R, 255);
    analogWrite(LED_G, 0);
    analogWrite(LED_B, 255);
    delay(WAIT);
    lcd.setCursor(0, 1);
    lcd.print("letnia");
  }
  else if (temp >= 70 && temp < 80) {
    // zmien na niebieski
    analogWrite(LED_R, 255);
    analogWrite(LED_G, 255);
    analogWrite(LED_B, 0);
    delay(WAIT);
    lcd.setCursor(0, 1);
    lcd.print("ciepla");
  }
  else if (temp >= 80 && temp < 90) {
    // fioletowy
    analogWrite(LED_R, 0);
    analogWrite(LED_G, 255);
    analogWrite(LED_B, 0);
    delay(WAIT);
    delay(WAIT);
    lcd.setCursor(0, 1);
    lcd.print("goraca");
  }
  else if (temp >= 90 && temp < 100) {
    // zolty
    analogWrite(LED_R, 0);
    analogWrite(LED_G, 150);
    analogWrite(LED_B, 255);
    delay(WAIT);
    delay(WAIT);
    lcd.setCursor(0, 1);
    lcd.print("bardzo goraca");
  }
  else if  (temp >= 100) {
    //  czerwony
    analogWrite(LED_R, 0);
    analogWrite(LED_G, 255);
    analogWrite(LED_B, 255);
    delay(WAIT);
    lcd.setCursor(0, 1);
    lcd.print("gotowe!");
  }


}


void setup() {
  lcd.init();
  lcd.backlight();

  sensors.begin();

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

}

void loop() {

  delay(1000);
  lcd.clear();
  ostatnieZadanie();


}
