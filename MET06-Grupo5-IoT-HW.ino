#define BOARD_ESP8266
#include "config.h"


#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#elif defined(ARDUINO_RASPBERRY_PI_PICO_W)
#include <WiFi.h>
#include <FirebaseESP8266.h>
#endif


// define global variables
float firebaseHumidity = 0.0;
bool firebaseHumidityAlarm = false;
bool firebasePresenceAlarm = false;
bool firebaseTempAlarm = false;
int firebaseLight = 0;
int firebaseTemp = 0;
int firebaseServo = 0;

// Provide the token generation process info.
#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "VODAFONE_E200"
#define WIFI_PASSWORD "exito2020"
#define API_KEY "AIzaSyAmW8Qm3YYyRfSWZ_6_hKzw2KFvcQ9OThE"
#define DATABASE_URL "https://met06-f9acf-default-rtdb.europe-west1.firebasedatabase.app/"
#define USER_EMAIL "marcnueno@gmail.com"
#define USER_PASSWORD "Hola12340!"

// Define Firebase Data object
FirebaseData stream;
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
volatile bool dataChanged = false;

#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
WiFiMulti multi;
#endif


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
    Serial.println("4. Test FIREBASE");
    Serial.println("5. Salir");
    
    inputOk = false;
    while (!inputOk) {
      if (Serial.available()) {
        inputOk = true;
        choice = Serial.read() - '0'; // convert char to int
        if (choice > 0 && choice <= MENU_EXIT) {
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
    case TEST_FIREBASE:
      Serial.println("Testing Firebase config...");  
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
    case TEST_FIREBASE:
      
      break;
  }
}

void setup() {
  Serial.begin(SERIAL_CONNECTION_SPEED);
  printConnection();

  #if defined(ARDUINO_RASPBERRY_PI_PICO_W)
    multi.addAP(WIFI_SSID, WIFI_PASSWORD);
    multi.run();
  #else
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  #endif

  Serial.print("Connecting to Wi-Fi");
  unsigned long ms = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  #if defined(ARDUINO_RASPBERRY_PI_PICO_W)
      if (millis() - ms > 10000)
        break;
  #endif
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

  // The WiFi credentials are required for Pico W
  // due to it does not have reconnect feature.
  #if defined(ARDUINO_RASPBERRY_PI_PICO_W)
    config.wifi.clearAP();
    config.wifi.addAP(WIFI_SSID, WIFI_PASSWORD);
  #endif

  // Or use legacy authenticate method
  // config.database_url = DATABASE_URL;
  // config.signer.tokens.legacy_token = "<database secret>";

  // To connect without auth in Test Mode, see Authentications/TestMode/TestMode.ino

  Firebase.begin(&config, &auth);

  Firebase.reconnectWiFi(true);


  //Configure Callbacks
  if (!Firebase.beginStream(stream, "/sensors_data"))
    Serial.printf("stream begin error, %s\n\n", stream.errorReason().c_str());
  Firebase.setStreamCallback(stream, streamCallback, streamTimeoutCallback);

  option = printMenu();
  // Setup code. runs once
  setupByChoice(option);
}


void loop() {
  #if defined(ARDUINO_RASPBERRY_PI_PICO_W)
    Firebase.runStream();
  #endif
  executeByChoice(option);
}
