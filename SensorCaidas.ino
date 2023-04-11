#include "config.h"
#include "TempHumSensor.h"
#include "PIRSensor.h"
#include "LED.h"

TempHumSensor tempHumSensor(5000, PIN_TEMP_SENSOR);

// Sensor objects
PIRSensor pirSensor(PIN_PIR_SENSOR_BOTTOM, PIN_PIR_SENSOR_TOP);
LED alarmLED;
Button alarmButton;
Button resetButton;

bool button_alarm = false;

void setupSensorCaidas() {
  alarmLED = LED(PIN_ALARM_LED_NOTIFICATION);
  pirSensor.setupPIR();
  alarmButton = Button(PIN_ALARM_BUTTON);
  resetButton = Button(PIN_MODE_BUTTON);
}

void sensorCaidas(){

  pirSensor.presenceRoutine();
  resetButton.button_routine();
  alarmButton.button_routine();
  tempHumSensor.readSensorData();


  
  int temp_alarms = tempHumSensor.checkAlarmStatus();
  // if(){
  //   alarmLED.turnOn();
  // }else{
  //   alarmLED.turnOff();
  // }
  
  
  // Presence ALARM
  bool presence_alarm = pirSensor.checkAlarmStatus();

  // button ALARM
  if(alarmButton.isPressed()){
    button_alarm = true;
  }

  if(button_alarm || presence_alarm || temp_alarms == TEMP_ALARM || temp_alarms == HUMIDITY_ALARM || temp_alarms == HUMIDITY_AND_TEMP_ALARM){
    alarmLED.turnOn();
  }


  if(resetButton.isPressed()){
    alarmLED.turnOff();
  }


}