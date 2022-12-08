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
long currentMillis = 0;
long previousMillis = 0;
int interval = 1000;
int interval1 = 250;
boolean ledState = LOW;
float calibrationFactor = 4.5;
volatile byte pulseCount;
byte pulse1Sec = 0;
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres = 0;

char dataKey[5];
int dataKeyInt;
int i = 0;

// this three function should be moved to function.cpp but idk how to someone pls fix
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
  pinMode(relay, OUTPUT);
  pinMode(flowSens,INPUT_PULLUP);

  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  previousMillis = 0;
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(flowSens), pulseCounter, FALLING);
}

void loop() {
  // multitasking with millis
  currentMillis = millis();
  // Keypad Reading
  char keypressed = keypad.getKey();
  if (keypressed){
    if (keypressed == '*'){
      backSpace();
    } else if(keypressed == '#'){
      dataKeyInt = atoi(dataKey);
      Serial.print("Input: ");
      Serial.println(dataKeyInt);
      clearData();
      while(totalMilliLitres < dataKeyInt){
        digitalWrite(LED, HIGH);
        delay(2000);
        if (currentMillis - previousMillis > interval) {
          
          pulse1Sec = pulseCount;
          pulseCount = 0;

          flowRate = ((1000.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
          previousMillis = millis();

          flowMilliLitres = (flowRate / 60) * 1000;
        }
      }
      digitalWrite(LED, LOW);
      totalMilliLitres = 0;
    }
    else{
      dataKey[i] = keypressed;
      dataKeyInt = atoi(dataKey);
      Serial.println(keypressed);
      Serial.println(dataKey);
      i++; 
    }
  }   
  // // Ultrasonic Reading 
  // currentMillis = millis();
  // if (currentMillis- previousMillis > interval1) { 
  //   previousMillis= currentMillis;
  //   usSig();
  //   int duration = pulseIn(echoPin,HIGH);

  //   float volume= -6.8804*(duration) + 12943;
  //   lcdPrint(volume);
  //   Serial.print("Volume: ");
  //   Serial.print(volume);
  //   Serial.println(" ml");
  //  }

  // // Flowsensor Reading
  // if (currentMillis - previousMillis > interval) {
    
  //   pulse1Sec = pulseCount;
  //   pulseCount = 0;

  //   flowRate = ((1000.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
  //   previousMillis = millis();

  //   flowMilliLitres = (flowRate / 60) * 1000;


    // Serial.print("Flow rate: ");
    // Serial.print(flowMilliLitres);  // Print the integer part of the variable
    // Serial.print("mL/s");
    // Serial.print("\t");       // Print tab space
}
