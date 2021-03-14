#include <Servo.h>

int lDirByte = 0;
int lSpeedByte = 0;
int rDirByte = 0;
int rSpeedByte = 0;

int Lval = 0;
int Rval = 0;

#define LEFT_TALON   10
#define RIGHT_TALON  9

Servo LTalon;
Servo RTalon;
unsigned long tick;

void setup() {
  Serial.begin(9600);
  LTalon.attach(LEFT_TALON);             // attaches motors to the servo objects with corresponding (pins)
  RTalon.attach(RIGHT_TALON);
  tick = millis();
}


void loop()
{
  if (millis() - tick >= 1000) {
    stopMovement();
    tick = millis();
    return;
  }

  if (Serial.available()) {
    uint32_t first = Serial.read();
    while (!Serial.available()) {
      if (millis() - tick >= 1000) {
        stopMovement();
        tick = millis();
        return;
      }
    }
    uint32_t second = Serial.read();

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
      tick = millis();
      return;
    }
    LTalon.write(Lval);
    RTalon.write(Rval);
    tick = millis();
  }
}

void stopMovement () {
  lDirByte = 0;
  lSpeedByte = 0;
  rDirByte = 0;
  rSpeedByte = 0;
  LTalon.write(1500);
  RTalon.write(1500);
  return;
}
