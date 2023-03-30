// BOARD
#define BOARD_ESP8266


// Global Settings
#define SERIAL_CONNECTION_SPEED       9600

// Debug Settings
#define DEBUG_DEVICES_SETUP_BASIC     true
#define DEBUG_ALARMS                  true
#define DEBUG_TEMP_HUM_SENSOR         false

// Pin Declarations for ESP8266 board
#ifdef BOARD_ESP8266
  #define BOARD_NAME                  "ESP8266"
  #define PIN_PIR_SENSOR_BOTTOM       5
  #define PIN_PIR_SENSOR_TOP          16
  #define PIN_ALARM_LED_NOTIFICATION  4
  #define PIN_ALARM_BUTTON            10 // TODO: Confirm button pin
  #define PIN_TEMP_SENSOR             0
#endif
