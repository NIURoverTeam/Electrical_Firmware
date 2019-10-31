#include <Servo.h>
#include <Wire.h>

int Lval = 1500;
int Rval = 1500;

int lDirByte = 0;
int lSpeedByte = 0;
int rDirByte = 0;
int rSpeedByte = 0;

#define LEFT_TALON   13
#define RIGHT_TALON  12
#define MULTIPLIER   1   //Set to 2 for full speed, 1 for half, etc.

Servo LTalon;
Servo RTalon;
unsigned long tick;

void setup() {
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
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
}

//executes every time something is sent over i2c
void receiveEvent(int howMany)
{
  tick = millis();

  //set the first byte to dirByte and the second to speedByte
  lDirByte = Wire.read();
  lSpeedByte = Wire.read();
  rDirByte = Wire.read();
  rSpeedByte = Wire.read();

  if (lDirByte == 76)
    Lval = 1500+(lSpeedByte * MULTIPLIER);
  else if (lDirByte == 108)
    Lval = 1500-(lSpeedByte * MULTIPLIER);
  else
    Lval = 1500;

  if (rDirByte == 82)
    Rval = 1500+(rSpeedByte * MULTIPLIER);
  else if (rDirByte == 114)
    Rval = 1500-(rSpeedByte * MULTIPLIER);
  else
    Rval = 1500;

  LTalon.write(Lval);
  RTalon.write(Rval);
}

void stopMovement () {
  Lval = 1500;
  Rval = 1500;
  LTalon.write(1500);
  RTalon.write(1500);
  return;
}
