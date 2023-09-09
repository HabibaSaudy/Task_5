# define PIN_ENCODER_A  2
# define PIN_ENCODER_B  3

// intializing and declaring variables
long long int counter = 0;
// the filter coefficients
float coefficients_b [2]= {0.40314272, 0.40314272};
float coefficients_a [2]= {1.0, 0.19371455}; 
// storing the previous states
float previous_input = 0.0;
float previous_output = 0.0;

void setup() {
  Serial.begin(9600);
  // setting up the encoder
  pinMode(PIN_ENCODER_A , INPUT_PULLUP);
  pinMode(PIN_ENCODER_B , INPUT_PULLUP);
  // 
  attachInterrupt(PIN_ENCODER_A, ISR_encoderPinA, CHANGE);
  attachInterrupt(PIN_ENCODER_B, ISR_encoderPinB, CHANGE);
}

void loop() {
  long current_input = counter;                 // the read value is stored in current_input to prevent it from changing during the calculations

  float input = (float) current_input ;
  float output = (coefficients_a[1]*previous_input) + (coefficients_b[0]*input) + (coefficients_b[1]*previous_input);       //  y[n] =  a1 y[n-1] + b0 x[n] + b1 x[n-1]

  previous_input = input;
  previous_output = output;

  Serial.print("Filtered Encoder Count: ");
  Serial.println(output);
}

void ISR_encoderPinA(void){
  if (digitalRead(PIN_ENCODER_A) != digitalRead(PIN_ENCODER_B)){
    counter++;    
  }
  else {
    counter--;
  }
}

void ISR_encoderPinB(void){
  if (digitalRead(PIN_ENCODER_A) == digitalRead(PIN_ENCODER_B)){
    counter++;
  }
  else {
    counter--;
  }
}
