int stepVertPin = 13; //#this one apparently has less power relative to the one connected to pin3
int dirVertPin =12; 

//VRy = arduino pin for Joystick
const int VRy = A0;

//temp jpystick value
int joyY;

//mapy value of joystick
int mapy = 0; 

int btn1 = 2;
int btn2 = 3;

  
void setup() {
  // put your setup code here, to run once:
pinMode(dirVertPin, OUTPUT);
pinMode(stepVertPin, OUTPUT);
pinMode(btn1, INPUT);
pinMode(btn2, INPUT);
Serial.begin(9600);
  
}


void joy(){ //joystick code
 joyY = analogRead(VRy); //sets joyY to take in the values read at A0(joystick pin location in the arduino)
 mapy = map(joyY, 0,1023,0,180); // converts our original joystick values of 0-1023 to 0-180

 Serial.print("Value: "); // prints this to the serial monitor in order for us to see our value
 Serial.println(mapy); // prints out our value

}

void loop(){
  bool clk1 = 0;
  bool clk2 = 0;
  
  if(!btn1)
    Serial.print("1\n");
    clk1 = 1;
    clk2 = 0;
    delay(3);

  if(!btn2)
    Serial.print("2\n");
    clk2 = 1;
    clk1 = 0;
    delay(3);

    
  if(clk1){
    // put your main code here, to run repeatedly:
    joy();
    if(mapy > 100){
      digitalWrite(dirVertPin, LOW);      //this sets spinning direction counterclockwise
      while(clk1){
        for(int i = 0; i < 700; i++){
          joy();
          digitalWrite(stepVertPin, HIGH);  //turns telescoping motor on
          digitalWrite(stepVertPin, LOW);   //turns telescoping motor off
          if(!btn1 || !btn2){
            clk1 = 0;
            clk2 = 1;
            delay(3);
          }
        }
      }
     }
  
     if(mapy < 80){
      digitalWrite(dirVertPin, HIGH);      //this sets spinning direction counterclockwise
      while(clk1){
        for(int i = 0; i < 700; i++){
          Serial.print("move\n");
          joy();
          digitalWrite(stepVertPin, HIGH);  //turns telescoping motor on
          digitalWrite(stepVertPin, LOW);   //turns telescoping motor off
        if(!btn1 || !btn2){
          clk1 = 0;
          clk2 = 1;
          delay(3);
        }
      }
     }  
    }
  }  



    if(clk2){
    // put your main code here, to run repeatedly:
    joy();
    if(mapy > 100){
      digitalWrite(dirVertPin, LOW);      //this sets spinning direction counterclockwise
      while(clk2){
        for(int i = 0; i < 700; i++){
          joy();
          digitalWrite(stepVertPin, HIGH);  //turns telescoping motor on
          digitalWrite(stepVertPin, LOW);   //turns telescoping motor off
         if(!btn1 || !btn2){
          clk1 = 1;
          clk2 = 0;
          delay(3);
        }
        }
     }
    }
     if(mapy < 80){
      digitalWrite(dirVertPin, HIGH);      //this sets spinning direction counterclockwise
      while(clk2){
        for(int i = 0; i < 700; i++){
          Serial.print("move\n");
          joy();
          digitalWrite(stepVertPin, HIGH);  //turns telescoping motor on
          digitalWrite(stepVertPin, LOW);   //turns telescoping motor off
        if(!btn1 || !btn2){
          clk1 = 1;
          clk2 = 0;
          delay(3);
        }
      }
     }  
    }
  } 
 } 
