#include <MIDI_Controller.h> // Include MIDI controller library
#define HAIRLESS_BAUD 1152200
#include "HX711.h"  // Library needed to communicate with HX711 https://github.com/bogde/HX711

#define DOUT  6  // Arduino pin 6 connect to HX711 DOUT
#define CLK  5  //  Arduino pin 5 connect to HX711 CLK
const int LOADCELL_DOUT_PIN = 6;
const int LOADCELL_SCK_PIN = 5;
HX711 scale;// Init of library

int v0 = 0;
int v0_ = 0;
int v1 = 0;
int v1_ = 0;
int threshold = 2;
int int_to_midi_ratio = 1024 / 128;
void SendMidiToSerial (unsigned char word0, unsigned char word1, unsigned char word2) {
  Serial.write(word0);
  Serial.write(word1);
  Serial.write(word2);
}

void setup () {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}
void loop () {
  
  long reading = scale.read() - 100000 - 14000;
  int range = map(reading, 250000, 400000, 3, 127);
  v0 = range;
  //Serial.println(v0);
  //v1 = analogRead(1) / int_to_midi_ratio;
  
 if (v0 - v0_ >= threshold || v0_ - v0 >= threshold) {
    v0_ = v0;
    SendMidiToSerial(176, 42, v0);
  }
  /*
  if (v1 - v1_ >= threshold || v1_ - v1 >= threshold) {
    v1_ = v1;
    SendMidiToSerial(176, 43, v1);
    
  }*/
}
