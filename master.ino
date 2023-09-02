#include <Wire.h>   //the I2C library

#define button_1 5     // pin 5 connected to button 1
#define button_2 7    // pin 7 connected to button 2

void setup() {
  //I2C communication protocol 
  Wire.begin();     
  pinMode(button_1, INPUT);  //set pin connected to button 1 to input
  pinMode(button_2, INPUT); //set pin connected to button 2 to input 
}

void loop() {
  bool state_1 = digitalRead(button_1);    //read digital value to know the state of button 1 HIGH/LOW
  bool state_2 = digitalRead(button_2);   //read digital value to know the state of button 2 HIGH/LOW
  
  Wire.beginTransmission(10);   // Address of the slave that will recieve the data
  Wire.write(state_1);       
  Wire.write(state_2);
  Wire.endTransmission();   //end the transmission 
}
