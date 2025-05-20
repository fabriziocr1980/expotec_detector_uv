#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// Use pins 2 and 3 to communicate with DFPlayer Mini
static const uint8_t PIN_MP3_TX = 9; // D7
static const uint8_t PIN_MP3_RX = 8; // D6
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

// Create the Player object
DFRobotDFPlayerMini player;

void setup() 
{
  Serial.begin(9600);
  softwareSerial.begin(9600);
  if (player.begin(softwareSerial)) 
  {
   Serial.println("OK");

    // Set volume to maximum (0 to 30).
    player.volume(22); //30 is very loud
  } 
  else 
  {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }
}

void loop() 
{
  Serial.print("Playing #1 \t");
  player.play(1);
  delay(30000);

}
