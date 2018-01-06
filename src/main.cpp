#include <Arduino.h>

#include <Auto_Serial_Speed.h>

#define Serial_Speed 115200

Auto_Serial_Speed STest(1);

String inputString = "";
char c;



int Loop_Counter = 1;

void setup() {
  Serial.begin(Serial_Speed);
  Serial.println("Doot done - tx queue");


  STest.Test_Speed_Master(1);

  while (!Serial1) {

    Serial.println("!Serial1");
    delay(250);

  }

  Serial.println("After");


  // while (Serial.available()) {
  //
  // c = (char)Serial.read();
  // inputString += c;
  // }
  //
  // if (inputString == "Ping") {
  //   Serial.println("Ok");
  //   Serial.flush();
  // }

} // setup


void loop() {



  // Serial1.write(Loop_Counter);
  //
  // Serial.print("tx: ");
  // Serial.println(Loop_Counter);
  //
  // Loop_Counter = Loop_Counter + 1;

  delay(1000);


} // loop
