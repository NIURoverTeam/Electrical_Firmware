#include <Servo.h>

//#define right_pwr 10
//#define left_pwr 11
//#define right_dir 12
//#define left_dir 13
//#define REVERSE HIGH
//#define FORWARD LOW

int lDirByte = 0;
int lSpeedByte = 0;
int rDirByte = 0;
int rSpeedByte = 0;

int Lval = 0;
int Rval = 0;

#define LEFT_TALON   13
#define RIGHT_TALON  12

Servo LTalon;
Servo RTalon;
unsigned long tick;

void setup() {
//  pinMode(left_pwr, OUTPUT);
//  pinMode(right_pwr, OUTPUT);
//  pinMode(left_dir, OUTPUT);
//  pinMode(right_dir, OUTPUT);
  Serial.begin(9600);
  LTalon.attach(LEFT_TALON);             // attaches motors to the servo objects with corresponding (pins)
  RTalon.attach(RIGHT_TALON);
  tick = millis();
}


void loop()
{
  if (millis() - tick >= 1000) {
  //  stopMovement();
    tick = millis();
  }

  if (Serial.available()) {
    uint32_t first = Serial.read();
    while (!Serial.available()) {
      if (millis() - tick >= 1000) {
//        stopMovement();
        tick = millis();
        return;
      }
    }
    uint32_t second = Serial.read();

//    switch (first) {
//      case 'L':
//        forwardMove(left_pwr, left_dir, second);
//        break;
//      case 'R':
//        forwardMove(right_pwr, right_dir, second);
//        break;
//      case 'l':
//        reverseMove(left_pwr, left_dir, second);
//        break;
//      case 'r':
//        reverseMove(right_pwr, right_dir, second);
//        break;
//      default:
//        stopMovement();
//        break;
//    }
    if (first == 76)
      Lval = 1500+(second*2);
    else if (first == 108)
      Lval = 1500-(second*2);
    if (first == 82)
      Rval = 1500+(second*5);
    else if (first == 114)
      Rval = 1500-(second*5);
    else {
      stopMovement();
    }
    LTalon.write(Lval);
    RTalon.write(Rval);
    tick = millis();
  }
}

void stopMovement () {
  LTalon.write(1500);
  RTalon.write(1500);
  return;
}

//void forwardMove(int motor_pin, int dir_pin, int pwm) {
//  analogWrite(motor_pin, pwm);
//  digitalWrite(dir_pin, FORWARD);
//  return;
//}
//
//void reverseMove(int motor_pin, int dir_pin, int pwm) {
//  analogWrite(motor_pin, pwm);
//  digitalWrite(dir_pin, REVERSE);
//  return;
//}
//
//void stopMovement () {
//  digitalWrite(left_pwr, 0);
//  analogWrite(left_dir, FORWARD);
//  digitalWrite(right_pwr, 0);
//  analogWrite(right_dir, FORWARD);
//  return;
//}
