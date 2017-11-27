#include <Servo.h>

Servo servo1;  // create servo object to control a servo
Servo servo2; 

const int servoButton1 = 2;
const int servoButton2 = 3;

// actual position of each servo
int servo1Val = 0;   
int servo2Val = 0;    
// states of both servos
int button1State = 0;
int button2State = 0;

int potpin = 0;
// speed of the servos
int servoSpeed;

void setup() {
  servo1.attach(9);  // attaches the servo on pin 9 to the servo object
  servo2.attach(10);
  pinMode(servoButton1, INPUT);
  pinMode(servoButton2, INPUT);
}

void loop() {
  button1State = digitalRead(servoButton1);
  button2State = digitalRead(servoButton2);
  servoSpeed = analogRead(potpin);
  servoSpeed = map(servoSpeed, 0, 1023, 1, 20);

  if (button1State == HIGH && servo1Val < 180){
    servo1Val++;
  }
  else if (servo1Val > 0) {
    servo1Val--;
  }
  if (button2State == HIGH && servo2Val < 180) {
    servo2Val++;
  }
  else if (servo2Val > 0) {
    servo2Val--;
  }
  servo1.write(servo1Val);
  servo2.write(servo2Val);
  delay(servoSpeed);
}

