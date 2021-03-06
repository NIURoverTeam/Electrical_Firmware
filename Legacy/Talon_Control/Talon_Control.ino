//Using servo objects for the talons because they're weird
#include <Servo.h>
#include <Wire.h>

#define LEFT_TALON    13
#define RIGHT_TALON   12

int lDirByte = 0;
int lSpeedByte = 0;
int rDirByte = 0;
int rSpeedByte = 0;

int Lval = 0;
int Rval = 0;

//attach motors to servo objects
Servo LTalon;  //creating servo objects for each individual talon
Servo RTalon; 

unsigned long tick;

void setup()
{
	Wire.begin(8);                  //begin i2c address 
  Serial.begin(9600);
  Wire.onReceive(receiveEvent);   //to be exectued each time i2c transaction occurs
	LTalon.attach(LEFT_TALON);             // attaches motors to the servo objects with corresponding (pins)
	RTalon.attach(RIGHT_TALON);
}

void loop() 
{
	if (millis() - tick >= 1000) 
	{
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
		Lval = 1500+(lSpeedByte*5);
	else if (lDirByte == 108)
		Lval = 1500-(lSpeedByte*5);
	else
		Lval = 1500;

	if (rDirByte == 82)
		Rval = 1500+(rSpeedByte*5);
	else if (rDirByte == 114)
		Rval = 1500-(rSpeedByte*5);
	else
		Rval = 1500;

	LTalon.write(Lval);
	RTalon.write(Rval);
}

void stopMovement () {
	LTalon.write(1500);
	RTalon.write(1500);
	return;
}
