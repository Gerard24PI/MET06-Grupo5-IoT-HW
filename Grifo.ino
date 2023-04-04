#include "Button.h"
#include "LED.h"
#include "Servomotor.h"


//Grifo pins
#define PIN_GRIFO_SERVOMOTOR      15    //D8
#define PIN_GRIFO_MODEBUTTON      14    //D5
#define PIN_GRIFO_EMERGENCYBUTTON 12    //D5
#define PIN_GRIFO_LED             4     //D2

//Grifo modes
#define MODE_TANCAT     0
#define MODE_SEMIOBERT  1
#define MODE_OBERT      2
#define N_MODES         3

//Grifo position modes
#define POS_TANCAT    0
#define POS_SEMIOBERT 90
#define POS_OBERT     180


Button grifoModeButton;
Button grifoEmergencyButton;
Servomotor grifoServomotor;
LED grifoLed;
char grifoMode;

void setupGrifo() {
  grifoModeButton = Button(PIN_GRIFO_MODEBUTTON);
  grifoEmergencyButton = Button(PIN_GRIFO_EMERGENCYBUTTON);
  grifoLed = LED(PIN_GRIFO_LED);
  grifoServomotor = Servomotor(PIN_GRIFO_SERVOMOTOR);

  
  grifoMode = MODE_TANCAT;
  update_mode(grifoMode);
}

void grifo() {
  /**Cooperative Loop Logic**/
  grifoModeButton.button_routine();
  grifoEmergencyButton.button_routine();
  grifoLed.updateLED_routine();
  /**************************/

  if (grifoModeButton.isPressed()) {
    change_mode();
  }

  if (grifoEmergencyButton.isPressed()) {
    update_mode(MODE_TANCAT);
  }
}


void change_mode() {
  grifoMode = (grifoMode+1) % N_MODES;
  update_mode(grifoMode);
}

void update_mode(char mode) {
  int degrees = POS_TANCAT;
  int brightness = LOW_BRIGHTNESS;
  switch(mode) {
    case MODE_SEMIOBERT:
      degrees = POS_SEMIOBERT;
      brightness = MED_BRIGHTNESS;
      break;
    case MODE_OBERT:
      degrees = POS_OBERT;
      brightness = HIGH_BRIGHTNESS;
      break;
    case MODE_TANCAT:
      degrees = POS_TANCAT;
      brightness = LOW_BRIGHTNESS;
      break;
  }
  grifoServomotor.moveServomotor(degrees);
  grifoLed.setBrightness(brightness);
  //Serial.print("Mode: ");
  //Serial.println(mode,DEC);
}