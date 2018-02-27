/*
 RadonSensor.cpp - Radon Sensor controller
 Copyright (c) 2016 Oscar Blanco.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "RadonSensor.h"
#include <Arduino.h>

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

void select(int n)
{
  digitalWrite(D7, n & 0b0001);
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
  while (digitalRead(D5) != LOW) {  }

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

int _getValue(){
  digitalWrite(D6, LOW);
  delay(1000);
  int value = getSegment(LCD_1) + getSegment(LCD_2) * 10 + getSegment(LCD_3) * 100 + getSegment(LCD_4) * 1000;
  delay(100);
  digitalWrite(D6, HIGH);
  return value;
}

SensorValue* RadonSensor::getValue() {
  Serial.println("Reading sensor...");
  return new SensorValue(1, _getValue());
}
