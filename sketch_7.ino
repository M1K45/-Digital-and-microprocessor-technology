#include <IRremote.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define IR_RECEIVE_PIN 8
#define CMD IrReceiver.decodedIRData.command

bool powerON;
void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
  powerON= false;
          lcd.init();
           lcd.noDisplay();
}

void loop() {

  if (IrReceiver.decode()) {
    
    IrReceiver.resume();
    if (!powerON && CMD == 69){
    powerON = true;
    Serial.println("on");
    lcd.display();
     lcd.clear();
    }
    else if (powerON && CMD == 69){
          powerON = false;
      lcd.clear();
      lcd.noDisplay();
          Serial.println("off");
    }    
  }  
}
