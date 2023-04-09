#ifndef PIR_SENSOR_H
#define PIR_SENSOR_H

#include <Arduino.h>
#include "LED.h"
#include "config.h"

class PIRSensor {
  private:
    int pinPirSensorBottom;
    int pinPirSensorTop;
    int pirState;
    unsigned long timestampFall;
    unsigned long timestampNow;
    bool presence_alarm;

  public:
    PIRSensor(int pinPirSensorBottom, int pinPirSensorTop);
    void setupPIR();
    void presenceRoutine();
    boolean isInTheRoom();
    boolean isInTheFloor();
    boolean readPresence(int pin);
    void pirTest();
    bool checkAlarmStatus();
};

#endif
