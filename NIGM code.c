#include <LiquidCrystal.h>

#include "Wire.h"
#include "LiquidCrystal.h"

// those are default pins for LCD, you can change them but most examples and codes on the internet use those.
LiquidCrystal lcd(7, 6, 5, 4, 1, 0);


const int sensorPin = A0; 
int sensorValue = 0;  
//int limit = 300; 

const int buttonPin = 10;     // the number of the pushbutton pin
const int ledPin =  13;   // the number of the LED pin
double array[10];

void setup() {

  // if you have 16x2 LCD just change 20 to 16 and 4 to 2
  lcd.begin(16, 2);
  // initialize the LED pin as an output:
   
    pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);


  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}
void loop() {
    // variables will change:
    int buttonState = 0;         // variable for reading the pushbutton status
    // read the state of the pushbutton value:
    
    buttonState = digitalRead(buttonPin);
Serial.println (" ");
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
     
     if (buttonState == HIGH) {
   for (int i = 0; i<10; i++){
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    
     // read the input on analog pin 0:
  int sensorValue = analogRead(sensorPin);
   
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
 double voltage = sensorValue * (5.0 / 1023.0);
 double milliVolt = voltage * 1000;
    array[i] = milliVolt;
  // print out the value you read:
 
  Serial.println(array[i]);
    delay(990);
   }
   double average = 0;

for (int i = 0; i<10; i++){
  
  average = array[i] +average ;
  
  
  }
average = average /10; 
 Serial.println(" ");
Serial.println(average);

   
     }else {
    
    // turn LED off:
    digitalWrite(ledPin, LOW);
    
  }
 lcd.clear();
//with setCursor we can move "cursor" to the position that we want
//the first number is character number in my case from 0 to 19
//second number is line in my case from 0 to 3
//after set cursor we can call print and text will be printed in place that we want
  lcd.setCursor(0, 0);
  lcd.print("Welcome to NIGM!");
  delay(2000);
  lcd.setCursor(0, 0);
  lcd.print("To Start Measure");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("Press the Button");
  delay(3000);
//with clear we can delate everything from LCD
lcd.clear();


//Insert button recognition code
 lcd.setCursor(0, 0);
  lcd.print("Measuring...");
  delay(5000);
  lcd.setCursor(0, 1);
  lcd.print("Please wait..");
  delay(5000);
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("Glucose Level:");
  lcd.setCursor(5, 5);
  lcd.print("X mg/dl");
 
  delay(3000);

  
}