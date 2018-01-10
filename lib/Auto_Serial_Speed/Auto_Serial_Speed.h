

// --------------------------------------------- Auto_Serial_Speed ---------------------------------------------
#ifndef Auto_Serial_Speed_h
  #define Auto_Serial_Speed_h


  #include "Arduino.h"

  class Auto_Serial_Speed {

    public:
      // --------------------------------------------- Setup ---------------------------------------------
      Auto_Serial_Speed();


      // --------------------------------------------- Auto_Serial_Speed ---------------------------------------------
      byte Test_Speed_Master(HardwareSerial &Serial_Port_Ref);
      byte Test_Speed_Slave(HardwareSerial &Serial_Port_Ref);


      unsigned long Speed_Step(byte Step);


    private:
      // --------------------------------------------- private ---------------------------------------------
      bool Boot_Check(bool Mater);

      bool Serial_Read_Match(String Match_String, HardwareSerial &Serial_Port_Ref);


      bool Handshake_Master(HardwareSerial &Serial_Port_Ref); // Master
      bool Handshake_Slave(HardwareSerial &Serial_Port_Ref); // Slave
      #define Last_Speed_To_Test 10

      #define Handshake_Loop_Delay 200
      #define Handshake_Loop_Count 50

      #define Handshake_1 "Hello"
      #define Handshake_2 "World"







  };

#endif
