#include "function.h"
#include <Arduino.h>
#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

void usSig(){
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
}

void lcdInit(LiquidCrystal_I2C lcd)
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Pertaminum");
  lcd.setCursor(1,1);
  lcd.print("LTF 3");
}

void lcdPrint(int distance, LiquidCrystal_I2C lcd)
{
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Input: ");
  lcd.setCursor(7,0);
  lcd.print(distance);
  lcd.print(" mL");
}

int priceCalc(int distance)
{
  // linear regression of the prices y = 9.0597x - 1166.6
  return (9.0597 * distance) - 1166.6;
}