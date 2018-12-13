#include "Arduino.h"
#include "pins_arduino.h"
//#include "Clock/Clock.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
//#include <WiFiManager.h>
#include <ArduinoJson.h>
#include "model/SensorValue.h"
#include "Sensor/RadonSensor.h"
#include <ESP8266httpUpdate.h>
#include <Ds1307.h>
#include "Password.h"
#include "FS.h"

extern "C" {
  #include <user_interface.h>
}

#define DS1307_I2C_ADDRESS 0x68

// DS1307 RTC instance
Ds1307 rtc(DS1307_I2C_ADDRESS);

const uint32_t SECONDS = 1000000;


void setup()
{
  Serial.begin(115200);
  pinMode(D8, OUTPUT);
  //pinMode(A0, INPUT);
  pinMode(D7, OUTPUT);
  pinMode(D5, OUTPUT); // D1
  pinMode(D4, OUTPUT); // D2
  pinMode(D3, OUTPUT); 
  pinMode(D6, OUTPUT);

  digitalWrite(D8, LOW); // sensor power on
  //digitalWrite(D8, HIGH);
  digitalWrite(D6, HIGH);
  delay(1000);

  //blinkOK();
  
  rtc.init();
  SPIFFS.begin();

  /*WiFiManager wifiManager;
  //wifiManager.resetSettings();
  String connString = String("Sensor-") + ESP.getChipId();
  wifiManager.autoConnect(connString.c_str());
  Serial.println("Network Connected");*/
  uint8_t mac[6] {0x68, 0xC6, 0x3A, 0xE1, 0x4C, 0xD0};
  wifi_set_macaddr(STATION_IF, mac);  
  delay(4000);
  WiFi.begin("udcportal"); 
  Serial.print("Connecting to ");
  Serial.print("udcportal"); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
    if (i > 10)
      break;
  }
  
  if (rtc.isHalted())
  {
    Serial.println("RTC is halted. Setting time...");

    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.println("Not connected to a network, unable to get NTP time.");
      ESP.deepSleep(10 * 60 * SECONDS);
    }

    HTTPClient http;
    http.begin("radon.4m1g0.com", 3000, "/radon/api/v1/time");
    int httpCode = http.GET();
    if (httpCode != HTTP_CODE_OK) {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      Serial.println("Unable to update time.");
      ESP.deepSleep(10 * 60 * SECONDS);
    }

    String time = http.getString();

    Serial.println(time);

    Ds1307::DateTime dt = {
        .year = atoi(time.substring(2, 4).c_str()),
        .month = atoi(time.substring(5, 7).c_str()),
        .day = atoi(time.substring(8, 10).c_str()),
        .hour = atoi(time.substring(0, 2).c_str()) +1 ,
        .minute = atoi(time.substring(3, 5).c_str()),
        .second = atoi(time.substring(6, 8).c_str()),
        .dow = Ds1307::DOW_THU
    };

    rtc.setDateTime(&dt);
    Serial.println("RTC Updated.");
  }


  DynamicJsonBuffer jsonBuffer;

  JsonObject& json = jsonBuffer.createObject();
  SensorValue* value = RadonSensor::getValue();
  value->toJson(json);
  Ds1307::DateTime now;
  rtc.getDateTime(&now);

  json.set<String>("date", String(now.year + 2000) + "-" + now.month + "-" + now.day + " " + now.hour + ":" + now.minute + ":" + now.second);
  char jsonChar[66];
  json.printTo((char*)jsonChar, json.measureLength() + 1);
  
  File f = SPIFFS.open("data.txt", "a+");
  f.println(jsonChar);
  f.close();

  f = SPIFFS.open("data.txt", "r");
  while(f.available()) {
      //Lets read line by line from the file
    String line = f.readStringUntil('\n');
    Serial.println(line);
  }
  f.close();
  
  
  if (WiFi.status() == WL_CONNECTED){
    int httpCode;
    f = SPIFFS.open("data.txt", "r");
    while(f.available()) {
      HTTPClient http;
      http.begin("radon.4m1g0.com", 3000, "/radon/api/v1/history/");
      http.addHeader("Content-Type", "application/json");
      //Lets read line by line from the file
      String line = f.readStringUntil('\n');
      httpCode = http.POST(line);
      http.end();
      Serial.println(String("code: ") + httpCode);
    }
    f.close();

    if (httpCode > 0)
      SPIFFS.remove("data.txt");

    if (httpCode == 205)
      RadonSensor::reset();

    String url = "http://radon.4m1g0.com/update/";
    url += String(ESP.getChipId()) + String(".bin");
    t_httpUpdate_return ret = ESPhttpUpdate.update(url);

    switch (ret) {
      case HTTP_UPDATE_FAILED:
        Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
        break;

      case HTTP_UPDATE_NO_UPDATES:
        Serial.println("HTTP_UPDATE_NO_UPDATES");
        break;

      case HTTP_UPDATE_OK:
        Serial.println("HTTP_UPDATE_OK");
        break;
    }
  }

  ESP.deepSleep(60UL * 60 * SECONDS); // 1 hour
}

void loop()
{
}
