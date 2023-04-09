#include "AnalogSensor.h"



AnalogSensor::AnalogSensor() {
}
AnalogSensor::AnalogSensor(int pin) {
  this->pin = pin;
  this->checkAnalogTime = CHECK_ADC_TIME_MS;
  this->analogTimer = Timer();
}

bool AnalogSensor::analogAvailable() {
  return analogTimer.waitTime_ms(checkAnalogTime);
}

int AnalogSensor::getAnalogValuePct() {
  int adcValue = getAnalogValue();
  return trunc((adcValue*100)/1024);
}

int AnalogSensor::getAnalogValue() {
  return analogRead(pin);
}