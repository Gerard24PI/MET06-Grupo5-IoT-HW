#include "PIRSensor.h"

#define FALL_CHECK_TIME_MS 200

PIRSensor::PIRSensor(int pinPirSensorBottom, int pinPirSensorTop) : pinPirSensorBottom(pinPirSensorBottom), pinPirSensorTop(pinPirSensorTop) {
  this->presence_alarm = false;
}

void PIRSensor::setupPIR() {
  pinMode(pinPirSensorBottom, INPUT); 
  pinMode(pinPirSensorTop, INPUT);
  pirState = 0;
}

unsigned long timeStampBot = 0;
unsigned long timeStampTop = 0;
bool flag = false;
bool flag2 = false;

void PIRSensor::presenceRoutine() {
  boolean presenceBot = readPresence(pinPirSensorBottom);
  boolean presenceTop = readPresence(pinPirSensorTop);
  // if(DEBUG_PIR_SENSOR){
  //   Serial.println(String(millis()/1000) +  "s --> [SENSORS] PIRTop: " + String(presenceTop) + "PIRBot: " + String(presenceBot));
  // }
  
  if (!flag) {
    Serial.println(String(millis()/1000) +  "s --> [SENSORS] PIRTop: " + String(presenceTop) + " PIRBot: " + String(presenceBot));
  }

  if (presenceTop && !flag && !flag2){
    timeStampTop = millis();
    flag = true;
  }
  if(presenceBot && !flag2 && flag){
    timeStampBot = millis();
    //Serial.println( "Time: " + String(timeStampBot - timeStampTop) + " ms");

    if((timeStampBot - timeStampTop > 10)){
      this->presence_alarm = true;
      flag2 = true;
    }
    else {
      flag = false;
      flag2 = false;
    }
  }
}

void PIRSensor::resetAlarm(){
  this->pirState = 0;
}

boolean PIRSensor::isInTheRoom() {
  boolean presenceBot = readPresence(pinPirSensorBottom);
  boolean presenceTop = readPresence(pinPirSensorTop);
  if (presenceBot && presenceTop) {

    return true;
  }
  return false;
}

boolean PIRSensor::isInTheFloor() {
  boolean presenceBot = readPresence(pinPirSensorBottom);
  boolean presenceTop = readPresence(pinPirSensorTop);
  if (presenceBot && !presenceTop) {

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
