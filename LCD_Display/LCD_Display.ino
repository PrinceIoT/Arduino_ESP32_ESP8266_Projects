#include <LiquidCrystal.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//LCD Address to 0x27 for 16chars by 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  // put your setup code here, to run once:
  lcd.init();
  //Serail.begin(9600);

  // set the backlight
  lcd.backlight();

}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.print("Dishan Otieno");
  lcd.setCursor(0,1);
  lcd.print("Hello World");
  //delay(1000);

}
