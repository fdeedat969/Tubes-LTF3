#include "function.h"
#include <Keypad.h>

#define ROW_NUM     4 // four rows
#define COLUMN_NUM  3 // three columns

char dataKey[4];
int dataKeyInt;
int i = 0;

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'},
};

byte pin_rows[ROW_NUM] = {19, 18, 5, 17}; // GIOP18, GIOP5, GIOP17, GIOP16 connect to the row pins
byte pin_column[COLUMN_NUM] = {16, 4, 2};  // GIOP4, GIOP0, GIOP2 connect to the column pins

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

// defines variables
int duration; // variable for the duration of sound wave travel
float distance1 = 0; // variable for the distance measurement
unsigned long previousTime = 0;
unsigned long interval1 = 500;
unsigned long interval2 = 50;

void setup() {
  Wire.begin();
  lcdInit();
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(relay, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600); // Serial Communication is starting with 9600 of baudrate speed
  //delay(3000);
}

void loop() {
  // multitasking with millis
  // unsigned long currentTime = millis();
  // if (currentTime - previousTime >= interval1) { 
  //   previousTime = currentTime;
  //   usSig();
  //   duration = pulseIn(echoPin,HIGH);

  //   distance1 = 19.44 - (0.0178*duration - 0.7605);
  //   lcdPrint(distance1);
  //   //Serial.print("Distance: ");
  //   //Serial.println(distance1);
  // }
  char keypressed = keypad.getKey();
  if (keypressed){
    //dataKey[i] = keypressed;
    Serial.println(keypressed);
    // Serial.println(dataKey);
    // i++;
  }
}