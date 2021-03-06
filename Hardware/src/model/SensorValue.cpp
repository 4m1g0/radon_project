/*
 NodeInfo.h - Class representing data values of one sensor
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

#include "SensorValue.h"
#include "../Clock/Clock.h"

SensorValue::SensorValue(uint32_t sensorId, int value)
{
  // Current date
  //_date = Clock::getHumanDateTime(Clock::getUnixTime());
  _sensorId = sensorId;
  _value = value;
}

void SensorValue::toJson(ArduinoJson::JsonObject &json)
{
  json.set<uint32_t>("sensorId", _sensorId);
  json.set<String>("date", "");
  json.set<int>("value", _value);
}

void SensorValue::fromJson(ArduinoJson::JsonObject &json)
{
  // not implemented
}
