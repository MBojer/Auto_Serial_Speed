

// --------------------------------------------- Auto_Serial_Speed ---------------------------------------------
#ifndef Auto_Serial_Speed_h
  #define Auto_Serial_Speed_h

  #define Test_Not_Done 1
  #define Test_Done 2
  #define Speed_Test_String "HelloWorld123"


  #include "Arduino.h"

  class Auto_Serial_Speed {

    public:
      // --------------------------------------------- Setup ---------------------------------------------
      Auto_Serial_Speed(byte Serial_Port);


      // --------------------------------------------- Auto_Serial_Speed ---------------------------------------------
      byte Test_Speed_Master(byte Serial_Port);
      byte Test_Speed_Slave(byte Serial_Port);

      void Test_Speed(byte Step_Nr);


      unsigned long Speed_Step(byte Step);

      unsigned long Serial_Speed;



    private:
      // --------------------------------------------- private ---------------------------------------------
      byte _Serial_Port;

      byte _Check_Stats = 1;


      String Read_String = "";
      char c;



  };

#endif
