//

//Using servo objects for the talons because they're weird
#include <Servo.h>
#include <Wire.h>

int percent = 0;
int PWMval = 0;
int PWMvalInv = 0;

int speedByte = 0;
int dirByte = 0;

//attach motors to servo objects
Servo myservo1;  //creating servo objects for each individual talon
Servo myservo2;  
Servo myservo3; 
Servo myservo4;
Servo myservo5;
Servo myservo6;


  void setup() 
    {
      Wire.begin(8);                  //begin i2c address 
      Wire.onReceive(receiveEvent);   //to be exectued each time i2c transaction occurs
      Serial.begin(9600);             //serial baud rate
      Serial.println("Starting");
      myservo1.attach(3);             // attaches motors to the servo objects with corresponding (pins)
      myservo2.attach(5);
      myservo3.attach(6);
      myservo4.attach(9);
      myservo5.attach(10);
      myservo6.attach(11);
    }

  void loop() 
    {
      delay(100);
    }
  
  
  //executes every time something is sent over i2c
  void receiveEvent(int howMany)
    {
      //set the first byte to dirByte and the second to speedByte
      dirByte = Wire.read();
      speedByte = Wire.read();
          
      //case statement to determine which direction and speed to go
      switch (dirByte) 
        {
          case 0:
            // statements
            Serial.println("Stopping");
            Serial.print("dirByte: ");
            Serial.println(dirByte);      // print the integer
    
            Serial.print("SpeedByte: ");    
            Serial.println(speedByte);      // print the integer
            myservo1.write(1500);                           // sets the servo position according to the scaled value
            myservo2.write(1500);
            myservo3.write(1500);
            myservo4.write(1500);
            myservo5.write(1500);
            myservo6.write(1500);
            Serial.println("---------------------------");
            break;
          
          //Forward
          case 1:
            // statements
            Serial.println("Forward");
            
            Serial.print("dirByte: ");
            Serial.println(dirByte);      // print the integer
    
            Serial.print("SpeedByte: ");    
            Serial.println(speedByte);      // print the integer
            
            PWMval = map(speedByte, 0, 100, 1500, 2000);     // scale it to use it with the servo (value between 0 and 180)
            myservo1.write(PWMval);                           // sets the servo position according to the scaled value
            myservo2.write(PWMval);
            myservo3.write(PWMval);
            myservo4.write(PWMval);
            myservo5.write(PWMval);
            myservo6.write(PWMval);
            
            Serial.print("PWMval: ");
            Serial.println(PWMval);
            Serial.println("---------------------------");
            break;

          //Reverse
          case 2:
            // statements
            Serial.println("Reverse");
            
            Serial.print("dirByte: ");
            Serial.println(dirByte);      // print the integer
    
            Serial.print("SpeedByte: ");    
            Serial.println(speedByte);      // print the integer
            
            PWMval = map(speedByte, 0, 100, 1000, 1500);     // scale it to use it with the servo (value between 0 and 180)
            myservo1.write(PWMval);                           // sets the servo position according to the scaled value
            myservo2.write(PWMval);
            myservo3.write(PWMval);
            myservo4.write(PWMval);
            myservo5.write(PWMval);
            myservo6.write(PWMval);
            
            Serial.print("PWMval: ");
            Serial.println(PWMval);
            Serial.println("---------------------------");
            break;
          
          //Left Turn
          case 3:
            // statements
            Serial.println("Turning Left");
            
            Serial.print("dirByte: ");
            Serial.println(dirByte);      // print the integer
    
            Serial.print("SpeedByte: ");    
            Serial.println(speedByte);      // print the integer

            PWMval = map(speedByte, 0, 100, 1500, 2000);     // scale it to use it with the servo (value between 0 and 180)
            PWMvalInv = map(speedByte, 0, 100, 1500, 1000);
            myservo1.write(PWMval);                           // sets the servo position according to the scaled value
            myservo2.write(PWMval);
            myservo3.write(PWMval);
            myservo4.write(PWMvalInv);
            myservo5.write(PWMvalInv);
            myservo6.write(PWMvalInv);
            
            Serial.print("PWMval: ");
            Serial.println(PWMval);

            Serial.print("PWMvalInv: ");
            Serial.println(PWMvalInv);
            Serial.println("---------------------------");
            
            break;
  
          //Right Turn
            case 4:
            // statements
            Serial.println("Turning Right");
            
            Serial.print("dirByte: ");
            Serial.println(dirByte);      // print the integer
    
            Serial.print("SpeedByte: ");    
            Serial.println(speedByte);      // print the integer
            
            PWMval = map(speedByte, 0, 100, 1500, 2000);     // scale it to use it with the servo (value between 0 and 180)
            PWMvalInv = map(speedByte, 0, 100, 1500, 1000);
            myservo1.write(PWMvalInv);                           // sets the servo position according to the scaled value
            myservo2.write(PWMvalInv);
            myservo3.write(PWMvalInv);
            myservo4.write(PWMval);
            myservo5.write(PWMval);
            myservo6.write(PWMval);
            
            Serial.print("PWMval: ");
            Serial.println(PWMval);

            Serial.print("PWMvalInv: ");
            Serial.println(PWMvalInv);
            Serial.println("---------------------------");
            
            break;
  
          //default case should do nothing
          default:
            // statements
            Serial.println("Waiting, if you entered a value maybe it is invalid");
            Serial.print("dirByte: ");
            Serial.println(dirByte);      // print the integer
    
            Serial.print("SpeedByte: ");    
            Serial.println(speedByte);      // print the integer
            myservo1.write(1500);                           // sets the servo position according to the scaled value
            myservo2.write(1500);
            myservo3.write(1500);
            myservo4.write(1500);
            myservo5.write(1500);
            myservo6.write(1500);
            Serial.println("---------------------------");
            break;
        }

    }
