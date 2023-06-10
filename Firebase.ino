void streamCallback(StreamData data){
  String path = data.dataPath().c_str();
  if (path == "/humidity_alarm"){
    humidityAlarmCallback(data);
  }else if (path == "/presence_alarm"){
    presenceAlarmCallback(data);
  }else if (path == "/temp_alarm"){
    tempAlarmCallback(data);
  }else if (path == "/humidity"){
    humidityCallback(data);
  }else if (path == "/temp"){
    tempCallback(data);
  }else if (path == "/light"){
    lightCallback(data);
  }else if (path == "/servo"){
    servoCallback(data);
  }else{
    Serial.println("Path does not exist in Firebase");
  }
}

void humidityAlarmCallback(StreamData data)
{
  Serial.print("Humidity Alarm Updated: ");
  printResult(data);
  Serial.println();
}

void presenceAlarmCallback(StreamData data)
{
  Serial.print("Presence Alarm Updated: ");
  printResult(data);
  Serial.println();
}

void tempAlarmCallback(StreamData data)
{
  Serial.print("Temp Alarm Updated: ");
  printResult(data);
  Serial.println();
}

void humidityCallback(StreamData data)
{
  Serial.print("Humidity Updated: ");
  printResult(data);
  Serial.println();
}

void tempCallback(StreamData data)
{
  Serial.print("Temp Updated: ");
  printResult(data);
  Serial.println();
}




void streamTimeoutCallback(bool timeout)
{
  if (timeout)
    Serial.println("stream timed out, resuming...\n");

}



void setHumidityToFB(float hum) {
  Firebase.RTDB.setFloat(&fbdo, F("sensors_data/humidity"), hum);
}
float getHumidityFromFB() {
  Firebase.RTDB.getFloat(&fbdo, F("sensors_data/humidity"));
  return fbdo.to<float>();
}

void setHumAlarmToFB(bool hum_alarm) {
  Firebase.RTDB.setBool(&fbdo, F("sensors_data/humidity_alarm"), hum_alarm);
}
bool getHumAlarmFromFB() {
  Firebase.RTDB.getBool(&fbdo, FPSTR("sensors_data/humidity_alarm"));
  return fbdo.to<bool>();
}

void setLightToFB(int light) {
  Firebase.RTDB.setInt(&fbdo, F("sensors_data/light"), (int)light);
}
int getLightFromFB() {
  Firebase.RTDB.getInt(&fbdo, F("sensors_data/light"));
  return fbdo.to<int>();
}

void setPresenceAlarmToFB(bool pres_alarm) {
  Firebase.RTDB.setBool(&fbdo, F("sensors_data/presence_alarm"), pres_alarm);
}
bool getPresenceAlarmFromFB() {
  Firebase.RTDB.getBool(&fbdo, FPSTR("sensors_data/presence_alarm"));
  return fbdo.to<bool>();
}

void setServoToFB(int servo) {
  Firebase.RTDB.setInt(&fbdo, F("sensors_data/servo"), (int)servo);
}
int getServoFromFB() {
  Firebase.RTDB.getInt(&fbdo, F("sensors_data/servo"));
  return fbdo.to<int>();
}

void setTemperatureToFB(int temp) {
  Firebase.RTDB.setInt(&fbdo, F("sensors_data/temp"), (int)temp);
}
int getTemperatureFromFB() {
  Firebase.RTDB.getInt(&fbdo, F("sensors_data/temp"));
  return fbdo.to<int>();
}

void setTemperatureAlarmToFB(bool temp_alarm) {
  Firebase.RTDB.setBool(&fbdo, F("sensors_data/temp_alarm"), temp_alarm);
}
bool getTemperatureAlarmFromFB() {
  Firebase.RTDB.getBool(&fbdo, FPSTR("sensors_data/temp_alarm"));
  return fbdo.to<bool>();
}