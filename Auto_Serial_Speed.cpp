

#include "Arduino.h"
#include "Auto_Serial_Speed.h"

// --------------------------------------------- Setup ---------------------------------------------
Auto_Serial_Speed::Auto_Serial_Speed() {
} // Auto_Serial_Speed


// --------------------------------------------- Auto_Serial_Speed ---------------------------------------------
byte Auto_Serial_Speed::Test_Speed_Master(HardwareSerial &Serial_Port_Ref) {

  // +++++++++++++++++++++++++++++++++++ Speed test +++++++++++++++++++++++++++++++++++
  for (byte i = 0; i < Last_Speed_To_Test + 1; i++)
  {
    Serial_Port_Ref.begin(Speed_Step(i));

    if (Handshake_Master(Serial_Port_Ref) == false)
    {
      if (i == 0) { // First check failed
        return 90; // 90 = Error - Port down
      }
      else
      {
        Serial_Port_Ref.begin(Speed_Step(i - 1)); // Stepping one speed down

        if (Handshake_Master(Serial_Port_Ref) == false)
        {
          return 92; // 92 = Error - Handshake failed after stepping one speed down after failure
        }
        else
        {
          return i - 1; // Speed OK
        }
      } // else
    } // if (Handshake_Slave(Serial_Port_Ref) == false)
  } // for (byte i = 0; i < Last_Speed_To_Test + 1; i++)


  return Last_Speed_To_Test; // MAX Speed OK;

} // Test_Speed_Master

byte Auto_Serial_Speed::Test_Speed_Slave(HardwareSerial &Serial_Port_Ref) {

  // +++++++++++++++++++++++++++++++++++ Speed test +++++++++++++++++++++++++++++++++++
  for (byte i = 0; i < Last_Speed_To_Test + 1; i++)
  {
    Serial_Port_Ref.begin(Speed_Step(i));

    if (Handshake_Slave(Serial_Port_Ref) == false)
    {
      if (i == 0) { // First check failed
        return 90; // 90 = Error - Port down
      }
      else
      {
        Serial_Port_Ref.begin(Speed_Step(i - 1)); // Stepping one speed down

        if (Handshake_Slave(Serial_Port_Ref) == false)
        {
          return 92; // 92 = Error - Handshake failed after stepping one speed down after failure
        }
        else
        {
          return i - 1; // Speed OK
        }
      } // else
    } // if (Handshake_Slave(Serial_Port_Ref) == false)
  } // for (byte i = 0; i < Last_Speed_To_Test + 1; i++)

  return Last_Speed_To_Test; // MAX Speed OK;

} // Test_Speed_Slave


unsigned long Auto_Serial_Speed::Speed_Step(byte Step) {

  switch (Step) {

    case 0:
    return 4800;

    case 1:
    return 9600;

    case 2:
    return 14400;

    case 3:
    return 19200;

    case 4:
    return 28800;

    case 5:
    return 38400;

    case 6:
    return 57600;

    case 7:
    return 115200;

    case 8:
    return 230400;

    case 9:
    return 345600;

    case 10:
    return 500000;


    default:
    return 115200;

  } // Switch

} // Speed_Step

String Auto_Serial_Speed::Error_Text(byte Error_Number) {

  switch (Error_Number) {
    case 90:
    return "Port down";

    case 91:
    return "Unit present but not able to achive speed 9600";

    case 92:
    return "Handshake failed after stepping one speed down after failure";

    default:
    return "Unknown error number";
  }
}





// --------------------------------------------- private ---------------------------------------------
bool Auto_Serial_Speed::Handshake_Master(HardwareSerial &Serial_Port_Ref) {

  byte Send_Ignore = 4;

  for (byte i = 0; i < Handshake_Loop_Count; i++)
  {
    if (Send_Ignore == 0)
    {
      Serial_Port_Ref.println(Handshake_1);
      Serial_Port_Ref.flush();
      Send_Ignore = 4;
    }
    if (Serial_Read_Match(Handshake_2, Serial_Port_Ref) == true)
    {
      return true;
    }
    delay(Handshake_Loop_Delay);
    Send_Ignore--;
  }

  return false;
}

bool Auto_Serial_Speed::Handshake_Slave(HardwareSerial &Serial_Port_Ref) {
  for (byte i = 0; i < Handshake_Loop_Count; i++)
  {
    if (Serial_Read_Match(Handshake_1, Serial_Port_Ref) == true)
    {
      Serial_Port_Ref.println(Handshake_2);
      Serial_Port_Ref.flush(); // flush to make sure the message gets send
      return true;
    }

    delay(Handshake_Loop_Delay);
  }

  return false;
}

bool Auto_Serial_Speed::Serial_Read_Match(String Match_String, HardwareSerial &Serial_Port_Ref) {

  if (Serial_Port_Ref.available() > 0)  {
    String Read_String;
    char c;

    while (Serial_Port_Ref.available()) {
      c = (char)Serial_Port_Ref.read();
      Read_String += c;
    } // while

    if (Read_String.indexOf(Match_String) != -1) {
      return true;
    }
  } // if (Serial_Port_Ref.available() > 2)

  return false;

} // Serial_Read_Match(String Match_String)
