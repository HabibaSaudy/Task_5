# Task 6.1

For this task it is required to Interface with the sensor MPU6050, and retrieve the Yaw angle which angle along the z-axis using an Arduino code .

Here is the code and its explanation:

## Libraries :

include the <wire.h> library for communication with i2c

```arduino
#include <Wire.h>
```

## Define constants :

We define the constants of the sensor using the sensor data sheet so that we don’t have to write them every time in the code we can just use the name they are defined by

```arduino
# define Samples  1000 
# define MPU_ADDRESS  0x68
# define PWR_MGMT_1   0x6B
# define GYRO_CONFIG  0x1B
# define GYRO_ZOUT_H  0x47
```

## Variables :

```arduino
// intializing variables
int16_t  gyro_Offset_z=0 ;
int16_t gyro_z = 0; 
unsigned long  previous_time=0 , current_time=0 ;
float dt = 0 ;           
float yaw_angle = 0;
float gyro_z_final = 0;
```

## Setup :

- initializing the serial monitor
- Use the wire library to start i2c communication with the sensor ,in which we choose which register to talk to and what to write in that register

```arduino
void setup() {
  Serial.begin(9600);
  Wire.begin();                                       // Initialize comunication
  Wire.beginTransmission(MPU_ADDRESS);               // start communication with MPU6050 which address is 0x68
  Wire.write(PWR_MGMT_1);                           // connecting to the register 6B
  Wire.write(0x00);                                //  Make reset - place a 0 into the 6B register
  Wire.endTransmission();                         // end the transmission
```

- Start the gyroscope configuration and start the transmission using wire.h library , then choose the register and write in it to choose our full-scale range then end the transmission

```arduino
// start the Gyroscope Configuration
Wire.beginTransmission(MPU_ADDRESS);               // start communication with MPU6050
Wire.write(GYRO_CONFIG);                          // connect the gyro_config register which address is 0x1B
Wire.write(0x00);                                // set the full-scale range to = +- 250 ^/s
Wire.endTransmission();                         // end the transmission
```

![1.PNG](/Images/Full_Scale_Range.png)

- Call the function MPU_Calibration to do the calibration to avoid errors

```arduino
MPU_Calibration();
delay(20);
}// end of setup
```

## Functions :

We have only one function which is MPU_Calibration() that Calibrates the MPU6050 by collecting gyroscope data samples and calculating the average offset value 

```arduino
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
  gyro_Offset_z /= Samples ;                 // calculating the average offset value to subtract from the data to limit the error
}
```

## Loop :

- Calculate the time difference between two steps by storing the start time in the variable (previous_time) and then read the actual time and store it in the variable (current_time) and get the difference between them , the result will be in milliseconds so we divide by 1000 to git the time difference in seconds

```arduino
void loop() {
  // reading Gyro data 
 previous_time = current_time ;                        // Previous time is stored before the actual time read 
 current_time  = millis();                            // Current time actual time read
 dt = (current_time - previous_time ) / 1000 ;       // dt is the time diffrenece between two steps and we divide by 1000 to git the time in seconds
```

- Use the wire.h library to communicate with the sensor , then choose the register we want talk to which in our case will be GYRO_ZOUT_H because we want to calculate the yaw angle

```arduino
 Wire.beginTransmission(MPU_ADDRESS);               // start communication with MPU6050
 Wire.write(GYRO_ZOUT_H);                          // start with the register GYRO_ZOUT_H which address is 0x47                              
 Wire.endTransmission();                          // end the transmission
```

- Use the (Wire.requestFrom()) function to request data from the sensor which size is 2 bytes, and then store it in 16 bits in the variable (gyro_z)

```arduino
 Wire.requestFrom(MPU_ADDRESS,2);               // request data with size of 2 bytes from MPU
 while (Wire.available() < 2);                 // read the data from the sensor and store it in 2 bytes = 16 bits
 gyro_z = Wire.read() <<8 | Wire.read() ;     // wait untill the data is 2 bytes
```

- To get the correct value of our data we subtract the offset value stored in(gyro_Offset_z) from the variable that store the data read from the sensor (gyro_z) and then we divide the output by 131 which is the sensitivity of the gyroscope for full-scale range we choose (+-250) according to the sensor datasheet

![2.PNG](/Images/Sensetivity.png)

- We calculate the yaw angle using the following equation :

$$
Yaw angle = Yawangle+(Yawrate * dt)
$$

```arduino
 gyro_z_final = (gyro_z - gyro_Offset_z ) / 131 ;           // the sensitivity of the gyroscope for full-scale range of +- 250 ^/s is 131 according to datasheet
 yaw_angle = yaw_angle + ( gyro_z_final * dt);             // according to the rule  yaw_angle = yaw_angle + ( yaw_rate * time difference between two steps) 
 Serial.println(yaw_angle);                               // printing the yaw angle to the serial monitor
} //end of loop 
```

## Uploading the code :

Finally, we upload the code and then we would be able to measure the yaw angle using the MPU6050 sensor

---

# Question :

If the Sensor is surrounded by a noisy environment, what type of filter could used and what is the recommended cutoff frequency depending on the sensor datasheet?

# Answer:

- Complementary filters and Kalman filters are commonly used for orientation estimation in IMU applications, but my choice would be complementary filter as Kalman filter would be more complex and our project needs  a straightforward and computationally efficient solution for estimating yaw angle with reasonable accuracy.
- According to the sensor datasheet, the cutoff frequency depend on the configuration we choose to write to the register DLPF_CFG and then the cutoff frequency will be equal to the bandwidth, for example if we write to the register 0x10 then the cutoff frequency = 98 HZ and the sampling frequency = 1 KHZ

![sensor sheet.PNG](/Images/Filter_Data_Sheet.png)