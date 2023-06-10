// Global Settings
#define SERIAL_CONNECTION_SPEED       9600
#define BOARD_ESP8266


// Debugging Settings
#define DEBUG_DEVICES_SETUP_BASIC     true
#define DEBUG_ALARMS                  false
#define DEBUG_PIR_SENSOR              true
#define DEBUG_TEMP_HUM_SENSOR         false
#define DEBUG_BUTTONS                 false
#define DEBUG_TIMING                  false
#define DEBUG_GRIFO                   true
#define DEBUG_LEDS                    false


// Menu Options
#define MENU_SCAIDAS  1
#define MENU_GRIFO    2
#define MENU_SLIGHT   3
#define TEST_FIREBASE 4
#define MENU_EXIT     5


// Pin Declarations for ESP8266 board
#ifdef BOARD_ESP8266
  #define BOARD_NAME                  "ESP8266"
  #define PIN_PIR_SENSOR_BOTTOM       13           // D8 (Intermediate Board)
  #define PIN_PIR_SENSOR_TOP          15           // D7 ( Board)
  #define PIN_ALARM_LED_NOTIFICATION  16           // D6 (RED LED)
  #define PIN_AUX_LED                 12            // SDD2          
  #define PIN_ANALOG_INPUT            A0           // A0 (50K POT)
  #define PIN_ALARM_BUTTON            10           // SDD3 (RED BTN)
  #define PIN_MODE_BUTTON             5            // D1 (BTN 1)
  #define PIN_AUX_BUTTON              4            // D2 (BTN 2)
  #define PIN_TEMP_SENSOR             2            // D4  (DHT22)
  #define PIN_SERVO                   14           // D5  (J1)
#endif
