
// --------------------------- SLAVE ---------------------------

#include <Arduino.h>

#define Speed_Test_String "HelloWorld123"

String Read_String = "";
char c;

String a;


void setup() {
  Serial.begin(115200);
  Serial.println("Doot - Speed Test - Slave");

  for ()

  while(Serial.available()) {

    a = Serial.readString();// read the incoming data as string
  }

  if (a != "") {

    Serial.println(a);
    a = "";
  }




  // while (true) {
  //
  //     while (Serial.available()) { // Read data
  //       c = (char)Serial.read();
  //       Read_String += c;
  //     } // while
  //
  //     if (Read_String != "") {
  //       if (Read_String == "Read_String") {
  //         Serial.println("Read_String == Read_String");
  //         break;
  //       }
  //
  //       else {
  //         Serial.println(Read_String);
  //         Read_String = "";
  //       }
  //
  //     }
  //
  //
  // }










  Serial.println("Doot Done - Speed Test - Slave");



} // setup


void loop() {

  Serial.println("loop");

  delay(5000);


} // loop
