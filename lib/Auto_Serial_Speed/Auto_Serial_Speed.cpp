

// --------------------------------------------- Auto_Serial_Speed ---------------------------------------------
#include "Arduino.h"
#include "Auto_Serial_Speed.h"


// --------------------------------------------- Setup ---------------------------------------------
Auto_Serial_Speed::Auto_Serial_Speed(byte Serial_Port) {

  _Serial_Port = Serial_Port;

} // Auto_Serial_Speed


// --------------------------------------------- Test_Speed_Master ---------------------------------------------
byte Auto_Serial_Speed::Test_Speed_Master(byte Serial_Port) {

  if (_Check_Stats != 1) return _Check_Stats; // Check already done

  else { // Check not done

    if (Serial_Port == 1) {

      for (byte i = 1; i < 13; i++) {

        Serial.print("Trying Serial Speed: "); // rm
        Serial.println(Speed_Step(i)); // rm

        // Serial1.begin(Speed_Step(i));



        /* code */
      }

    } // Serial_Port == 1


  } // else




  return -1;




} // Test_Speed_Master


// --------------------------------------------- Test_Speed_Slave ---------------------------------------------
byte Auto_Serial_Speed::Test_Speed_Slave(byte Serial_Port) {

  if (_Check_Stats != Test_Done) return _Check_Stats; // Check already done


  if (Serial_Port == 1) {

    for (byte i = 1; i < 13; i++) {




    } // for (byte i = 1; i < 13; i++)



  } // if (Serial_Port == 1)






  return -1;




} // Test_Speed_Slave


void Auto_Serial_Speed::Test_Speed(byte  Step_Nr) {

  Serial1.begin(Speed_Step(Step_Nr));




  for (byte i = 0; i == 255; i++) { // Wait for date or else timeout

    if (Serial1.available()) break;

    else if (i == 254) {
      Serial.print("No responce on serial at speed: "); // rm
      Serial.println(Speed_Step(Step_Nr)); // rm

      Serial_Speed = Speed_Step(i - 1);

      return; // change me
    }

    delay(25);

  } // for


  while (Serial1.available()) { // Read data
    c = (char)Serial.read();
    Read_String += c;
  } // while


  int i = 1; // change me

  if (Read_String != Speed_Test_String) {

    if (i == 1) { // Error - Port not up
      Serial.println("ERROR: Serial port not up"); // rm
      _Check_Stats = 4;
    }

    else { // Trying last speed
      _Check_Stats = 3;

      Serial.println("Read_String != Speed_Test_String"); // rm

      Serial.print("Read_String: "); // rm
      Serial.println(Read_String); // rm

      Serial.print("i: "); // rm
      Serial.println(i); // rm

      Serial_Speed = Speed_Step(i - 1);
    }


    return; // change me
  } // if



  Serial.println("END MARKER - for (byte i = 1; i < 13; i++)"); // rm
  delay(10000); // rm
  return; // change me
}


unsigned long Auto_Serial_Speed::Speed_Step(byte Step) {

  switch (Step) {

    case 1:
      return 300;

    case 2:
      return 600;

    case 3:
      return 1200;

    case 4:
      return 2400;

    case 5:
      return 4800;

    case 6:
      return 9600;

    case 7:
      return 14400;

    case 8:
      return 19200;

    case 9:
      return 28800;

    case 10:
      return 38400;

    case 11:
      return 57600;

    case 12:
      return 115200;

    default:
      return -1;

    } // Switch

} // Speed_Step
