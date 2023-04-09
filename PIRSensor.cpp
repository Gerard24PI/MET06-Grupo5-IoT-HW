#include "PIRSensor.h"

#define FALL_CHECK_TIME_MS 3000

PIRSensor::PIRSensor(int pinPirSensorBottom, int pinPirSensorTop) : pinPirSensorBottom(pinPirSensorBottom), pinPirSensorTop(pinPirSensorTop) {
  this->presence_alarm = false;
}

void PIRSensor::setupPIR() {
  pinMode(pinPirSensorBottom, INPUT); 
  pinMode(pinPirSensorTop, INPUT);
  pirState = 0;
}

void PIRSensor::presenceRoutine() {
  switch (pirState) {
    case 0:
      if (isInTheRoom()) {
        pirState = 1;
      }
      break;
    case 1:
      if (isInTheFloor()) {
        pirState = 2;
        timestampFall = millis();
      }
      break;
    case 2:
      // Wait for FALL_CHECK_TIME_MS milliseconds to confirm the fall
      timestampNow = millis();
      if (timestampNow - timestampFall >= FALL_CHECK_TIME_MS) {
        if (isInTheFloor()) {
          pirState = 3;
        }
        else {
          pirState = 0;
        }
      }
      break;
    case 3:
      presence_alarm = true;

      pirState = 0;
      //Todo: set alarm to flase somewhere....
      break;
  }  
}

boolean PIRSensor::isInTheRoom() {
  boolean presenceBot = readPresence(pinPirSensorBottom);
  boolean presenceTop = readPresence(pinPirSensorTop);
  if (presenceBot && presenceTop) {

    if(DEBUG_PIR_SENSOR){
      Serial.println("Is in the room");
    }
    return true;
  }
  return false;
}

boolean PIRSensor::isInTheFloor() {
  boolean presenceBot = readPresence(pinPirSensorBottom);
  boolean presenceTop = readPresence(pinPirSensorTop);
  if (presenceBot && !presenceTop) {
    if(DEBUG_PIR_SENSOR){
      Serial.println("Is in the floor");
    }
    return true;
  }
  return false;
}

boolean PIRSensor::readPresence(int pin) {
  return digitalRead(pin);
}

void PIRSensor::pirTest() {
  // Testing PIR Sensor
  delay(150);
  if (readPresence(pinPirSensorBottom)) {
    presence_alarm = true;
    Serial.println("TRUE");
  }
  else {
    presence_alarm = false;
    Serial.println("FALSE");
  }
}

bool PIRSensor::checkAlarmStatus(){
  return presence_alarm;
}
