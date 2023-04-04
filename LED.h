#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "Timer.h"

#define MIN_BRIGHTNESS  0
#define LOW_BRIGHTNESS  25
#define MED_BRIGHTNESS  50
#define HIGH_BRIGHTNESS 75
#define MAX_BRIGHTNESS  100

#define LED_PERIOD_MS 20

class LED {
public:
  LED();
  LED(int pin);
  void turnOn();
  void turnOff();
  void test();
  
  void setBrightness(int brightness);
  int getBrightness();
  void setLedPeriod(int period);
  void updateLED_routine();

private:
  int pin;
  int led_state;
  int led_period_ms;
  int led_high_ms;
  int brightness_pct;
  Timer led_timer;
  int getMsFromBrightnessPct();
};

#endif
