
#include "HX711.h"  // Library needed to communicate with HX711 https://github.com/bogde/HX711

#define DOUT  6  // Arduino pin 6 connect to HX711 DOUT
#define CLK  5  //  Arduino pin 5 connect to HX711 CLK

const int LOADCELL_DOUT_PIN = 6;
const int LOADCELL_SCK_PIN = 5;

//HX711 scale;// Init of library

byte noteON = 144;//note on command

void setup() {
  Serial.begin(9600);
  //scale.set_scale();
  //scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  //int mappedrange =  map(scale, 100000, 1500000, 0, 127);
  //scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

}

void loop() {
  //long reading = scale.read();

  //Serial.print("HX711 reading: ");
  //Serial.println(reading);
  //int note = map(scale.read(), 80000, 1500000, 0, 127);
  //Serial.println(note);
  MIDImessage(noteON, 80, 100);//turn note on
  delay(300);//hold note for 300ms
  MIDImessage(noteON, 80, 0);//turn note off (note on with velocity 0)
  delay(200);//wait 200ms until triggering next note
}

//send MIDI message
void MIDImessage(byte command, byte data1, byte data2) {
  Serial.write(command);
  Serial.write(data1);
  Serial.write(data2);
}
