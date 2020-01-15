#include "HX711.h"
#include <MIDI_Controller.h>                                 // Include MIDI controller library
#define HAIRLESS_BAUD 1152200

HairlessMIDI_Interface HairlessMIDI;                         // Class pour logiciel Hairless ( link ableton/Arduino )

// HX711 = controle du poid sur la balance
const int LOADCELL_DOUT_PIN = 6;
const int LOADCELL_SCK_PIN = 5;
HX711 scale;

int loadcellval;                                                  // Valeur de la balance
int midival = 0;                                                  // Valeur MIDI
int v0_ = 0;                                                      // Valeur de Controle ( ancienne valeur )

int threshold = 2;                                                // Valeur de difference lors du controle

// Plutôt que d'utiliser les classes Analog ou Digital,
// on recrée une classe BalanceController qui envoie ce qu'il faut au MIDI
class BalanceController : public MIDI_Control_Element
{
  public:
    explicit BalanceController( uint8_t );
    void setValue( uint8_t );
  private:
    void refresh(); // méthode qui surcharge ce qui doit être envoyé au MIDI, appelé par MIDI_Controller.refresh();

  public:
    uint8_t value_;
};

BalanceController::BalanceController( uint8_t value )
  : value_( value )
{
};

void BalanceController::setValue( uint8_t value )
{
  value_ = value;
};

void BalanceController::refresh()
{
  uint8_t channelOffset = 0;
  uint8_t addressOffset = 0;
  uint8_t channelsPerBank = 1;

  MIDI_Controller.MIDI()->send(CC,
                               4 + channelOffset * channelsPerBank,
                               MIDI_CC::Channel_Volume + addressOffset * channelsPerBank,
                               value_
                              ); // send a Control Change MIDI event
};

BalanceController maBalance( 0 );

void setup() {
   //Serial.begin(115200);                                          //Port de sortie pour controle de data des balances
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);                // Connectiques de la balance
}

void loop() {
  //   Serial.println(nCounter)
  // myBase.setValue ( (uint8_t) constrain( nCounter, 0, 127 ) );

  if (scale.is_ready()) {                                          // Demarrage de lecture de la balance
    long loadcellval = scale.read() ;                      // Tare manuel de la balance
    //Channel 1
    //loadcellval = map(loadcellval, 255000, 300000, 0, 127);        // Map pour valeur MIDI entre 0 - 127
    //Chanel 2
    //loadcellval = map(loadcellval, 300000, 500000, 0, 127);
    //Channel 3
    //loadcellval = map(loadcellval, 260000, 430000, 0, 127);
    //Channel 4
    loadcellval = map(loadcellval, 550000, 750000, 0, 127);
    loadcellval = constrain(loadcellval, 0, 127);                  // Garder la valeur entre 0 - 127
    midival = loadcellval;                                         //
    //Serial.print("v1: "); Serial.println(loadcellval);           // Controle qualité de valeur
  }

  if (midival - v0_ >= threshold || v0_ - midival >= threshold) {  // Controle de changment de valeur
    v0_ = midival;                                                 // Si la valeur change alors, elle peut etre envoyé en commande
    //Serial.println(v0_);                                         // Controle de valeur en mise jour
    uint8_t value = (uint8_t) midival;
    maBalance.setValue( value );
    MIDI_Controller.refresh();
  }

  //delay( 100 ); // délai d'1sec
}
