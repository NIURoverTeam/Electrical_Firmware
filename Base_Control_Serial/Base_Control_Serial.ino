#include <Servo.h>

int Lval = 1500;
int Rval = 1500;

#define LEFT_TALON   13
#define RIGHT_TALON  12

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

    // Note: 'second' ranges from 0 to 255. The full range on the talon is 1500 +- 500.
    //       If you want it to have other than half power, add a multiplier
    switch (first) {
      case 'L':
        Lval = 1500+(second);
        break;
      case 'R':
        Rval = 1500+(second);
        break;
      case 'l':
        Lval = 1500-(second);
        break;
      case 'r':
        Rval = 1500-(second);
        break;
      default:
        stopMovement();
        break;
    }
    
    LTalon.write(Lval);
    RTalon.write(Rval);
    tick = millis();
  }
}

void stopMovement () {
  Lval = 1500;
  Rval = 1500;
  LTalon.write(1500);
  RTalon.write(1500);
  return;
}
