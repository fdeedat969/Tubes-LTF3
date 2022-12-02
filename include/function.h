#ifndef FUNCTION_H
#define FUNCTION_H

#include <Arduino.h>

#define echoPin 26 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 25 //attach pin D3 Arduino to pin Trig of HC-SR0
#define LED 3
#define flowSens 27

void usSig();
void lcdInit();
void lcdPrint(int distance);
void clearData();
void backSpace();

#endif