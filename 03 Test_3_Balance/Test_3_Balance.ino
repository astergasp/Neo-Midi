#include "HX711.h"  // Library needed to communicate with HX711 https://github.com/bogde/HX711

#define DOUT  6  // Arduino pin 6 connect to HX711 DOUT
#define CLK  5  //  Arduino pin 5 connect to HX711 CLK

//const int LOADCELL_DOUT_PIN = 6; // Blue
//const int LOADCELL_SCK_PIN = 5;
const int LOADCELL_DOUT_PIN = 36;
const int LOADCELL_SCK_PIN = 34;
HX711 scale;// Init of library

//byte volumecontrol = OxB
int data1 = 2;


void setup() {
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

}

void loop() {
  long reading = scale.read() - 100000 - 14000;
  int range = map(reading, 0, 600000, 5, 127);
  byte vol = range;
  Serial.println (range);
//  MIDImessage(volumecontrol, 

}

//send MIDI message
void MIDImessage(byte command, byte data1, byte data2) {
  Serial.write(command);
  Serial.write(data1);
  Serial.write(data2);
}
