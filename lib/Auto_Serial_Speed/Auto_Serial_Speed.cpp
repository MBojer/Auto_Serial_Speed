

// --------------------------------------------- Auto_Serial_Speed ---------------------------------------------
#include "Arduino.h"
#include "Auto_Serial_Speed.h"


bool Auto_Serial_Speed::Serial_Read_Match(String Match_String) {

  if (Serial1.available() > 0)  {
    String Read_String;
    char c;

    while (Serial1.available()) {
      c = (char)Serial1.read();
      Read_String += c;
    } // while

    if (Read_String.indexOf(Match_String) != -1) {
      Serial.println("MATCH");
      return true;
    }
  } // if (Serial1.available() > 2)

  return false;

} // Serial_Read_Match(String Match_String)



bool Auto_Serial_Speed::Handshake_Master() {

  byte Send_Ignore = 4;

  for (byte i = 0; i < Handshake_Loop_Count; i++)
  {
    if (Send_Ignore == 0)
    {
      Serial.print("+"); // rm
      Serial1.println(Handshake_1); // rm
      Serial1.flush();
      Send_Ignore = 4;
    }
    if (Serial_Read_Match(Handshake_2) == true)
    {
      return true;
    }
    delay(Handshake_Loop_Delay);
    Send_Ignore--;
  }

  return false;
}


bool Auto_Serial_Speed::Handshake_Slave()
{
  for (byte i = 0; i < Handshake_Loop_Count; i++)
  {
    if (Serial_Read_Match(Handshake_1) == true)
    {
      Serial1.println(Handshake_2);
      Serial1.flush(); // flush to make sure the message gets send
      return true;
    }

    delay(Handshake_Loop_Delay);
  }

  return false;
}



// --------------------------------------------- Test_Speed_Master ---------------------------------------------
byte Auto_Serial_Speed::Test_Speed_Master(HardwareSerial &Serial_Port) {

  if (_Check_Stats != 1 && _Check_Stats != 2) return _Check_Stats; // Check already done

  if (_Serial_Port == 1) {

    // +++++++++++++++++++++++++++++++++++ Speed test +++++++++++++++++++++++++++++++++++
    for (byte i = 0; i < 8; i++)
    {
      Serial1.begin(Speed_Step(i));

      if (Handshake_Master() == false)
      {
        if (i == 0) { // First check failed
          _Check_Stats = 4; // 4 = Error - Port down
          return _Check_Stats;
        }
        else
        {
          Serial1.begin(Speed_Step(i - 1)); // Stepping one speed down

          if (Handshake_Master() == false)
          {
            _Check_Stats = 6; // 6 = Error - Handshake failed after stepping one speed down after failure
            return _Check_Stats;
          }
          else
          {
            Selected_Speed = Speed_Step(i - 1);
            _Check_Stats = 2; // 2 = done and ok
            return _Check_Stats;
          }
        } // else
      } // if (Handshake_Slave() == false)
    } // for (byte i = 0; i < 8; i++)
  } // _Serial_Port == 1


  Selected_Speed = Speed_Step(7);
  _Check_Stats = 2; // 2 = done and ok
  return _Check_Stats;

} // Test_Speed_Master


// --------------------------------------------- Test_Speed_Slave ---------------------------------------------
byte Auto_Serial_Speed::Test_Speed_Slave(HardwareSerial &Serial_Port) {

  if (_Check_Stats != 1 && _Check_Stats != 2) return _Check_Stats; // Check already done

  if (_Serial_Port == 1) {

    // +++++++++++++++++++++++++++++++++++ Speed test +++++++++++++++++++++++++++++++++++
    for (byte i = 0; i < 8; i++)
    {
      Serial_Port.begin(Speed_Step(i));

      Serial.println(i); // rm
      if (Handshake_Slave() == false)
      {
        if (i == 0) { // First check failed
          _Check_Stats = 4; // 4 = Error - Port down
          return _Check_Stats;
        }
        else
        {
          Serial1.begin(Speed_Step(i - 1)); // Stepping one speed down

          if (Handshake_Slave() == false)
          {
            _Check_Stats = 6; // 6 = Error - Handshake failed after stepping one speed down after failure
            return _Check_Stats;
          }
          else
          {
            Selected_Speed = Speed_Step(i - 1);
            _Check_Stats = 2; // 2 = done and ok
            return _Check_Stats;
          }
        } // else
      } // if (Handshake_Slave() == false)
    } // for (byte i = 0; i < 8; i++)
  } // _Serial_Port == 1


  Selected_Speed = Speed_Step(7);
  _Check_Stats = 2; // 2 = done and ok
  return _Check_Stats;

} // Test_Speed_Slave




unsigned long Auto_Serial_Speed::Speed_Step(byte Step) {

  Serial.print("Speed: "); // rm

  switch (Step) {

    case 0:
      Serial.println("4800"); // rm
      return 4800;

    case 1:
      Serial.println("9600"); // rm
      return 9600;

    case 2:
      Serial.println("14400"); // rm
      return 14400;

    case 3:
      Serial.println("19200"); // rm
      return 19200;

    case 4:
      Serial.println("28800"); // rm
      return 28800;

    case 5:
      Serial.println("38400"); // rm
      return 38400;

    case 6:
      Serial.println("57600"); // rm
      return 57600;

    case 7:
      Serial.println("115200"); // rm
      return 115200;

    default:
      Serial.println("115200"); // rm
      return 115200;

    } // Switch

} // Speed_Step
