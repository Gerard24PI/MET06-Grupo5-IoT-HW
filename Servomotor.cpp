#include "Servomotor.h"


Servomotor::Servomotor() {
}

Servomotor::Servomotor(int pin) {
  motor.attach(pin);
}

void Servomotor::moveServomotor(int degrees) {
  motor.write(degrees);
}