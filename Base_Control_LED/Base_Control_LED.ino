#include <Servo.h>

int lDirByte = 0;
int lSpeedByte = 0;
int rDirByte = 0;
int rSpeedByte = 0;

int Lval = 0;
int Rval = 0;

#define LEFT_TALON   10
#define RIGHT_TALON  9

//Servo LTalon;
//Servo RTalon;
unsigned long tick;

void setup() {
  Serial.begin(9600);
//  LTalon.attach(LEFT_TALON);             // attaches motors to the servo objects with corresponding (pins)
//  RTalon.attach(RIGHT_TALON);
  tick = millis();
}


void loop()
{
//  if (millis() - tick >= 1000) {
//    stopMovement();
//    tick = millis();
//    return;
//  }

  Serial.print("testing\n");

  if (Serial.available()) {
    uint32_t first = Serial.read();
//    while (!Serial.available()) {
//      if (millis() - tick >= 1000) {
//        stopMovement();
//        tick = millis();
//        return;
//      }
//    }
    uint32_t second = Serial.read();

//    if (first == 'L')           // first byte is 'L' for "left forward"
//      Lval = 1500+(second*2);
//    else if (first == 'l')      // first byte is 'l' for "left backward"
//      Lval = 1500-(second*2);
//
//    if (first == 'R')           // first byte is 'R' for "right forward"
//      Rval = 1500+(second*5);
//    else if (first == 'r')      // first byte is 'r' for "right backward"
//      Rval = 1500-(second*5);
//    else {
//      stopMovement();
//      tick = millis();
//      return;
//    }

    char str[64];
    strcpy(str, "Arduino read: '");
    strcat(str, first);
    strcat(str, second);
    strcat(str, "'\n'");
    Serial.print(str);

    if (first == 'L' or first == 'l') {
      Lval = second;  // read the left joystick value, range [0, 125]
    } else if (first == 'R' or first == 'r') {
      Rval = second;  // read the right joystick value, range [0, 125]
    } else {
//       // something is wrong, stop movement
//       stopMovement();
//       tick = millis();
//       return;
    }

//    // Servos expect degrees in [0, 180]
//    map(Lval, 0, 125, 0, 180);
//    map(Rval, 0, 125, 0, 180);
    // LEDs expect values in [0, 255]
    map(Lval, 0, 125, 0, 255);
    map(Rval, 0, 125, 0, 255);

//    LTalon.write(Lval);
//    RTalon.write(Rval);
    analogWrite(LEFT_TALON, Lval);
    analogWrite(RIGHT_TALON, Rval);
    tick = millis();
  }
}

//void stopMovement () {
//  lDirByte = 0;
//  lSpeedByte = 0;
//  rDirByte = 0;
//  rSpeedByte = 0;
//  LTalon.write(1500);
//  RTalon.write(1500);
//  return;
//}
