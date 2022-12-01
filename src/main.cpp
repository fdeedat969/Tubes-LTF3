#include "function.h"

#define ROW_NUM     4 // four rows
#define COLUMN_NUM  3 // three columns

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
unsigned long interval2 = 50;

int i = 0;
char dataKey[5];
int dataKeyInt;

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
  char keypressed = keypad.getKey();
  if (keypressed){
    if (keypressed == '*'){
      backSpace();
    } else if(keypressed == '#'){
      dataKeyInt = atoi(dataKey);
      if (height >= dataKeyInt){
        digitalWrite(relay, HIGH);
        digitalWrite(LED, HIGH);
      } else {
        digitalWrite(relay, LOW);
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