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

 #ifndef SENSORVALUE_H
 #define SENSORVALUE_H

 #include "Serializable.h"
 #include <ArduinoJson.h>

class SensorValue : public Serializable<JsonObject&>
{
public:
  SensorValue(int sensorId, int value);
  void fromJson(JsonObject& json);
  void toJson(JsonObject& json);

protected:
  String _date;
  int _sensorId;
  int _value;
};

#endif
