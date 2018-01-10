#include <Arduino.h>


#include <Auto_Serial_Speed.h>

Auto_Serial_Speed Speed_Test;



void setup() {
  Serial.begin(115200);
  Serial.println("Doot - Speed Test");

  delay(5000);
  Serial.println("After dalay");


  Serial.println("Master");
  Serial.print("Serial 1: ");
  Serial.println(Speed_Test.Test_Speed_Master(Serial1));
  Serial.print("Serial 2: ");
  Serial.println(Speed_Test.Test_Speed_Master(Serial2));
  Serial.print("Serial 3: ");
  Serial.println(Speed_Test.Test_Speed_Master(Serial3));


  Serial.println("Doot Done - Speed Test");

} // setup


void loop() {

  Serial.println("loop");

  delay(2500);




} // loop
