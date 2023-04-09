#ifndef ANALOGSENSOR_H
#define ANALOGSENSOR_H

#include <Arduino.h>
#include "Timer.h"

#define CHECK_ADC_TIME_MS 60

class AnalogSensor {
  public:
    AnalogSensor();
    AnalogSensor(int pin);
    bool analogAvailable();
    int getAnalogValuePct();
    int getAnalogValue();
  private:
    int pin;
    int checkAnalogTime;
    Timer analogTimer;

};

#endif