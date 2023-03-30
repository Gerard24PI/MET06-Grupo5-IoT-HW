#define BOARD_ESP8266
#include "config.h"
#include "TempHumSensor.h"
#include "PIRSensor.h"
#include "LED.h"


// Sensor objects
TempHumSensor tempHumSensor(5000);
PIRSensor pirSensor(PIN_PIR_SENSOR_BOTTOM, PIN_PIR_SENSOR_TOP);
LED alarmLED;


// MENU 

void setup() {
  // Setup code. runs once
  alarmLED = LED(PIN_ALARM_LED_NOTIFICATION);
  pirSensor.setupPIR();

  Serial.begin(SERIAL_CONNECTION_SPEED);
  
  Serial.println("");
  Serial.println(String(millis()/1000) + " --> [INFO] "+ String(BOARD_NAME) + " connected @" + String(SERIAL_CONNECTION_SPEED) + "baud");

  Serial.println("========================================");
  Serial.println("🚀🚀     Welcome to MET_06 project   🚀🚀");
  Serial.println("           SELECT AN OPTION             ");
  Serial.println("========================================");
  Serial.println("1. Sensor Caidas IoT");
  Serial.println("2. Grifo IoT");
  Serial.println("3. Smart Light IoT");
  Serial.println("4. Salir");
}



void loop() {
  // handle Menu
  if (Serial.available()) {
    int choice = Serial.read() - '0'; // convert char to int
    Serial.println("");

    switch (choice) {
      case 1:
        Serial.println("Executing Sensor Caidas...");
         while (Serial.available() == 0 || Serial.read() != '4') {
          sensorCaidas();
        }
        break;

      case 2:
        while (Serial.available() == 0 || Serial.read() != '4') {
          Serial.println("Executing Grifo IoT...");
        }
        break;
      
      case 3:
        while (Serial.available() == 0 || Serial.read() != '4') {
          Serial.println("Executing Smart Light IoT...");
        }
        break;

      case 4:
        Serial.println("Exiting program...");
        exit(0);
        break;

      
      default:
        Serial.println("Invalid choice. Please try again.");
        break;
    }

    Serial.println("");
    Serial.println("========================================");
    Serial.println("           SELECT AN OPTION             ");
    Serial.println("========================================");
    Serial.println("1. Sensor Caidas IoT");
    Serial.println("2. Grifo IoT");
    Serial.println("3. Smart Light IoT");
    Serial.println("4. Salir");

  }
}
