#define BOARD_ESP8266
#include "config.h"
#include "TempHumSensor.h"
#include "PIRSensor.h"
#include "LED.h"

// MENU 
#define MENU_SCAIDAS  1
#define MENU_GRIFO    2
#define MENU_SLIGHT   3
#define MENU_EXIT     4

int option;

void printConnection() {
  Serial.println(String(millis()/1000) + " --> [INFO] "+ String(BOARD_NAME) + " connected @" + String(SERIAL_CONNECTION_SPEED) + "baud");
}

int printMenu() {
  int choice;
  bool getOk = false;
  bool inputOk;
  while (!getOk) {
    Serial.println("========================================");
    Serial.println("🚀🚀     Welcome to MET_06 project   🚀🚀");
    Serial.println("           SELECT AN OPTION             ");
    Serial.println("========================================");
    Serial.println("1. Sensor Caidas IoT");
    Serial.println("2. Grifo IoT");
    Serial.println("3. Smart Light IoT");
    Serial.println("4. Salir");
    
    inputOk = false;
    while (!inputOk) {
      if (Serial.available()) {
        inputOk = true;
        choice = Serial.read() - '0'; // convert char to int
        if (choice > 0 && choice <= 4) {
          getOk = true;
        }
        else {
          Serial.println("\nInvalid choice. Please try again.\n");
        }
      }
    }

  }
  return choice;
}

void setupByChoice(int opt) {
  switch (opt) {
    case MENU_SCAIDAS:
      Serial.println("Initializating Sensor Caidas...");
      setupSensorCaidas();
      break;
    case MENU_GRIFO:
      Serial.println("Initializating Grifo IoT..."); 
      setupGrifo();
      break; 
    case MENU_SLIGHT:
      Serial.println("Initializating Smart Light IoT...");  
      setupSmartLight();
      break;
    case MENU_EXIT:
      Serial.println("Exiting program...");  
      exit(0);
      break;
  }
  Serial.println("Executing...");
}

void executeByChoice(int opt) {
  switch (opt) {
    case MENU_SCAIDAS:
      sensorCaidas();
      break;
    case MENU_GRIFO:
      grifo();
      break; 
    case MENU_SLIGHT:
      smartLight();
      break;
  }
}

void setup() {
  Serial.begin(SERIAL_CONNECTION_SPEED);
  printConnection();
  option = printMenu();
  // Setup code. runs once
  setupByChoice(option);

}



void loop() {
  executeByChoice(option);
}
