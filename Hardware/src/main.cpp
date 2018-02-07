#include "Arduino.h"
#include "pins_arduino.h"
#include "Clock/Clock.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

enum radonPinout {
  SEG_A = 0,
  SEG_B,
  SEG_C,
  SEG_D,
  SEG_E,
  SEG_F,
  SEG_G,
  LCD_1,
  LCD_4,
  LCD_3,
  LCD_2,
  LCD_L4,
};
int ledStatus = LOW;

const char* _ssid = "***";
const char* _password = "***";

void setup()
{
  Serial.begin(9600);
  pinMode(D5, INPUT);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);


  WiFi.mode(WIFI_STA);
  WiFi.begin(_ssid, _password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  while (!Clock::updateTime())
  {
    Serial.println("Unable to update time.");
  }
}

void select(int n)
{
  digitalWrite(D0, n & 0b0001);
  digitalWrite(D1, n & 0b0010);
  digitalWrite(D2, n & 0b0100);
  digitalWrite(D3, n & 0b1000);
}

void printSegments() {
  select(SEG_A);
  int A = digitalRead(D5);
  select(SEG_B);
  int B = digitalRead(D5);
  select(SEG_C);
  int C = digitalRead(D5);
  select(SEG_D);
  int D = digitalRead(D5);
  select(SEG_E);
  int E = digitalRead(D5);
  select(SEG_F);
  int F = digitalRead(D5);
  select(SEG_G);
  int G = digitalRead(D5);

  Serial.print(A);
  Serial.print(B);
  Serial.print(C);
  Serial.print(D);
  Serial.print(E);
  Serial.print(F);
  Serial.print(G);
  Serial.println();
}

int getSegment(int n){
  select(n);
  while (digitalRead(D5) != LOW) {}

  select(SEG_A);
  int A = !digitalRead(D5);
  select(SEG_B);
  int B = !digitalRead(D5);
  select(SEG_C);
  int C = !digitalRead(D5);
  select(SEG_D);
  int D = !digitalRead(D5);
  select(SEG_E);
  int E = !digitalRead(D5);
  select(SEG_F);
  int F = !digitalRead(D5);
  select(SEG_G);
  int G = !digitalRead(D5);

  int mask = (A<<6) | (B<<5) | (C<<4) | (D<<3) | (E<<2) | (F<<1) | G;

  switch (mask) {
    case 0b0000000:
      return 0;
    case 0b1111110:
      return 0;
    case 0b0110000:
      return 1;
    case 0b1101101:
      return 2;
    case 0b1111001:
      return 3;
    case 0b0110011:
      return 4;
    case 0b1011011:
      return 5;
    case 0b0011111:
      return 6;
    case 0b1110000:
      return 7;
    case 0b1111111:
      return 8;
    case 0b1110011:
      return 9;
  }

  return -1;
}

int getValue(){
  return getSegment(LCD_1) + getSegment(LCD_2) * 10 + getSegment(LCD_3) * 100 + getSegment(LCD_4) * 1000;
}

int i = 0;
void loop()
{
  Serial.print("LCD1: ");
  select(LCD_1);
  while (digitalRead(D5) != LOW) {}
  printSegments();

  Serial.print("LCD2: ");
  select(LCD_2);
  while (digitalRead(D5) != LOW) {}
  printSegments();

  Serial.print("LCD3: ");
  select(LCD_3);
  while (digitalRead(D5) != LOW) {}
  printSegments();
  Serial.print("LCD4: ");
  select(LCD_4);
  while (digitalRead(D5) != LOW) {}
  printSegments();
  Serial.println();
  Serial.println(getSegment(LCD_1));
  Serial.println(getSegment(LCD_2));
  Serial.println(getSegment(LCD_3));
  Serial.println(getSegment(LCD_4));
  int value = getValue();
  Serial.println(value);

  digitalWrite(LED_BUILTIN, ledStatus);
  ledStatus = !ledStatus;
  delay(5000);

  i++;
  //720
  if (i > 720){
    i = 0;
    HTTPClient http;

    http.begin(String("http://4m1g0.com/radon/save.php?timestamp=") + Clock::getUnixTime() + "&value=" + value);
    int httpCode = http.GET();
    Serial.println(String("code: ") + httpCode);
    http.end();
  }
}
