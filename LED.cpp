#include "LED.h"


LED::LED() {
}

LED::LED(int pin) {
  this->pin = pin;
  pinMode(pin, OUTPUT);
  turnOff();
}

void LED::turnOn() {
  digitalWrite(pin, HIGH);
}

void LED::turnOff() {
  digitalWrite(pin, LOW);
}

void LED::test() {
  turnOn();
  delay(1000);
  turnOff();
  delay(1000);
}
