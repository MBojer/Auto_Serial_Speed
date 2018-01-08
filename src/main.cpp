#include <Arduino.h>


#include <Auto_Serial_Speed.h>


Auto_Serial_Speed Speed_Test(1);



void setup() {
  Serial.begin(115200);
  Serial.println("Doot - Speed Test");

  delay(5000);
  Serial.println("After dalay");


  Serial.println("Master");
  Speed_Test.Test_Speed_Master();

  // Serial.println("Slave");
  // Speed_Test.Test_Speed_Slave();


  Serial.println("Doot Done - Speed Test");

} // setup


void loop() {

  Serial.println("loop");

  delay(2500);




} // loop
