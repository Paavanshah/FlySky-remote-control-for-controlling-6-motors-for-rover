/*
Motor Driver: - MD10C Rev3.0 Cytron motor driver
Johnson Geared Motor (Grade B) 300 RPM
Arduino Nano
*/


// Channels connections
#define CH1 10
#define CH2 11

// Motors connections
const int pwm1 = 3;
const int dir1 = 2;

const int pwm2 = 5;
const int dir2 = 4;

const int pwm3 = 9;
const int dir3 = 8;

// Integers to represent values from the channels

// Thresholds to define the direction
int thresholdForward = 20;    // CH1 above this value means forward
int thresholdBackward = -20;  // CH1 below this value means backward
int thresholdLeft = -20;      // CH2 below this value means left
int thresholdRight = 20;      // CH2 above this value means right

int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue) {
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

void setup() {
  // Set up serial monitor
  Serial.begin(115200);

  // Set all pins as inputs
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);

  // Pins for motors
  pinMode(pwm1, OUTPUT);
  pinMode(dir1, OUTPUT);

  pinMode(pwm2, OUTPUT);
  pinMode(dir2, OUTPUT);

  pinMode(pwm3, OUTPUT);
  pinMode(dir3, OUTPUT);
}

void loop() {
  // Get values for CH1 and CH2
  int ch1Value = readChannel(CH1, -100, 100, 0);
  int ch2Value = readChannel(CH2, -100, 100, 0);

  // Determine rover movement based on channel values
  bool forward = (ch1Value > thresholdForward);
  bool backward = (ch1Value < thresholdBackward);
  bool left = (ch2Value < thresholdLeft);
  bool right = (ch2Value > thresholdRight);

  // Decision combinations
  if (forward && left) {
    Serial.println("Forward Left");
    Serial.println("channel 1:");
    Serial.println(ch1Value);
    Serial.println("channel 2:");
    Serial.println(ch2Value);
    // Add code for rover movement - e.g., motors, wheels, etc.
  } else if (forward && right) {
    Serial.println("Forward Right");
    Serial.println("channel 1:");
    Serial.println(ch1Value);
    Serial.println("channel 2:");
    Serial.println(ch2Value);
    // Add code for rover movement
  } else if (forward) {
    Serial.println("Forward");
    Serial.println("channel 1:");
    Serial.println(ch1Value);
    int pwmfor = map(ch1Value, 0, 100, 0, 255);  
    Serial.println("channel 2:");
    Serial.println(ch2Value);
    Serial.println("forwd");

    digitalWrite(dir1, LOW);    // LOW forward ............HIGH Backward
    analogWrite(pwm1, pwmfor);  // always set PWM to HIGH

    digitalWrite(dir2, LOW);    // LOW forward ............ HIGH Backward
    analogWrite(pwm2, pwmfor);  // always set PWM to HIGH

    digitalWrite(dir3, LOW);    // LOW....forward             HIGH backward
    analogWrite(pwm3, pwmfor);  // always set PWM to HIGH
  } else if (backward && left) {
    Serial.println("Backward Left");
    Serial.println("channel 1:");
    Serial.println(ch1Value);
    Serial.println("channel 2:");
    Serial.println(ch2Value);
    // Add code for rover movement
  } else if (backward && right) {
    Serial.println("Backward Right");
    Serial.println("channel 1:");
    Serial.println(ch1Value);
    Serial.println("channel 2:");
    Serial.println(ch2Value);
    // Add code for rover movement
  } else if (backward) {
    Serial.println("Backward");
    Serial.println("channel 1:");
    Serial.println(ch1Value);
    Serial.println("channel 2:");
    Serial.println(ch2Value);
   int a=ch1Value*(-1);
   Serial.println(a);
    int pwmbac = map(a, 0, 100, 0, 255);
    Serial.println("back");

    digitalWrite(dir1, HIGH);   // LOW forward ............HIGH Backward
    analogWrite(pwm1, pwmbac);  // always set PWM to HIGH

    digitalWrite(dir2, HIGH);   // LOW forward ............ HIGH Backward
    analogWrite(pwm2, pwmbac);  // always set PWM to HIGH

    digitalWrite(dir3, HIGH);   // LOW....forward             HIGH backward
    analogWrite(pwm3, pwmbac);  // always set PWM to HIGH
    // Add code for rover movement
  } else if (right) {
    Serial.println("right");
    Serial.println("channel 1:");
    Serial.println(ch1Value);
    Serial.println("channel 2:");
    Serial.println(ch2Value);


    int pwmright = map(ch2Value, 0, 100, 0, 180);

    Serial.println("right");


    digitalWrite(dir1, HIGH);      // LOW forward ............HIGH Backward
    analogWrite(pwm1, pwmright);  // always set PWM to HIGH


    digitalWrite(dir2, HIGH);      // LOW back ............ HIGH forward
    analogWrite(pwm2, pwmright);  // always set PWM to HIGH

    digitalWrite(dir3, LOW);     //LOW....forward             HIGH backward
    analogWrite(pwm3, pwmright);  // always set PWM to HIGH
  } else if (left) {
    Serial.println("left");
    Serial.println("channel 1:");
    Serial.println(ch1Value);
    Serial.println("channel 2:");
    Serial.println(ch2Value);
    
    int a=ch2Value*(-1);
    Serial.println(a);
    int pwmleft = map(a, 0, 100, 0, 255);
    //int pwmleft = map(ch2Value, 0, 100, 0, 180);

    Serial.println("left");


    digitalWrite(dir1, LOW);      // LOW forward ............HIGH Backward
    analogWrite(pwm1, pwmleft);  // always set PWM to HIGH


    digitalWrite(dir2, LOW);      // LOW back ............ HIGH forward
    analogWrite(pwm2, pwmleft);  // always set PWM to HIGH

    digitalWrite(dir3, HIGH);     //LOW....forward             HIGH backward
    analogWrite(pwm3, pwmleft);  // always set PWM to HIGH

  } else {
    Serial.println("Stopped");
    Serial.println("channel 1:");
    Serial.println(ch1Value);
    Serial.println("channel 2:");
    Serial.println(ch2Value);
    // Add code for rover to stop or maintain its current state
    //int pwmbac = map(ch1Value, 0, 100, 0, 255);
    Serial.println("Stop");

    digitalWrite(dir1, HIGH);   // LOW forward ............HIGH Backward
    analogWrite(pwm1, 0);  // always set PWM to HIGH

    digitalWrite(dir2, HIGH);   // LOW forward ............ HIGH Backward
    analogWrite(pwm2, 0);  // always set PWM to HIGH

    digitalWrite(dir3, HIGH);   // LOW....forward             HIGH backward
    analogWrite(pwm3, 0);  // always set PWM to HIGH


    
  }

  delay(500);
}
