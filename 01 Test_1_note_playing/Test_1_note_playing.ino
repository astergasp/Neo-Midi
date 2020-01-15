
byte noteON = 144;//note on command 

void setup() {
  Serial.begin(9600);
}

void loop() {
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
