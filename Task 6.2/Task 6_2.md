# Task 6.2

For this task it is required to interface with rotary Encoder and get the number of counts from the train of impulse from A, and B signals , it is also required to design a Software Practical Low Pass Filter (LPF) to filter the output of the encoder

# Designing the Low Pass Filter

To design the suitable filter for our project we need the specifications of our encoder which are given to us and calculate the cutoff frequency using them :

 

## Steps

- Calculate the cutoff frequency :

```python
# Givens
pulse_per_revolution = 540
wheel_radius = 0.2      # radius = diameter / 2 = 0.4 / 2 =0.2
max_speed = 0.5 
time_for_revolution =  (2* np.pi *wheel_radius) /  max_speed
pulse_per_second =np.ceil(pulse_per_revolution / time_for_revolution) 
cutOff_freq = pulse_per_second       # cutt off frequency 
sampling_freq = 1000                 # sampled at 1 kHz = 1000 samples / second
w0 = 2 * np.pi * cutOff_freq         # 
numerator = w0                                     # transfer function numerator coefficients
denominator = [1,w0]                                 # transfer function denominator coefficients
lowPass = signal.TransferFunction(numerator, denominator)  # Transfer function
```

- Use the Low pass Filter equation :

```python
cutOff_freq = pulse_per_second       # cutt off frequency 
sampling_freq = 1000                 # sampled at 1 kHz = 1000 samples / second
w0 = 2 * np.pi * cutOff_freq         # 
numerator = w0                                     # transfer function numerator coefficients
denominator = [1,w0]                                 # transfer function denominator coefficients
lowPass = signal.TransferFunction(numerator, denominator)  # Transfer function
```

- Discrete Transfer Function :

```python
dt = 1.0/sampling_freq;                      #time step = dt = 1/sampling frequency
discreteLowPass = lowPass.to_discrete(dt, method='gbt' ,alpha=0.5)  # the to_discrete function is used to compute the bilinear transform (Tustin's method)
```

- Get the Filter coefficients :

```python
b = discreteLowPass.num      #extracts the numerator coefficients of the discrete-time filter and stores them in the variable b
a = -discreteLowPass.den     #extracts the denominator coefficients of the discrete-time filter and change thier signs to make them suitable for use in filter implementations
print("Filter coefficients b_i: " + str(b))
print("Filter coefficients a_i: " + str(a[1:]))
```

- Integrate the filter into the Arduino code for the encoder :

      After we acquire the filter coefficients we use them in the following equation to get the filtered        value.

$$
y[n] = a_1 y[n-1] + a_2 y[n-2] + ... + b_0 x[n] + b_1 x[n-1] + ...
$$

---

# Interface with rotary Encoder

We setup the encoder and Integrate the filter into the Arduino code for the encoder to get the filtered counts of the rotary encoder. 

Here is the Arduino code explained :

 

## Hardware Setup :

 

- Connect Encoder Pin A to Digital Pin 2
- Connect Encoder Pin B to Digital Pin 3

```arduino
# define PIN_ENCODER_A  2
# define PIN_ENCODER_B  3
```

## Variables :

```arduino
long long int counter = 0;          //the encoder counts
// the filter coefficients
float coefficients_b [2]= {0.40314272, 0.40314272};
float coefficients_a [2]= {1.0, 0.19371455}; 
// storing the previous states
float previous_input = 0.0;
float previous_output = 0.0;
```

## Setup :

- Initializing the serial monitor
- configure the pins :

       PIN_ENCODER_A  and PIN_ENCODER_B as input pins 

- Attaches interrupt service routines (ISRs) to PIN_ENCODER_A and PIN_ENCODER_B to handle encoder signal changes

```arduino
void setup() {
  Serial.begin(9600);
  // setting up the encoder
  pinMode(PIN_ENCODER_A , INPUT_PULLUP);
  pinMode(PIN_ENCODER_B , INPUT_PULLUP);
  // 
  attachInterrupt(PIN_ENCODER_A, ISR_encoderPinA, CHANGE);
  attachInterrupt(PIN_ENCODER_B, ISR_encoderPinB, CHANGE);
}
```

## The ISR functions :

- The function ISR_encoderPinA is called when data is received from the pin A at encoder and depending on the relation between the state of Pin A and Pin B it changes the number of counts

```arduino
void ISR_encoderPinA(void){
  if (digitalRead(PIN_ENCODER_A) != digitalRead(PIN_ENCODER_B)){
    counter++;    
  }
  else {
    counter--;
  }
}
```

- The function ISR_encoderPinB is called when data is received from the pin B at encoder and depending on the relation between the state of Pin A and Pin B it changes the number of counts

```arduino
void ISR_encoderPinB(void){
  if (digitalRead(PIN_ENCODER_A) == digitalRead(PIN_ENCODER_B)){
    counter++;
  }
  else {
    counter--;
  }
}
```

## Loop :

- A variable current_input of the type (long long) is declared to store the value of the encoder input to maintain the stability of the variable used in the filtering equation so that doesn’t keep changing with the input from the encoder
- The value of current_input is changed to the type float and stored in the variable input
- Substitute in the filtering equation and store the result in the variable output
- Store the current state of the filter as the previous state and get our current state from the next reading
- Print the output to the serial monitor

```arduino
void loop() {
  long current_input = counter;                 // the read value is stored in current_input to prevent it from changing during the calculations

  float input = (float) current_input ;
  float output = (coefficients_a[1]*previous_input) + (coefficients_b[0]*input) + (coefficients_b[1]*previous_input);       //  y[n] =  a1 y[n-1] + b0 x[n] + b1 x[n-1]

  previous_input = input;
  previous_output = output;

  Serial.print("Filtered Encoder Count: ");
  Serial.println(output);
}
```

# Upload the code to the Arduino :

The last step is to upload the code to the Arduino connected to our Encoder and now the have the desired output which is the filtered value of the encoder number of counts .