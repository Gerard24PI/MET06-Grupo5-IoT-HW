#include "Button.h"

Button::Button() {
}

Button::Button(int pin) {
  this->pin = pin;
  pinMode(pin, INPUT_PULLUP);
  this->button_state = 0;
  this->rebound_time_ms = BUTTON_REBOUND_MS;
  this->status = false;
  this->button_timer = Timer();
}

void Button::setReboundTime(int time_ms) {
  this->rebound_time_ms = time_ms;
}

bool Button::isPressed() {
  if (status) {
    status = false;
    return true;
  }
  return false;
}

void Button::button_routine() {
  switch(button_state) {
    //Espera pulsació
    case 0:
      if (buttonConsult()) {
        button_timer.setTimeReference();
        button_state++;
      }
      break;
    //Espera rebots pulsació
    case 1:
      if (esperaRebots()) {
        if (buttonConsult()) {
          if (DEBUG_BUTTONS){
            Serial.println("\nButton pressed");
          }
          
          status = true;
          button_state++;
        }
        else {
          button_state--;
        }
      }
      break;
    //Espera despulsació
    case 2:
      if (!buttonConsult()) {
        button_timer.setTimeReference();
        button_state++;
      }
      break;
    //Espera rebots despulsació
    case 3:
      if (esperaRebots()) {
        if (!buttonConsult()) {
          button_state = 0;
        }
        else {
          button_state--;
        }
      }
  }
}

bool Button::buttonConsult() {
  //Pull-Up interno
  if (digitalRead(pin) == LOW) {
    return true;
  }
  return false;
}

bool Button::esperaRebots() {
  return button_timer.waitTime_ms(rebound_time_ms);
}
