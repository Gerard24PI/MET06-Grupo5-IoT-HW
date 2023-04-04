#include "LED.h"


LED::LED() {
}

LED::LED(int pin) {
  this->pin = pin;
  pinMode(pin, OUTPUT);
  this->led_period_ms = LED_PERIOD_MS;
  turnOff();
  this->led_state = 0;
  led_timer = Timer();
}

void LED::turnOn() {
  digitalWrite(pin, HIGH);
  this->brightness_pct = 100;
  this->led_period_ms = getMsFromBrightnessPct();
}

void LED::turnOff() {
  digitalWrite(pin, LOW);
  this->brightness_pct = 0;
  this->led_period_ms = getMsFromBrightnessPct();
}

/**
 * 0 <= brightness <= 100
**/
void LED::setBrightness(int brightness) {
  this->brightness_pct = brightness;
}

int LED::getBrightness() {
  return brightness_pct;
}

void LED::setLedPeriod(int period) {
  this->led_period_ms = period;
}

void LED::updateLED_routine() {

}

void LED::test() {
  turnOn();
  delay(1000);
  turnOff();
  delay(1000);
}


int LED::getMsFromBrightnessPct() {
  return trunc((brightness_pct/100)*led_period_ms);
}
