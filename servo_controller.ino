#include <Keypad.h>
#include <Servo.h>

// rows and columns of keypad
const byte ROWS = 2;
const byte COLS = 2;

// array of all the keys
char keys[ROWS][COLS] = {
  {'D', '#'},
  {'C', '9'}
};

// binding pins with each kepad row and column
byte rowPins[ROWS] = {4, 5};
byte colPins[COLS] = {2, 3};

// defining the keypad
Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// defining servos
Servo servo0;
Servo servo1;

// pot that is used to modify speed of servo
int potpin = 0;
int servo_speed;

// min val
int servos_min_val = 10;
// max val
int servos_max_val = 180;

int servo0_pos = servos_min_val;
int servo1_pos = servos_min_val;

// variable in order to know if the servo is moving upwards or downwards
// first dimension is each servo and the third one says movement 
// -1 = going down towards servos_min_Val
// 0 = maintining position
// 1 = going upwards to 180
int servos_moving[2][1] = {
  {0},
  {0},
};

void setup() {
  servo0.attach(9);
  servo1.attach(10);

  servo0.write(10);
  servo1.write(servo1_pos);
  
  Serial.begin(9600);

}


void loop() {
  servo_speed = analogRead(potpin);
  servo_speed = map(servo_speed, 0, 1023, 1, 15);


  if (servos_moving[0][0] == -1 && servo0_pos > servos_min_val) {
    servo0_pos--;
    servo0.write(servo0_pos);
    delay(servo_speed);
  }
  if (servos_moving[0][0] == 1 && servo0_pos < servos_max_val) {
    servo0_pos++;
    servo0.write(servo0_pos);
    delay(servo_speed);
  }

  if (servos_moving[1][0] == -1 && servo1_pos > servos_min_val) {
    servo1_pos--;
    servo1.write(servo1_pos);
    delay(servo_speed);
  }
  if (servos_moving[1][0] == 1 && servo1_pos < servos_max_val) {
    servo1_pos++;
    servo1.write(servo1_pos);
    delay(servo_speed);
  }

  if (kpd.getKeys()) {
    for (int i=0; i<LIST_MAX; i++) {
      if (kpd.key[i].stateChanged) {
        switch(kpd.key[i].kstate){
          case RELEASED:
            switch(kpd.key[i].kchar){
              case 'D':
                servos_moving[0][0] = 0;
                break;
              case 'C':
                servos_moving[0][0] = 0;
                break;
              case '#':
                servos_moving[1][0] = 0;
                break;
              case '9':
                servos_moving[1][0] = 0;
                break;
            }
            break;
          case PRESSED:
            switch(kpd.key[i].kchar) {
              case 'D':
                servos_moving[0][0] = 1;
                break;
              case 'C':
                servos_moving[0][0] = -1;
                break;
              case '#':
                servos_moving[1][0] = 1;
                break;
              case '9':
                servos_moving[1][0] = -1;
                break;
            }
            break;
        }
      }
    }
  }
  
}



