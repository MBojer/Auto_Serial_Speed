

// --------------------------------------------- Auto_Serial_Speed ---------------------------------------------
#ifndef Auto_Serial_Speed_h
  #define Auto_Serial_Speed_h

  #include "Arduino.h"

  class Auto_Serial_Speed {

    public:
      // --------------------------------------------- Setup ---------------------------------------------
      Auto_Serial_Speed(byte Serial_Port);


      // --------------------------------------------- Auto_Serial_Speed ---------------------------------------------
      byte Test_Speed_Master(byte Serial_Port);
      byte Test_Speed_Slave(byte Serial_Port);

      unsigned long Speed_Step(byte Step);



    private:
      // --------------------------------------------- private ---------------------------------------------
      byte _Serial_Port;

      byte _Check_Done_S1 = -1;
      byte _Check_Done_S2 = -1;
      byte _Check_Done_S3 = -1;



  };

#endif
