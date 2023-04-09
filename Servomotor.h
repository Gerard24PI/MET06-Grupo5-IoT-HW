#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H

#include <Arduino.h>
#include <Servo.h>

class Servomotor {
  public:
    Servomotor();
    Servomotor(int pin);
    void moveServomotor(int degrees);
  private:
    int pin;
    Servo motor;
};

#endif