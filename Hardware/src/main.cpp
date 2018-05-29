#include "Arduino.h"
#include "pins_arduino.h"
#include "Clock/Clock.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>
#include "model/SensorValue.h"
#include "Sensor/RadonSensor.h"
#include <ESP8266httpUpdate.h>

const uint32_t SECONDS = 1000000;

void blinkOK(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
  delay(50);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
  delay(50);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
}

void blinkError() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
  delay(50);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(50);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
}

void setup()
{
  Serial.begin(115200);
  pinMode(D8, OUTPUT);
  pinMode(D5, INPUT);
  pinMode(D7, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(D8, LOW); // sensor power on
  digitalWrite(D6, HIGH);
  delay(5000);

  blinkOK();

  WiFiManager wifiManager;
  String connString = String("Sensor-") + ESP.getChipId();
  wifiManager.autoConnect(connString.c_str());
  Serial.println("Network Connected");

  int i = 0;
  while (!Clock::updateTime())
  {
    Serial.println("Unable to update time.");
    if (i++ > 5)
    {
      blinkError();
      ESP.deepSleep(10 * 60 * SECONDS);
    }
  }

  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  SensorValue* value = RadonSensor::getValue();
  value->toJson(json);
  char jsonChar[60];
  json.printTo((char*)jsonChar, json.measureLength() + 1);

  HTTPClient http;
  http.begin("radon.4m1g0.com", 3000, "/radon/api/v1/history/");
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST(jsonChar);
  http.end();
  Serial.println(String("code: ") + httpCode);

  if (httpCode == 205)
    RadonSensor::reset();

  t_httpUpdate_return ret = ESPhttpUpdate.update("http://radon.4m1g0.com/update/firmware.bin");

    switch (ret) {
      case HTTP_UPDATE_FAILED:
        Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
        break;

      case HTTP_UPDATE_NO_UPDATES:
        Serial.println("HTTP_UPDATE_NO_UPDATES");
        break;

      case HTTP_UPDATE_OK:
        Serial.println("HTTP_UPDATE_OK");
        break;
  }

  ESP.deepSleep(60UL * 60 * SECONDS); // 1 hour
}

void loop()
{
}
