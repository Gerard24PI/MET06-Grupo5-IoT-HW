# MET06-Grupo5-IoT-HW

Entrega 07 de Abril 2023
Entrega 1: Sensor de caídas IoT

Este sensor debe detectar la caída de una persona y en el momento de detectarlo debe encender un Led.

    Detectar caídas producidas en el baño --> Al detectar notificar emergencia
    Botón del pánico (simulado con pushbutton) -> Al apretar notificar emergencia
    Sensor de temperatura y humedad. Con constantes máximas que al superarse se notifica con la emergencia

Todas las emergencias se notifican mediante un LED
Entrega 2: Smart Light IoT

    LED regulable: Subir o bajar la intensidad del LED
    Con un pulsador se puede regular la intensidad en 4 modos
    Grifo inteligente: Con un servo se simula un grifo automático que se mueve con 3 intensidades a partir de un grifo. Indicar intensidad (cerrado, medio, alto) y frecuencia (Cuantos bips)

Links:

    Sensor PIR HC-SR501 https://solectroshop.com/es/content/70-como-hacer-un-detector-de-movimiento-con-arduino-y-el-sensor-hc-sr501

Pinout: Pinout


class LED {

#define	PERIOD		20 // The period in ms
#define MODE_ALARM		1
#define MODE_VARIABLE	2

#define	LOW_INTENSITY	25
#define	MED_INTENSITY	50
#define	HIGH_INTENSITY	75
#define	MAX_INTENSITY	100

private:
  int pin;				// The pin where led is connected
  float intensity;		// The intensity of the led arrays
  int mode;				// The LED mode

public:
  LED(int pin, int mode);

  void setModesArray();	//Set the modes array for variable intensity

  void turnOn();		// Set intensity to 100
  void turnOff();		// Set intensity to 0
  
  void setLedIntensity(int intensity);


  void setIntensityMode(2);


  int updateLED();			// Executes always and updates the brightness

};


class TempHumSensor {

#define	....


private:
  int pin;				// The pin where sensor is connected
  DHT22 dht;
  float temperature;
  float humidity;
  int alarm_interval;
  bool temp_alarm;
  bool humidity_alarm;


public:
  TempHumSensor(int pin, int interval);

  void readSensorData()

  float getLastTemperatureCelsius();

  float getLastHumidity();

  int checkAlarmStatus();	// Executes always in the loop

};



class Button{

private:
  int pin;				// The pin where button is connected
  boolean status;



public:
  Button(int pin);

  boolean isPressed();	// Executes always in the loop

  void buttonRoutine();	// 
	
}


class Servomotor{

#define POS_TANCAT	0
#define POS_SEMIOBERT 90
#define POS_OBERT 	  180

private:
  int pin;				// The pin where button is connected
  Servo servomotor;
  boolean status;

public:
  Servomotor(int pin);

  void moveServo(int degrees);

  void buttonRoutine();	// 
	
}




PIRSensor



LightSensor



Timer
