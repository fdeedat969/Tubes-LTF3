#include "function.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

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
int intervalFlow = 125;
int intervalUs = 500;
float calibrationFactor = 7.5;
byte pulse1Sec = 0;
float flowRate;
float flowMilliLitres;
float totalMilliLitres = 0;
float totTotMil = 0;

char dataKey[5];
int dataKeyInt;
int i = 0;

volatile byte pulseCount;

// All these function should be moved to function.cpp but idk how to someone pls fix
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

void IRAM_ATTR pulseCounter() // Interrupt Service Routine
{
  pulseCount++;
}

void lcdInit()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Pertaminum");
  lcd.setCursor(1,1);
  lcd.print("LTF 3");
}

void lcdPrint(int distance)
{
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Input: ");
  lcd.setCursor(7,0);
  lcd.print(distance);
  lcd.print(" mL");
}

int priceCalc(int distance)
{
  // linear regression of the prices y = 9.0597x - 1166.6
  return (9.0597 * distance) - 1166.6;
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
  delay(3000);
  lcd.clear();
  lcdPrint(dataKeyInt);
}

void loop() {
  // multitasking with millis
  currentMillis = millis();
  // Keypad Reading
  char keypressed = keypad.getKey();
  if (keypressed){
    if (keypressed == '*'){
      clearData();
      lcd.clear();
      lcd.print("Input: ");
      lcd.setCursor(7,0);
      lcd.print("0");
      lcd.print(" mL");
    } else if(keypressed == '#'){
      dataKeyInt = atoi(dataKey);
      int limit = dataKeyInt/100;
      clearData();
      for (int i = 0; i <limit ; i++){
        digitalWrite(LED, HIGH);
        digitalWrite(relay, HIGH);      
        delay(1000);
        int loopingFactor = 100;
        while(totalMilliLitres <= (loopingFactor)){
          // FLow Sensor Reading
          currentMillis = 0;
          currentMillis = millis();
          if (currentMillis - previousMillis >= intervalFlow) {  // Refreshes every 125ms
            detachInterrupt(flowSens);

            flowRate = ((1000.0 / (currentMillis - previousMillis)) * pulseCount) / calibrationFactor;
            previousMillis = currentMillis;

            flowMilliLitres = ((flowRate / 60) * 1000);
            flowMilliLitres = flowMilliLitres / 8;
            
            if (flowMilliLitres > 4.16){ // this is retarded but it works so fight me
              flowMilliLitres = 5.2;
            }
            totalMilliLitres += flowMilliLitres;

            Serial.println(flowMilliLitres);
            lcd.setCursor(7,1);
            lcd.print("FS: ");
            lcd.setCursor(10,1);
            lcd.print("     ");
            lcd.printf("%d", totTotMil);
            lcd.print("mL");
            
            pulseCount = 0;
            attachInterrupt(digitalPinToInterrupt(flowSens), pulseCounter, FALLING);
          }
        }
        digitalWrite(LED, LOW);
        digitalWrite(relay, LOW);        
        totTotMil += totalMilliLitres;
        totalMilliLitres = 0 ;
        delay(1000);
      }
      digitalWrite(LED, LOW);
      digitalWrite(relay, LOW);

      lcd.clear();
      lcd.backlight();
      lcd.setCursor(0,0);
      lcd.print("Bayar !!");
      lcd.setCursor(0,1);
      lcd.print("Harga: Rp. ");
      lcd.print(priceCalc(totTotMil));
      delay(5000);
      lcd.clear();

      lcd.clear(); 
      lcd.print("Input: ");
      lcd.setCursor(7,0);
      lcd.print("0");
      lcd.print(" mL");

      dataKeyInt = 0;
      totalMilliLitres = 0;
      totTotMil = 0;
    }
    else{
      dataKey[i] = keypressed;
      dataKeyInt = atoi(dataKey);
      lcdPrint(dataKeyInt);
      Serial.println(keypressed);
      Serial.println(dataKey);+
      i++; 
    }
  }   
  // Ultrasonic Reading 
  if (currentMillis- previousMillis > intervalUs) { 
    previousMillis = currentMillis;
    usSig();
    int duration = pulseIn(echoPin,HIGH);

    //y = -0.0071x + 13.114
    float volume = -0.0071*(duration) + 13.114 - 0.2;
    if (volume < 0){
      volume = 0;
    }
    lcd.setCursor(0,1);
    lcd.print("US: ");
    lcd.setCursor(3,1);
    lcd.print("     ");
    lcd.setCursor(3,1);
    lcd.printf("%.1f", volume);
    lcd.print("L");

    lcd.setCursor(9,1);
    lcd.print("FS: ");
    lcd.setCursor(12,1);
    lcd.print("     ");
    lcd.setCursor(12,1);
    lcd.printf("%d", totalMilliLitres);
    lcd.print("mL");
   }
}
