
// --------------------------- SLAVE ---------------------------

#include <Arduino.h>

#include <Auto_Serial_Speed.h>

#define Serial_Speed 115200

Auto_Serial_Speed STest(1);





void setup() {
  Serial.begin(Serial_Speed);
  Serial.println("Doot - Speed Test - Slave");


  STest.Test_Speed_Slave(1);


  Serial.println("Doot Done - Speed Test - Slave");

} // setup


void loop() {


  delay(1000);


} // loop
