#ifndef LED_H
#define LED_H

#include <Arduino.h>

class LED {
public:
  LED();
  LED(int pin);
  void turnOn();
  void turnOff();
  void test();

private:
  int pin;
};

#endif
