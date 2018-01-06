

// --------------------------------------------- Auto_Serial_Speed ---------------------------------------------
#include "Arduino.h"
#include "Auto_Serial_Speed.h"


// --------------------------------------------- Setup ---------------------------------------------
Auto_Serial_Speed::Auto_Serial_Speed(byte Serial_Port) {

  _Serial_Port = Serial_Port;

} // Auto_Serial_Speed


// --------------------------------------------- Test_Speed_Master ---------------------------------------------
byte Auto_Serial_Speed::Test_Speed_Master(byte Serial_Port) {

  if (_Check_Done != 1) return _Check_Done; // Check already done

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

  if (_Check_Done != 1) return _Check_Done; // Check already done


  if (Serial_Port == 1) {

    for (byte i = 1; i < 13; i++) {

      Serial1.begin(Speed_Step(i));

      for (byte ii = 0; ii == 255; ii++) { // Wait for date or else timeout

        if (Serial1.available()) break;

        else if (ii == 254) {
          Serial.print("No responce on serial at speed: "); // rm
          Serial.println(Speed_Step(i)); // rm
          return 2; // change me
        }

        delay(25);

      } // for


      while (Serial1.available()) { // Read data
        c = (char)Serial.read();
        Read_String += c;
      } // while


      if (Read_String != Speed_Test_String) {
        Serial.println("Read_String != Speed_Test_String"); // rm

        delay(10000); // rm
        return 2; // change me
      } // if



      Serial.println("END MARKER - for (byte i = 1; i < 13; i++)"); // rm
      delay(10000); // rm
      return 2; // change me


    } // for (byte i = 1; i < 13; i++)



  } // if (Serial_Port == 1)






  return -1;




} // Test_Speed_Slave


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
