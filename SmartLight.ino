#include "Button.h"
#include "LED.h"
#include "AnalogSensor.h"


//Smart Light modes
#define SLIGHT_MODE_RANGE_LOW       0
#define SLIGHT_MODE_RANGE_MED       1
#define SLIGHT_MODE_RANGE_HIGH      2
#define SLIGHT_MODE_RANGE_COMPLETE  3
#define SLIGHT_N_MODES              4

typedef struct {
  char min;
  char max;
} BrightnessRange;
char sLightMode;

int global_brightness = 0;

// Sensor & Actuator Objects
BrightnessRange brightnessRange;
Button sLightModeButton;
LED sLightLed;
AnalogSensor sLightAnalogSensor;


void lightCallback(StreamData data)
{
  Serial.print("Light Updated from FB: ");
  printResult(data);
  global_brightness = data.to<int>();
  
}


void setupSmartLight() {
  sLightModeButton = Button(PIN_MODE_BUTTON);
  sLightLed = LED(PIN_AUX_LED);
  sLightAnalogSensor = AnalogSensor(PIN_ANALOG_INPUT);
  
  sLightMode = SLIGHT_MODE_RANGE_COMPLETE;
  sLight_update_mode(sLightMode);
}

void smartLight() {
  /**Cooperative Loop Logic**/
  sLightModeButton.button_routine();
  sLightLed.updateLED_routine();
  /**************************/

  if (sLightModeButton.isPressed()) {
    sLight_change_mode();

    // Update light value in Firebase
    int analogValPct = sLightAnalogSensor.getAnalogValuePct();
    setLightToFB(getBrightnessAcordingRange(analogValPct));
  }

  if(LIGHT_SENSOR_OVERRIDE_POT){
    // Firebase value will be used
    sLightLed.setBrightness(global_brightness);
  }else{
    //Cada X temps, es consulta valor Analògic i s'actualitza brightness segons valor analogic i el rang de brillantor permes en aquell mode
    if (sLightAnalogSensor.analogAvailable()) {
      int analogValPct = sLightAnalogSensor.getAnalogValuePct();
      int brightness = getBrightnessAcordingRange(analogValPct);
      sLightLed.setBrightness(brightness);
    } 

  }
}

//Extreu el valor de brightness dintre del rang especificat segons el percentatge
int getBrightnessAcordingRange(int pct) {
  return ((brightnessRange.max - brightnessRange.min)*pct)/100 + brightnessRange.min;
}

void sLight_change_mode() {
  sLightMode = (sLightMode+1) % SLIGHT_N_MODES;
  sLight_update_mode(sLightMode);
}

void sLight_update_mode(char mode) {
  BrightnessRange br_aux;
  br_aux.min = MIN_BRIGHTNESS;
  br_aux.max = MAX_BRIGHTNESS;
  switch(mode) {
    case SLIGHT_MODE_RANGE_LOW:
      br_aux.min = MIN_BRIGHTNESS;
      br_aux.max = trunc(MAX_BRIGHTNESS/(SLIGHT_N_MODES-1));
      break;
    case SLIGHT_MODE_RANGE_MED:
      br_aux.min = trunc(MAX_BRIGHTNESS/(SLIGHT_N_MODES-1));
      br_aux.max = trunc(2*(MAX_BRIGHTNESS/(SLIGHT_N_MODES-1)));
      break;
    case SLIGHT_MODE_RANGE_HIGH:
      br_aux.min = trunc(2*(MAX_BRIGHTNESS/(SLIGHT_N_MODES-1)));
      br_aux.max = MAX_BRIGHTNESS;
      break;
    case SLIGHT_MODE_RANGE_COMPLETE:
      br_aux.min = MIN_BRIGHTNESS;
      br_aux.max = MAX_BRIGHTNESS;
      break;
  }
  brightnessRange = br_aux;
  //sLightLed.setBrightness(brightness);

  Serial.print("\nMode actualitzat a ");
  Serial.println(sLightMode,DEC);
}