#include <Servo.h>
#include <SPI.h>

volatile uint8_t byteCount = 0;
volatile bool dataReady = false;

uint8_t data[4];
uint8_t *ptr = (uint8_t *)&data;

int lDirByte = 0;
int lSpeedByte = 0;
int rDirByte = 0;
int rSpeedByte = 0;

int Lval = 0;
int Rval = 0;

#define LEFT_TALON   10
#define RIGHT_TALON  9
#define SPI_PIN      MISO

Servo LTalon;
Servo RTalon;
unsigned long tick;

// SPI interrupt routine
ISR (SPI_STC_vect) {
  ptr[byteCount++] = SPDR;
  if (byteCount == 4) {
    dataReady = true;
  }
}

void setup() {
  Serial.begin(115200);
  SPCR |= bit(SPE);                     // enable SPI slave mode
  pinMode(SPI_PIN, OUTPUT);
  SPI.attachInterrupt();
  LTalon.attach(LEFT_TALON);             // attaches motors to the servo objects with corresponding (pins)
  RTalon.attach(RIGHT_TALON);
  tick = millis();
}


void loop()
{
  if (dataReady) {
    lDirByte = data[0];
    lSpeedByte = data[1];
    rDirByte = data[2];
    rSpeedByte = data[3];
    if (lDirByte == 76)
      Lval = 1500+(lSpeedByte*2);
    else if (lDirByte == 108)
      Lval = 1500-(lSpeedByte*2);
    if (rDirByte == 82)
      Rval = 1500+(rSpeedByte*5);
    else if (rDirByte == 114)
      Rval = 1500-(rSpeedByte*5);
    else {
      stopMovement();
    }
    tick = millis();
    LTalon.write(Lval);
    RTalon.write(Rval);
    dataReady = False;
    byteCount = 0;
  }
  if (tick - millis() >= 1000) {
    tick = millis();
    stopMovement();
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
