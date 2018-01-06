
// --------------------------- SLAVE ---------------------------

#include <Arduino.h>

#define Handshake_rx "Hello\r"
#define Handshake_tx "World\r"

bool CRC_Check() {

  Serial1.flush();

  bool Check_Failed_Once = false;

  // for (byte i = 0; i < 255; i++) {
  //
  //     if (Serial1.available() > 0)  {
  //
  //         String Read_String = Serial1.readStringUntil('\n');
  //
  //         if (Read_String == Speed_Test_String) { // Match
  //           Serial.println(); // rm
  //           Serial.println("HIT"); // rm
  //           return true;
  //         }
  //
  //         else { // Not a match
  //
  //           if (Check_Failed_Once == true) return false;
  //
  //           Serial.println(); // rm
  //           Serial.print("NOT a hit: "); // rm
  //           Serial.println(Read_String); // rm
  //           Check_Failed_Once = true;
  //           i--;
  //         }
  //
  //       }
  //
  //     delay(40); // 40 * 254 = a bit over 10 sec
  //     Serial.print("-"); // rm
  //
  // } // for (byte i = 0; i < 255; i++)

  for (byte i = 0; i < 255; i++) { // Handshake_rx

      if (Serial1.available() > 0)  {

          String Read_String = Serial1.readStringUntil('\n');

          if (Read_String == Handshake_rx) { // Match
            Serial.println(); // rm
            Serial.println("HIT - Sending Handshake_tx"); // rm

            Serial1.println(Handshake_tx);
            break;
          }

          else { // Not a match

            if (Check_Failed_Once == true) return false;

            Serial.println(); // rm
            Serial.print("NOT a hit: "); // rm
            Serial.println(Read_String); // rm
            Check_Failed_Once = true;
            i--;
          }

        }

      delay(40); // 40 * 254 = a bit over 10 sec
      Serial.print("-"); // rm

      if (i == 254) {
        Serial.println("end of for loop"); // rm
        return false;
      }

  } // for (byte i = 0; i < 255; i++)



  Check_Failed_Once = false;

  for (byte i = 0; i < 255; i++) { // Handshake_tx

    if (Serial1.available() > 2)  {

        String Read_String = Serial1.readStringUntil('\n');

        if (Read_String == Handshake_tx) { // Match
          Serial.println(); // rm
          Serial.println("HIT - Handshake OK"); // rm

          return true;
        }

        else { // Not a match

          if (Check_Failed_Once == true) return false;

          Serial.println(); // rm
          Serial.print("NOT a hit: "); // rm
          Serial.println(Read_String); // rm
          Check_Failed_Once = true;
          i--;
        }

      }

    delay(40); // 40 * 254 = a bit over 10 sec
    Serial.print("-"); // rm

  }


  Serial.println("After for loop 22"); // rm
  return false;
} // CRC_Check




void setup() {
  Serial.begin(115200);
  Serial.println("Doot - Speed Test - Slave 123");

  Serial1.begin(9600);

  for (byte i = 1; i < 13; i++) {

    delay(2500);

    if (CRC_Check() == false) {

      if (i == 1) { // Serial port not up
        Serial.println("Serial port not up"); // rm
        break; // Change me to an fetal error
      }


      else { // go back to last speed

        Serial.print("go back to last speed"); // rm
        break; // Change me

      } // else

    } // if (CRC_Check() == false)

    delay(150);

  }





  Serial.println("Doot Done - Speed Test - Slave");

} // setup


void loop() {






  delay(1000);




} // loop
