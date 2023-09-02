#include <Wire.h>  //including I2C library

#define led 3   // set pin 3 to led

//declaring variables
bool state_1 = 0;
bool state_2 = 0;
int brightness = 0;
String message = "";

void setup() {
  //I2C communication protocol
  Wire.begin(10);             // the slave address
  pinMode(led, OUTPUT);      // setting pin connected to led to output
  Serial.begin(9600);        //to communicate with the serial monitor
  Wire.onReceive(receiveData); // Set to call the function when recieving data
}

void loop() {
  // no need for a function to be on loop 
}

void receiveData(int bytes) {
  if (bytes >= 2)     //size of integer 
  {
    state_1 = Wire.read();      //reading data recieved from master
    state_2 = Wire.read();
    
    if (state_1 == LOW && state_2 == LOW)
    {
      brightness = 0;
      message = "No message";
    } 
    else if (state_1 == HIGH && state_2 == LOW) 
    {
      brightness = 128; // 50% of maximum (255) using pwm
      message = "Vector focused";
    } 
    else if (state_1 == LOW && state_2 == HIGH)
    {
      brightness = 191; // 75% of maximum (255)
      message = "Vector distracted";
    }
     else if (state_1 == HIGH && state_2 == HIGH)
    {
      brightness = 255; // 100% of maximum (255)
      message = "Glitch";
    }
    
    analogWrite(led, brightness); // stting the brightness of led based on the data recieved 
    Serial.println(message); // Print message to Serial Monitor 
  }
}
