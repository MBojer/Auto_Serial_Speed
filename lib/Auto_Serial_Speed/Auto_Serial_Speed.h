

// --------------------------------------------- Auto_Serial_Speed ---------------------------------------------
#ifndef Auto_Serial_Speed_h
  #define Auto_Serial_Speed_h


  #include "Arduino.h"

  class Auto_Serial_Speed {

    public:
      // --------------------------------------------- Auto_Serial_Speed ---------------------------------------------
      byte Test_Speed_Master(HardwareSerial &Serial_Port);
      byte Test_Speed_Slave(HardwareSerial &Serial_Port);

      bool Boot_Check(bool Mater);

      bool Serial_Read_Match(String Match_String);


      bool Handshake_Master(); // Master
      bool Handshake_Slave(); // Slave

      #define Handshake_Loop_Delay 200
      #define Handshake_Loop_Count 50

      #define Handshake_1 "Hello"
      #define Handshake_2 "World"


      unsigned long Speed_Step(byte Step);

      unsigned long Serial_Speed;

      unsigned long Selected_Speed;



    private:
      // --------------------------------------------- private ---------------------------------------------
      byte _Serial_Port;

      byte _Check_Stats = 1;







  };

#endif
