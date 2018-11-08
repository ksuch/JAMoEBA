#include "Arduino.h"
#include "stdint.h"
#include "SCMD.h"
#include "SCMD_config.h"
#include "Wire.h"

SCMD myMotorDriver;

void setup() {
  pinMode(8,INPUT_PULLUP); //GND
  
  Serial.begin(9600);
  //Configuring Motor Driver Settings
  myMotorDriver.settings.commInterface = I2C_MODE;
  myMotorDriver.settings.I2CAddress = 0x5A;
  

  //initializing the driver to wait for idle
  while  (myMotorDriver.begin() != 0xA9)
    {
      Serial.println( "Incorrect ID :/" );
      delay(500);
    }
    Serial.println  ( "ID matches 0xA9 :D" )
    
    //Check the driver is done looking for slaves
    Serial.print("Looking for more slaves...")
    while ( myMotorDriver.ready() == false );
    Serial.println( "Done!" )
    Serial.println();

    //Inverting motor 1
    while ( myMotorDriver.busy());
    myMotorDriver.inversionMode(1,1);

    //Enable output driver hardware
    while ( myMotorDriver.busy ());
    myMotorDriver.enable();
}

#define LM 0
#define RM 1
void loop() {
  // setDrive takes a motor number, direction as 0 or 1 and level from 0 to 255
  myMotorDriver.setDrive( LM, 0, 0); //Stop motor
  myMotorDriver.setDrive( RM, 0, 0); //Stop motor
  while (digitalRead(8) == 0);
    for (int i=0; i<256; i++)
    {
      myMotorDriver.setDrive( LM,0,i); //Increase speed of left motor and back
      myMotorDriver.setDrive( RM, 0,20 + (i/2));
      delay(5);
      }
     for (int i=255; i>=0; i--)
     {
      myMotorDriver.setDrive( LM, 0, i);
      myMotorDriver.setDrive( RM,0, 20+ (i/2));
      delay(5);
      }
     for (int = 0, i<256; i++)
     {
      myMotorDriver.setDrive( LM, 0, 20, (i/2)); //Increase speed of right motor and back
      myMotorDriver.setDrive(RM, 0, i);
      }
     for (int i=255; i>= 0; i--);
     {
      myMotorDriver.setDrive( LM,0,20+(i/2));
      myMotorDriver.setDrive( RM, 0, i);
      delay(5);
      } 
}

