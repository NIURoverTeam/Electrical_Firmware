#include <Servo.h>
unsigned long tick;
int percent_left = 0;
int percent_right = 0;
int pins[] = {2, 3};
int arm_pins[] = {A0, 13};
const int numPins = 2;
Servo controllers[numPins];
const int move_percent = -20;
const int arm_power = 150;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  controllers[0].attach(pins[0]);
  delay(1000);
  controllers[1].attach(pins[1]);
  delay(1000);
  tick = millis();
  pinMode(arm_pins[0], OUTPUT);
  pinMode(arm_pins[1], OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
//  if (tick - millis() > 1000) {
//    controllers[0].writeMicroseconds(1500);
//    controllers[1].writeMicroseconds(1500);
//    tick = millis();
//  }
  
  
  if (Serial.available() > 1) {
    char command = Serial.read();
    if (command == 'w') {percent_left = move_percent; percent_right = move_percent;} //w
    else if (command == 'a') {percent_left = -move_percent * 1.5; percent_right = move_percent;} //a
    else if (command == 's') {percent_left = -move_percent; percent_right = -move_percent;}//s
    else if (command == 'd') {percent_left = -move_percent * 2; percent_right = move_percent * 2;}//d
    else if (command == 'q') {analogWrite(arm_pins[0], arm_power); digitalWrite(arm_pins[1], LOW);}
    else if (command == 'e') {analogWrite(arm_pins[0], arm_power); digitalWrite(arm_pins[1], HIGH);}
    else {percent_left = 0; percent_right = 0; analogWrite(arm_pins[0], 0);}
    int PWM_left = percent_left * 5 + 1500;
    int PWM_right = percent_right * 5 + 1500;
    controllers[0].writeMicroseconds(PWM_left);
    controllers[1].writeMicroseconds(PWM_right);
    tick = millis();
  }
}
