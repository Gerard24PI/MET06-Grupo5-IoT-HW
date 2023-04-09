#ifndef TEMP_HUM_SENSOR_H
#define TEMP_HUM_SENSOR_H

#include <Arduino.h>
#include <DHT22.h>

// Sensor Configuration
#define READING_INTERVAL        2000 // Sensor gives readings each 2000ms

// ALARM configuration
#define MIN_TEMP                10.0
#define MAX_TEMP                23.5
#define MIN_HUMIDITY            10.0
#define MAX_HUMIDITY            80.0

// ALARM modes definitions
#define NO_ALARM                0
#define TEMP_ALARM              1
#define HUMIDITY_ALARM          2
#define HUMIDITY_AND_TEMP_ALARM 3

class TempHumSensor {
  private:
    DHT22 dht;
    float temperature;
    float humidity;
    int alarm_interval;
    bool temp_alarm;
    bool humidity_alarm;

  public:
    
    /*
     * Constructor to initialize the sensor
     *
     * @param interval: Interval between sensor readings in milliseconds
     */
    TempHumSensor(int interval, int pin);
    

    

    /*
     * Update sensor readings. Valeus are only updated each interval
     */
    void readSensorData();

    /*
     * Method to get temperature data
     *
     * @return: Temperature in degrees Celsius
     */
    float getLastTemperatureCelsius();

    /*
     * Method to get humidity data
     *
     * @return: Relative humidity as percentage
     */
    float getLastHumidity();


    /*
     * Method to check alarm status
     *
     * @return: alarm code: 0 - NO ALARM, 1 - TEMP, 2 - HUMIDITY, 3 - HUMIDITY AND TEMP
     */
    int checkAlarmStatus();


};

#endif
