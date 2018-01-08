

// --------------------------------------------- Auto_Serial_Speed ---------------------------------------------
#ifndef Auto_Serial_Speed_h
  #define Auto_Serial_Speed_h

  #define Boot_Ping "1337"
  #define Boot_Retries 120 // This controls how long the master looks for the slave, it will be Boot_Retries * 250ms

  #define Handshake_rx "Hello"
  #define Handshake_tx "World"




  #include "Arduino.h"

  class Auto_Serial_Speed {

    public:
      // --------------------------------------------- Setup ---------------------------------------------
      Auto_Serial_Speed(byte Serial_Port);


      // --------------------------------------------- Auto_Serial_Speed ---------------------------------------------
      byte Test_Speed_Master();
      byte Test_Speed_Slave();

      void Test_Speed(byte Step_Nr);

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



    private:
      // --------------------------------------------- private ---------------------------------------------
      byte _Serial_Port;

      byte _Check_Stats = 1;







  };

#endif
