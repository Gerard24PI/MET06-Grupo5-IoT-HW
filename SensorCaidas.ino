#include "config.h"
#include "TempHumSensor.h"
#include "PIRSensor.h"
#include "LED.h"

TempHumSensor tempHumSensor(5000, PIN_TEMP_SENSOR);

// Sensor objects
PIRSensor pirSensor(PIN_PIR_SENSOR_BOTTOM, PIN_PIR_SENSOR_TOP);
LED alarmLED;

void setupSensorCaidas() {
  alarmLED = LED(PIN_ALARM_LED_NOTIFICATION);
  pirSensor.setupPIR();
}

void sensorCaidas(){
  // Humidity & Temp ALARM
  tempHumSensor.readSensorData();
  int temp_alarms = tempHumSensor.checkAlarmStatus();
  if(temp_alarms == TEMP_ALARM || temp_alarms == HUMIDITY_ALARM || temp_alarms == HUMIDITY_AND_TEMP_ALARM){
    alarmLED.turnOn();
  }else{
    alarmLED.turnOff();
  }
  
  // Presence ALARM
  bool presence_alarm = pirSensor.checkAlarmStatus();
  if(presence_alarm){
    alarmLED.turnOn();
  }else{
    alarmLED.turnOff();
  }

  // button ALARM
  bool button_alarm = false;
  if(button_alarm){
    alarmLED.turnOn();
  }else{
    alarmLED.turnOff();
  }
}