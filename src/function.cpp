#include "function.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void usSig(){
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
}

void lcdInit()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Pertaminum");
  lcd.setCursor(1,1);
  lcd.print("LTF 3");
}

void lcdPrint(int distance)
{
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Tinggi Air: ");
  lcd.setCursor(0,1);
  lcd.print(distance);
  lcd.print(" cm");
}