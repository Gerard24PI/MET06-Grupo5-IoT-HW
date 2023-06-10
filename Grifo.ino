#include "Button.h"
#include "LED.h"
#include "Servomotor.h"


// Grifo modes
#define GRIFO_MODE_TANCAT     0
#define GRIFO_MODE_SEMIOBERT  1
#define GRIFO_MODE_OBERT      2
#define GRIFO_N_MODES         3


//Grifo modes degreess mapping
#define GRIFO_POS_TANCAT    0
#define GRIFO_POS_SEMIOBERT 30
#define GRIFO_POS_OBERT     120

// Sensor & Actuator objects
Button grifoModeButton;
Button grifoEmergencyButton;
Servomotor grifoServomotor;
LED grifoLed;


char grifoMode;


void servoCallback(StreamData data)
{
  Serial.print("Servo Updated from FB: ");
  printResult(data);
  switch(data.to<int>()){
    case 0:
      grifo_update_mode(GRIFO_MODE_TANCAT);
      break;
    case 90:
      grifo_update_mode(GRIFO_MODE_SEMIOBERT);
      break;
    case 180:
      grifo_update_mode(GRIFO_MODE_OBERT);
      break;
    default:
      break;
  }
    
}


void setupGrifo() {
  grifoModeButton = Button(PIN_MODE_BUTTON);
  grifoEmergencyButton = Button(PIN_ALARM_BUTTON);
  grifoLed = LED(PIN_AUX_LED);
  grifoServomotor = Servomotor(PIN_SERVO);

  
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
      setServoToFB(90);
      break;
    case GRIFO_MODE_OBERT:
      degrees = GRIFO_POS_OBERT;
      brightness = HIGH_BRIGHTNESS;
      setServoToFB(180);
      break;
    case GRIFO_MODE_TANCAT:
      degrees = GRIFO_POS_TANCAT;
      brightness = LOW_BRIGHTNESS;
      setServoToFB(0);
      break;
  }
  grifoServomotor.moveServomotor(degrees);

  grifoLed.setBrightness(brightness);

  if(DEBUG_GRIFO){
    Serial.print("\nMode actualitzat a ");
    Serial.println(grifoMode,DEC);
    Serial.print("\tDegrees: ");
    Serial.println(degrees,DEC);
    Serial.print("\tBness: ");
    Serial.println(grifoLed.getBrightness(),DEC);
  }
  
}