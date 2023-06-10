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

  unsigned long last_FB_update = 0;
  
  int temp_alarms = tempHumSensor.checkAlarmStatus();
  // Presence ALARM
  bool presence_alarm = pirSensor.checkAlarmStatus();

// Update temps in Firebase

if (millis() - last_FB_update > 1000) {
  last_FB_update = millis();
  
  setTemperatureToFB(tempHumSensor.getLastTemperatureCelsius());
  setHumidityToFB(tempHumSensor.getLastHumidity());
  }

  // button ALARM
  if(alarmButton.isPressed()){
    button_alarm = true;
  }

  if(button_alarm || presence_alarm || temp_alarms == TEMP_ALARM || temp_alarms == HUMIDITY_ALARM || temp_alarms == HUMIDITY_AND_TEMP_ALARM){
    alarmLED.turnOn();


    if(presence_alarm){
      setPresenceAlarmToFB(true);
    }

    if (temp_alarms == TEMP_ALARM){
      setTemperatureAlarmToFB(true);
    }else{
      if(temp_alarms != HUMIDITY_AND_TEMP_ALARM){
        setTemperatureAlarmToFB(false);
      }
    }

    if (temp_alarms == HUMIDITY_ALARM){
      setHumAlarmToFB(true);
    }else{
      if(temp_alarms != HUMIDITY_AND_TEMP_ALARM){
        setHumAlarmToFB(false);
      }
    }

    if (temp_alarms == HUMIDITY_AND_TEMP_ALARM){
      setTemperatureAlarmToFB(true);
      setHumAlarmToFB(true);
    } 
  }


  if(resetButton.isPressed()){
    alarmLED.turnOff();
    
    pirSensor.resetAlarm();
    setPresenceAlarmToFB(false);
  }


}