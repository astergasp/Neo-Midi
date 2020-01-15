#include "HX711.h" // Include Load cells library
#include <MIDI_Controller.h> // Include MIDI controller library
#define HAIRLESS_BAUD 1152200

HairlessMIDI_Interface HairlessMIDI;


// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

HX711 scale;

int LC0;
int v1 = LC0;
int v2 = A1;

//__________________________________________________________________________________________________________________________

const uint8_t velocity = 0b01111111; // The velocity of the buttons (0b01111111 = 127 = 100%)
const unsigned int latchTime = 100;  // How long a note will be held on, in DigitalLatch mode (in milliseconds).

const int speedMultiply = 1; // If the jog wheels or other encoders are too slow in your software, increase this value
// (it will be multiplied with the actual speed of the encoder, as the name implies.) Default is 1.

// Create a new instance of the class 'Analog', called 'Load cell', on value of load cell,
// that sends MIDI messages with controller 7 (channel volume) on channel 1
Analog loadcell[] = {
  {v1, MIDI_CC::Channel_Volume, 1},
  //{v2, MIDI_CC::Channel_Volume, 2},
  //{v3, MIDI_CC::Channel_Volume, 3},
  //{v4, MIDI_CC::Channel_Volume, 4},
  //{v5, MIDI_CC::Channel_Volume, 5},
};

Bank bank(5); // A bank with four channels

BankSelector bankselector(bank, 11, LED_BUILTIN, BankSelector::TOGGLE); // A bank selector with a single toggle switch on pin 11 and an LED for feedback on pin 13


void setup() {
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  bank.add(loadcell, Bank::CHANGE_CHANNEL); // Add the control elements to the bank

}

void loop() {
  // Refresh the MIDI controller (check whether the potentiometer's input has changed since last time, if so, send the new value over MIDI)
  long reading = scale.read() - 100000 - 14000;
  int range = map(reading, 250000, 400000, 3, 127);
  LC0 = range;
  MIDI_Controller.refresh();
  delay (500);
}
