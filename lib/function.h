#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define echoPin 26 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 25 //attach pin D3 Arduino to pin Trig of HC-SR0
#define relay 27
#define LED 3
#define rly 4

void usSig();
void lcdInit();
void lcdPrint(int distance);