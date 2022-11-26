#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define echoPin 26 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 25 //attach pin D3 Arduino to pin Trig of HC-SR04

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

// defines variables
float duration; // variable for the duration of sound wave travel
float distance1; // variable for the distance measurement
float distance2;

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
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("hello everyone");
  lcd.setCursor(1,1);
  lcd.print("konichiwaa");
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


void setup() {
  Wire.begin();
  lcdInit();
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  delay(500);
}

void loop() {
  usSig();
  duration = pulseIn(echoPin,HIGH);
  delay(500);

  distance1 = 0.0178*duration - 0.7605;
  distance2 = 340*duration/(2*10000);

  distance1 = 19.44-distance1;

  Serial.println(distance1); 
  lcdPrint(distance1);
}