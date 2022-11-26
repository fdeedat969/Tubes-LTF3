#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define echoPin 26 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 25 //attach pin D3 Arduino to pin Trig of HC-SR04

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
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Pertamina tapi di minum");
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

