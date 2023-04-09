#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include "Timer.h"
#include "config.h"

#define BUTTON_REBOUND_MS 16

class Button {
  public:
    Button();
    Button(int pin);
    void setReboundTime(int time_ms);
    bool isPressed();
    void button_routine();
  private:
    int pin;
    int button_state;
    int rebound_time_ms;
    bool status;
    Timer button_timer;
    bool buttonConsult();
    bool esperaRebots();
};

#endif