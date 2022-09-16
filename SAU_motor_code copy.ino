
//**********************//
//
//    SAU motor code
// by: Griffin Schroeder
//  start date: 3-3-21
//
//**********************//

// because of the 'autonomous' aspect, code will be
// set on a timer. When the arduino obtains power,
// the state machine will begin from start to end.
// The machine will repeat itself until power turns off


  //define motor that raises/lowers auger. This motor will require a DM542 driver and a 24V battery
  int stepVertPin = 13; //#this one apparently has less power relative to the one connected to pin3
  int dirVertPin =12; 

  //define motor that spins auger. This motor will require a DM542 driver and a 24V battery
  int stepSpinPin = 4;
  int dirSpinPin = 5;

  //define motor for collection cup. This motor will also require a DM542 driver and a 24V battery
  int stepCupPin = 6;
  int dirCupPin = 7;

int RelayPin = 8;          //linear actuator pin


void setup(){

  //declare pins as output
  pinMode(dirVertPin, OUTPUT);
  pinMode(stepVertPin, OUTPUT);
  pinMode(dirSpinPin, OUTPUT);
  pinMode(stepSpinPin, OUTPUT);
  pinMode(dirCupPin, OUTPUT);
  pinMode(stepCupPin, OUTPUT); 

  pinMode(RelayPin, OUTPUT);    //linear actuator initializer
}

void loop(){

  int i; 
/*
  //here is where the flowchart takes place

delay(3000);    //initial pause to start
  
  //lowers auger into ground

  digitalWrite(dirVertPin, HIGH);     //sets spinning direction clockwise
    
  for(i = 0; i < 6000; i++){      //turns motor how every many rotations
    digitalWrite(stepVertPin, LOW);  //turns telescoping motor on
    delayMicroseconds(2500);          //accelerating speed
    digitalWrite(stepVertPin, LOW);   //turns telescoping motor off
    delayMicroseconds(2500);          //decelerating speed 
  }
/*
delay(2000);

//spin auger while in ground
*/
  digitalWrite(dirSpinPin, HIGH);     //sets spinning direction clockwise
    
  for(i = 0; i < 2000; i++){       //turns motor how every many rotations
    digitalWrite(stepSpinPin, LOW);  //turns spinning motor on
    delayMicroseconds(1200);          //accelerating speed
    digitalWrite(stepSpinPin, LOW);   //turns spinning motor off
    delayMicroseconds(1200);          //decelerating speed 
  }

delay(2000);

  //raises auger back up, spinning motor is motionless
  
  digitalWrite(dirVertPin, LOW);      //this sets spinning direction counterclockwise
  for(i = 0; i < 925; i++){
    digitalWrite(stepVertPin, HIGH);  //turns telescoping motor on
    delayMicroseconds(2500);          //accelerating speed
    digitalWrite(stepVertPin, LOW);   //turns telescoping motor off
    delayMicroseconds(2500);          //decelerating speed 
  }

delay(2000);

  //collection cup slides underneath auger
  
  digitalWrite(dirCupPin, LOW);      //sets spinning direction clockwise
  for(i = 0; i < 4300; i++){
    digitalWrite(stepCupPin, HIGH);  //turns collection cup motor on
    delayMicroseconds(1200);          //accelerating speed
    digitalWrite(stepCupPin, LOW);   //turns collection cup motor off
    delayMicroseconds(1200);          //decelerating speed  
  }
  
delay(2000);

  //auger spins counterclockwise, emptying soil into collection cup

  digitalWrite(dirSpinPin, LOW);      //sets spinning direction counterclockwise
  for(i = 0; i < 2000; i++){
    digitalWrite(stepSpinPin, HIGH);  //turns spinning motor on
    delayMicroseconds(1200);          //accelerating speed
    digitalWrite(stepSpinPin, LOW);   //turns spinning motor off
    delayMicroseconds(1200);          //decelerating speed
  }

delay(2000);

  //collection cup slides underneath sensors
  
  digitalWrite(dirCupPin, HIGH);      //sets spinning direction clockwise
  for(i = 0; i < 4300; i++){
    digitalWrite(stepCupPin, HIGH);  //turns collection cup motor on
    delayMicroseconds(1200);          //accelerating speed
    digitalWrite(stepCupPin, LOW);   //turns collection cup motor off
    delayMicroseconds(1200);          //decelerating speed  
  }

delay(5000);


//  digitalWrite(RelayPin, HIGH);          //lower sensor down
//  delay(5000);                           //wait for sensor measurements
  
//  digitalWrite(RelayPin, LOW);           //raise sensor back up
//  delay(2000);


  //collection cup empties into waste bin

  digitalWrite(dirCupPin, HIGH);      //sets spinning direction clockwise
  for(i = 0; i < 11000; i++){
    digitalWrite(stepCupPin, HIGH);  //turns collection cup motor on
    delayMicroseconds(1200);          //accelerating speed
    digitalWrite(stepCupPin, LOW);   //turns collection cup motor off
    delayMicroseconds(1200);          //decelerating speed  
  }

delay(2000);

  //collection cup goes back to home position

  digitalWrite(dirCupPin, LOW);      //sets spinning direction counterclockwise
  for(i = 0; i < 11000; i++){
    digitalWrite(stepCupPin, HIGH);  //turns collection cup motor on
    delayMicroseconds(1200);          //accelerating speed
    digitalWrite(stepCupPin, LOW);   //turns collection cup motor off
    delayMicroseconds(1200);          //decelerating speed  
  }

delay(15000);


}   //the loop then ends and begins the process again until power from arduino
    //is disconnected */
