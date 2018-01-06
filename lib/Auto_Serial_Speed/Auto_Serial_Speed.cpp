

// --------------------------------------------- Auto_Serial_Speed ---------------------------------------------
#include "Arduino.h"
#include "Auto_Serial_Speed.h"

#define _Port_Speed_Multiplyer 300


// --------------------------------------------- Setup ---------------------------------------------
Auto_Serial_Speed::Auto_Serial_Speed(byte Serial_Port) {

  _Serial_Port = Serial_Port;

} // Auto_Serial_Speed


// --------------------------------------------- Test_Speed ---------------------------------------------
byte Auto_Serial_Speed::Test_Speed_Master(byte Serial_Port) {

  if (_Check_Done_S1 != 1 && Serial_Port == 1) return _Check_Done_S1; // Check already done
  if (_Check_Done_S2 != 1 && Serial_Port == 2) return _Check_Done_S2; // Check already done
  if (_Check_Done_S3 != 1 && Serial_Port == 3) return _Check_Done_S3; // Check already done

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




} // Test_Speed


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
