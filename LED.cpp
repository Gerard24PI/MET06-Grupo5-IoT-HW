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
  this->brightness_pct = MAX_BRIGHTNESS;
  this->led_high_ms = getMsFromBrightnessPct();
}

void LED::turnOff() {
  digitalWrite(pin, LOW);
  this->brightness_pct = MIN_BRIGHTNESS;
  this->led_high_ms = getMsFromBrightnessPct();
}

/**
 * 0 <= brightness <= 100
**/
void LED::setBrightness(int brightness) {
  this->brightness_pct = brightness;
  this->led_high_ms = getMsFromBrightnessPct();
}

int LED::getBrightness() {
  return brightness_pct;
}

void LED::setLedPeriod(int period) {
  this->led_period_ms = period;
}

void LED::updateLED_routine() {
  switch(led_state) {
    case 0:
      //Espera temps a 0 (LOW)
      if (led_timer.waitTime_ms(led_period_ms-led_high_ms)) {
        turnOn();
        led_timer.setTimeReference();
        led_state++;
      }
      break;
    case 1:
      //Espera temps a 1 (HIGH)
      if (led_timer.waitTime_ms(led_high_ms)) {
        turnOff();
        led_timer.setTimeReference();
        led_state = 0;
      }
  }
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
