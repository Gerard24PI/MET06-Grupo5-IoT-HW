#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

class Timer {
  public:
    void setTimeReference();
    bool waitTime_ms(int time_ms);
  private:
    unsigned long timestamp_reference;
};

#endif