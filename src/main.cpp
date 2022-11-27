#include "function.h"

// defines variables
float duration; // variable for the duration of sound wave travel
float distance1 = 0; // variable for the distance measurement
unsigned long previousTime = 0;
unsigned long interval = 500;

void setup() {
  Wire.begin();
  lcdInit();
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(relay, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  delay(2000);
}

void loop() {
  // multitasking with millis
  unsigned long currentTime = millis();
  if (currentTime - previousTime >= interval) {
    previousTime = currentTime;
    usSig();
    duration = pulseIn(echoPin,HIGH);

    distance1 = 19.44 - (0.0178*duration - 0.7605);
    lcdPrint(distance1);
    Serial.print("Distance: ");
    Serial.println(distance1);
  }
   if (distance1 < 10) {
      digitalWrite(LED, HIGH);
      digitalWrite(relay, HIGH);
     } else {
      digitalWrite(LED, LOW);
      digitalWrite(relay, LOW);
    }
}