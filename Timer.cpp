#include "Timer.h"

Timer::Timer() {
}

void Timer::setTimeReference() {
  timestamp_reference = millis();
}

//**
bool Timer::waitTime_ms(int time_ms) {
  unsigned long timestamp_now = millis();
  if (timestamp_now - timestamp_reference >= time_ms) {
    return true;
  }
  return false;
}
