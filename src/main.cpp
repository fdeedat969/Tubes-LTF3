#include "function.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h>

#define ROW_NUM     4 // four rows
#define COLUMN_NUM  3 // three columns

// define the symbols on the buttons of the keypads
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte pin_rows[ROW_NUM] = {16, 17, 18, 19}; 
byte pin_column[COLUMN_NUM] = {14, 27, 26};  

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

// defines variables
int duration; // variable for the duration of sound wave travel
float height = 0; // variable for the distance measurement
unsigned long previousTime = 0;
unsigned long interval1 = 500;
unsigned long interval2 = 1000;
volatile byte pulseCount;
byte pulse1sec = 0;
float flowRate;

char dataKey[5];
int dataKeyInt;
int i = 0;

// this two function should be moved to function.cpp but idk how to someone pls fix
void clearData(){
  while (i != 0){
    dataKey[i--] = 0;
  }
}

void backSpace(){
  if (i != 0){
    dataKey[i--] = 0;
  }
}

void IRAM_ATTR pulseCounter()
{
  pulseCount++;
}

void setup() {
  Wire.begin();
  lcdInit();
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(LED, OUTPUT);
  pinMode(flowSens,INPUT_PULLUP);
  Serial.begin(9600); // Serial Communication is starting with 9600 of baudrate speed
  attachInterrupt(digitalPinToInterrupt(flowSens), pulseCounter, FALLING);
}

void loop() {
  // multitasking with millis
  // Ultrasonic Reading 
  unsigned long currentTime = millis();
  if (currentTime - previousTime >= interval1) { 
    previousTime = currentTime;
    usSig();
    duration = pulseIn(echoPin,HIGH);

    height = 19.44 - (0.0178*duration - 0.7605);
    lcdPrint(height);
    //Serial.print("Distance: ");
    //Serial.println(height);
   }

  // Flowsensor Reading
  if (currentTime - previousTime >= interval2) { 
    previousTime = currentTime;
    pulse1sec = pulseCount;
    pulseCount = 0;
    flowRate = ((float)pulse1sec);

    Serial.print("Flow rate: ");
    Serial.print(int(flowRate));
  }

  char keypressed = keypad.getKey();
  if (keypressed){
    if (keypressed == '*'){
      backSpace();
    } else if(keypressed == '#'){
      dataKeyInt = atoi(dataKey);
      if (height >= dataKeyInt){
        digitalWrite(LED, HIGH);
      } else {
        digitalWrite(LED, LOW);
      }
      clearData();
    }
    else{
      dataKey[i] = keypressed;
      dataKeyInt = atoi(dataKey);
      Serial.println(keypressed);
      Serial.println(dataKey);
      i++; 
    }
  }
}