#include "function.h"

// defines variables
float duration; // variable for the duration of sound wave travel
float distance1; // variable for the distance measurement

void setup() {
  Wire.begin();
  lcdInit();
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  delay(2000);
}

void loop() {
  usSig();
  duration = pulseIn(echoPin,HIGH);
  delay(500);

  distance1 = 0.0178*duration - 0.7605;
  // distance2 = 340*duration/(2*10000);

  distance1 = 19.44-distance1;

  Serial.println(distance1); 
  lcdPrint(distance1);
}