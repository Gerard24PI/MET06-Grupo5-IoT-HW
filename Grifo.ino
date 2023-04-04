#include "Button.h"
#include "LED.h"
#include "Servomotor.h"


//Grifo pins
#define PIN_GRIFO_SERVOMOTOR      15    //D8
#define PIN_GRIFO_MODEBUTTON      14    //D5
#define PIN_GRIFO_EMERGENCYBUTTON 12    //D5
#define PIN_GRIFO_LED             4     //D2

//Grifo modes
#define GRIFO_MODE_TANCAT     0
#define GRIFO_MODE_SEMIOBERT  1
#define GRIFO_MODE_OBERT      2
#define GRIFO_N_MODES         3

//Grifo position modes
#define GRIFO_POS_TANCAT    0
#define GRIFO_POS_SEMIOBERT 90
#define GRIFO_POS_OBERT     180


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

  
  grifoMode = GRIFO_MODE_TANCAT;
  grifo_update_mode(grifoMode);
}

void grifo() {
  /**Cooperative Loop Logic**/
  grifoModeButton.button_routine();
  grifoEmergencyButton.button_routine();
  grifoLed.updateLED_routine();
  /**************************/

  if (grifoModeButton.isPressed()) {
    grifo_change_mode();
  }

  if (grifoEmergencyButton.isPressed()) {
    grifo_update_mode(GRIFO_MODE_TANCAT);
  }

}


void grifo_change_mode() {
  grifoMode = (grifoMode+1) % GRIFO_N_MODES;
  grifo_update_mode(grifoMode);
}

void grifo_update_mode(char mode) {
  int degrees = GRIFO_POS_TANCAT;
  int brightness = LOW_BRIGHTNESS;
  switch(mode) {
    case GRIFO_MODE_SEMIOBERT:
      degrees = GRIFO_POS_SEMIOBERT;
      brightness = MED_BRIGHTNESS;
      break;
    case GRIFO_MODE_OBERT:
      degrees = GRIFO_POS_OBERT;
      brightness = HIGH_BRIGHTNESS;
      break;
    case GRIFO_MODE_TANCAT:
      degrees = GRIFO_POS_TANCAT;
      brightness = LOW_BRIGHTNESS;
      break;
  }
  grifoServomotor.moveServomotor(degrees);
  grifoLed.setBrightness(brightness);

  Serial.print("\nMode actualitzat a ");
  Serial.println(grifoMode,DEC);
  Serial.print("\tDegrees: ");
  Serial.println(degrees,DEC);
  Serial.print("\tBness: ");
  Serial.println(grifoLed.getBrightness(),DEC);
}