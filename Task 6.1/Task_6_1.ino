// including the wire library for i2c communication
#include <Wire.h>

# define Samples  1000 
# define MPU_ADDRESS  0x68
# define PWR_MGMT_1   0x6B
# define GYRO_CONFIG  0x1B
# define GYRO_ZOUT_H  0x47

// intializing variables
int16_t  gyro_Offset_z=0 ;      
int16_t gyro_z = 0; 
unsigned long  previous_time=0 , current_time=0 ;
float dt = 0 ;                         
float yaw_angle = 0;
float gyro_z_final = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();                                       // Initialize comunication
  Wire.beginTransmission(MPU_ADDRESS);               // start communication with MPU6050 which address is 0x68
  Wire.write(PWR_MGMT_1);                           // connecting to the register 6B
  Wire.write(0x00);                                //  Make reset - place a 0 into the 6B register
  Wire.endTransmission();                         // end the transmission
  
// start the Gyroscope Configuration
Wire.beginTransmission(MPU_ADDRESS);               // start communication with MPU6050
Wire.write(GYRO_CONFIG);                          // connect the gyro_config register which address is 0x1B
Wire.write(0x00);                                // set the full-scale range to = +- 250 ^/s
Wire.endTransmission();                         // end the transmission

MPU_Calibration();
delay(20);
}

void loop() {
  // reading Gyro data 
 previous_time = current_time ;                        // Previous time is stored before the actual time read 
 current_time  = millis();                            // Current time actual time read
 dt = (current_time - previous_time ) / 1000 ;       // dt is the time diffrenece between two steps and we divide by 1000 to git the time in seconds

 Wire.beginTransmission(MPU_ADDRESS);               // start communication with MPU6050
 Wire.write(GYRO_ZOUT_H);                          // start with the register GYRO_ZOUT_H which address is 0x47                              
 Wire.endTransmission();                          // end the transmission

 Wire.requestFrom(MPU_ADDRESS,2);               // request data with size of 2 bytes from MPU
 while (Wire.available() < 2);                 // read the data from the sensor and store it in 2 bytes = 16 bits
 gyro_z = Wire.read() <<8 | Wire.read() ;     // wait untill the data is 2 bytes


 gyro_z_final = (gyro_z - gyro_Offset_z ) / 131 ;           // the sensitivity of the gyroscope for full-scale range of +- 250 ^/s is 131 according to datasheet
 yaw_angle = yaw_angle + ( gyro_z_final * dt);             // according to the rule  yaw_angle = yaw_angle + ( yaw_rate * time difference between two steps) 
 Serial.println(yaw_angle);                               // printing the yaw angle to the serial monitor
}

void MPU_Calibration() {
  int16_t gyro_z =0 ;
  for (int i=0; i<Samples; i++)
  {
    Wire.beginTransmission(MPU_ADDRESS);               // start communication with MPU6050
    Wire.write(GYRO_ZOUT_H);                          // start with the register GYRO_ZOUT_H which address is 0x47                           
    Wire.endTransmission();                          // end the transmission
    Wire.requestFrom(MPU_ADDRESS,2);                // request data with size of 2 bytes from MPU

    while (Wire.available() < 2);                 // wait untill the data is 2 bytes

    gyro_z = Wire.read() <<8 | Wire.read() ;    // read the data from the sensor and store it in 2 bytes = 16 bits
    gyro_Offset_z += gyro_z ;                  // Accumulate data for calibration
  }
  gyro_Offset_z /= Samples ;                 // calculating the average offset value to subtract from the data to limit error
}
