//Defined Names of the Pins//

int channel_1 = A0 ;
int channel_2 = A1 ;
int channel_3 = A2 ;
int channel_4 = A3 ;
int channel_5 = A4 ;
int channel_6 = A5 ;

//////Directions///////
int forward = A6 ;
int backward = A7 ;
int left = A8 ;
int right = A9 ;
//////////////////////////

void setup() 
{
  Serial.begin(9600); //Baud Rate Begin//
  
  ///////Analog Inputs//////////
  pinMode(A0 , INPUT) ;
  pinMode(A1 , INPUT) ;
  pinMode(A2 , INPUT) ;
  pinMode(A3 , INPUT) ;
  pinMode(A4 , INPUT) ;
  pinMode(A5 , INPUT) ;
  ///////////////////////////

  pinMode(forward , OUTPUT) ;
  pinMode(backward , OUTPUT) ;
  pinMode(left , OUTPUT) ;
  pinMode(right , OUTPUT) ;
}

void loop()
{
//Set names to read the values of the channels//
int ch_1val = 0 ;
int ch_2val = 0 ;
int ch_3val = 0 ;
int ch_4val = 0 ;
int ch_5val = 0 ;
int ch_6val = 0 ;

int forward = 0 ;
int backward = 0 ;
int left = 0 ;
int right = 0;

///////Read Values//////////
ch_1val = analogRead(channel_1) ;
ch_2val = analogRead(channel_2) ;
ch_3val = analogRead(channel_3) ;
ch_4val = analogRead(channel_4) ;
ch_5val = analogRead(channel_5) ;
ch_6val = analogRead(channel_6) ;
////////////////////////////




/////Writes Data to Serial Monitor///////////
Serial.print(ch_1val) ;
Serial.print('\n') ;
//Serial.print(ch_2val) ;
//Serial.print('\n') ;
//Serial.print(ch_3val) ;
//Serial.print(ch_4val) ;
//Serial.print(ch_5val) ; 



//////////////////////////////////////////////
delay(750) ; //Delayed by 750 ms to read the data// 
}
