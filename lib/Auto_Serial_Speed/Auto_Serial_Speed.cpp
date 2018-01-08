

// --------------------------------------------- Auto_Serial_Speed ---------------------------------------------
#include "Arduino.h"
#include "Auto_Serial_Speed.h"


// --------------------------------------------- Setup ---------------------------------------------
Auto_Serial_Speed::Auto_Serial_Speed(byte Serial_Port) {
  _Serial_Port = Serial_Port;
} // Auto_Serial_Speed


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

bool Auto_Serial_Speed::Boot_Check(bool Mater) {

  bool Send_Message;
  if (Mater == true) Send_Message = true;
  else Send_Message = false;

  for (byte i = 0; i < Boot_Retries; i++) // Waiting for reply
  {

    if (Send_Message == true) Serial.print("+"); // rm
    if (Send_Message == false) Serial.print("."); // rm

    if (Send_Message == true) Serial1.println(Boot_Ping);


    if (Serial_Read_Match(Boot_Ping) == true)
    {
      if (Mater == true)  // Master
      {
        if (Send_Message == true) Send_Message = false;
        else
        {
          Serial1.println(Boot_Ping);
          Serial1.println(Boot_Ping);
          return true;
        }
        delay(33);
      }

      else if (Mater == false)
      {
        if (Send_Message == false) Send_Message = true;
        else
        {
          Serial1.println(Boot_Ping);
          Serial1.println(Boot_Ping);
          return true;
        }
        delay(33);
      }



      while (Serial1.available() > 0) Serial1.read();
    }


    if (i == Boot_Retries - 1)// Timeout
    {
      _Check_Stats = 5;
      return false;
    }


    delay(250);

  } // for

  return false;
} // Boot_Check




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
      Serial.println("Handshake OK"); // rm
      return true;
    }
    delay(Handshake_Loop_Delay);
    Send_Ignore--;
  }

  Serial.println("Handshake FAILED"); // rm

  return false;
}


bool Auto_Serial_Speed::Handshake_Slave()
{
  for (byte i = 0; i < Handshake_Loop_Count; i++)
  {
    if (Serial_Read_Match(Handshake_1) == true)
    {
      Serial.println("Handshake OK"); // rm

      Serial1.println(Handshake_2);
      Serial1.flush(); // flush to make sure the message gets send
      return true;
    }

    delay(Handshake_Loop_Delay);
  }

  Serial.println("Handshake FAILED"); // rm

  return false;
}



// --------------------------------------------- Test_Speed_Master ---------------------------------------------
byte Auto_Serial_Speed::Test_Speed_Master() {

  if (_Check_Stats == 2) return _Check_Stats; // Check already done


  if (_Serial_Port == 1) {

    // +++++++++++++++++++++++++++++++++++ Boot test +++++++++++++++++++++++++++++++++++

    Serial1.begin(4800);

    if (Handshake_Master() == true) {
      Serial.println("Marker: Boot_Check(1) == true"); // rm
      return 1; // change me
    }

    Serial.println("Marker FALSE"); // rm

    // +++++++++++++++++++++++++++++++++++ Speed test +++++++++++++++++++++++++++++++++++

  } // _Serial_Port == 1





  return 1;

} // Test_Speed_Master


// --------------------------------------------- Test_Speed_Slave ---------------------------------------------
byte Auto_Serial_Speed::Test_Speed_Slave() {

  if (_Check_Stats == 2) return _Check_Stats; // Check already done


  if (_Serial_Port == 1) {


    // +++++++++++++++++++++++++++++++++++ Boot test +++++++++++++++++++++++++++++++++++
    Serial1.begin(4800);

    if (Handshake_Slave() == true) {
      Serial.println("Marker: Boot_Check(0) == true"); // rm
      return 1;
    }

    Serial.println("Marker FALSE"); // rm

    // +++++++++++++++++++++++++++++++++++ Speed test +++++++++++++++++++++++++++++++++++

  } // _Serial_Port == 1





  return 1;

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

  String Read_String = "";

  while (Serial1.available()) { // Read data
    char c = (char)Serial.read();
    Read_String += c;
  } // while


  int i = 1; // change me

  if (Read_String != Handshake_rx) {

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
