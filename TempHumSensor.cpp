#include "config.h"
#include "TempHumSensor.h"


TempHumSensor::TempHumSensor(int alarm_interval, int pin) : dht(pin) {
  this->temperature = 0.0;
  this->humidity = 0.0;
  this->alarm_interval = alarm_interval;
  this->temp_alarm = false;
  this->humidity_alarm = false;
}

void TempHumSensor::readSensorData() {
    static unsigned long last_reading_timestamp = 0;

    if (millis() - last_reading_timestamp > int(READING_INTERVAL)) {
        temperature = dht.getTemperature();
        humidity = dht.getHumidity();
        last_reading_timestamp = millis();

        if(DEBUG_TEMP_HUM_SENSOR){
          Serial.println(String(last_reading_timestamp/1000) +  "s --> [SENSORS] Temp: " + String(temperature) + "; Hum:" + String(humidity));          
        }
        
    }
}

float TempHumSensor::getLastTemperatureCelsius(){
  readSensorData();
  return temperature;
}

float TempHumSensor::getLastHumidity(){
  readSensorData();
  return humidity;
}


int TempHumSensor::checkAlarmStatus(){
  static unsigned long last_alarm_timestamp = 0;

  if (millis() - last_alarm_timestamp > alarm_interval) {
    last_alarm_timestamp = millis();
    temp_alarm = (temperature < float(MIN_TEMP) || temperature > float(MAX_TEMP));
    humidity_alarm = (humidity < float(MIN_HUMIDITY) || humidity > float(MAX_HUMIDITY));

    if(DEBUG_ALARMS){
      Serial.println(String(last_alarm_timestamp/1000) +  "s --> [ALARMS] Temp Alarm: " + String(temp_alarm) + "; Hum Alarm: " + String(humidity_alarm));
    }
  }

  if (humidity_alarm && temp_alarm){
    return HUMIDITY_AND_TEMP_ALARM;
  }else{
    if(temp_alarm){
      return TEMP_ALARM;
    }

    if (humidity_alarm){
      return HUMIDITY_ALARM;
    }
  }
  return NO_ALARM;
}


