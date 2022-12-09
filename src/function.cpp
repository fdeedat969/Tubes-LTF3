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