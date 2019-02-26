// rf69 demo tx rx.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple addressed, reliable messaging client
// with the RH_RF69 class. RH_RF69 class does not provide for addressing or
// reliability, so you should only use RH_RF69  if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example rf69_server.
// Demonstrates the use of AES encryption, setting the frequency and modem 
// configuration

#include <SPI.h>
#include <RH_RF69.h>
#include <RHReliableDatagram.h>
#include <Wire.h>
#include <String.h>

/************ Radio Setup ***************/

// Change to 434.0 or other frequency, must match RX's freq!
#define RF69_FREQ 915.0

// who am i? (server address)
#define MY_ADDRESS     1


#if defined (__AVR_ATmega32U4__) // Feather 32u4 w/Radio
  #define RFM69_CS      8
  #define RFM69_INT     7
  #define RFM69_RST     4
  #define LED           13
#endif

// Singleton instance of the radio driver
RH_RF69 rf69(RFM69_CS, RFM69_INT);

// Class to manage message delivery and receipt, using the driver declared above
RHReliableDatagram rf69_manager(rf69, MY_ADDRESS);


int16_t packetnum = 0;  // packet counter, we increment per xmission

void setup() 
{
  Wire.begin();
  
  Serial.begin(115200);
  //while (!Serial) { delay(1); } // wait until serial console is open, remove if not tethered to computer

  pinMode(LED, OUTPUT);     
  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, LOW);

  Serial.println("Feather Addressed RFM69 RX Test!");
  Serial.println();

  // manual reset
  digitalWrite(RFM69_RST, HIGH);
  delay(10);
  digitalWrite(RFM69_RST, LOW);
  delay(10);
  
  if (!rf69_manager.init()) {
    Serial.println("RFM69 radio init failed");
    while (1);
  }
  Serial.println("RFM69 radio init OK!");
  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM (for low power module)
  // No encryption
  if (!rf69.setFrequency(RF69_FREQ)) {
    Serial.println("setFrequency failed");
  }

  // If you are using a high power RF69 eg RFM69HW, you *must* set a Tx power with the
  // ishighpowermodule flag set like this:
  rf69.setTxPower(20, true);  // range from 14-20 for power, 2nd arg must be true for 69HCW

  // The encryption key has to be the same as the one in the server
  uint8_t key[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  rf69.setEncryptionKey(key);
  
  pinMode(LED, OUTPUT);

  Serial.print("RFM69 radio @");  Serial.print((int)RF69_FREQ);  Serial.println(" MHz");
}


// Dont put this on the stack:
uint8_t data[] = "And hello back to you";
// Dont put this on the stack:
byte buf[2];


int value;


void loop() 
  {
    if (rf69_manager.available())
    {
      //Begin RF Receive stuff
      // Wait for a message addressed to us from the client
      uint8_t len = sizeof(buf);
      uint8_t from;
      if (rf69_manager.recvfromAck(buf, &len, &from)) 
        {
          //buf[len] = 0; // zero out remaining string
          
          Serial.print("Got packet from #"); Serial.print(from);
          Serial.print(" [RSSI :");
          Serial.print(rf69.lastRssi());
          Serial.print("] : [");
          Serial.print(buf[0]);
          Serial.print("], [");
          Serial.print(buf[1]);
          Serial.println("]");
          Blink(LED, 40, 3); //blink LED 3 times, 40ms between blinks
    
          // Send a reply back to the originator client
          if (!rf69_manager.sendtoWait(data, sizeof(data), from))
            Serial.println("Sending failed (no ack)");

          //End RF Receive stuff

          //Begin i2c Stuff
          int dirByte = 0;
          int speedByte = 0;

          //set dirByte and speedByte 
          dirByte = buf[0];
          speedByte = buf[1];
    
          Wire.beginTransmission(8);        // transmit to device #4
          Wire.write(dirByte);              // sends one byte
          Wire.write(speedByte);
          Wire.endTransmission();           // stop transmitting

          //print just to double check on the serial monitor
          Serial.print("dirByte is: ");     
          Serial.println(dirByte);
    
          Serial.print("speedByte is: ");
          Serial.println(speedByte);

          //clear buf out
          memset(buf,0,sizeof(buf));
        }
    }
  }
  
  
  void Blink(byte PIN, byte DELAY_MS, byte loops) {
    for (byte i=0; i<loops; i++)  {
      digitalWrite(PIN,HIGH);
      delay(DELAY_MS);
      digitalWrite(PIN,LOW);
      delay(DELAY_MS);
    }
}


