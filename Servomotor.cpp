#include "Servomotor.h"


Servomotor::Servomotor() {
}

Servomotor::Servomotor(int pin) {
  motor.attach(pin);
  moveServomotor(0);
}

void Servomotor::moveServomotor(int degrees) {
  motor.write(degrees);
}