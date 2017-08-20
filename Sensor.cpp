/*
    Copyright 2017 Evandro Pires Alves

    This file is part of Frigorífico.

    Frigorífico is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Frigorífico is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Frigorífico.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Sensor.h"

Sensor::Sensor(int id, String name) {
  this->id = id;
  this->name = name;
  this->min = Storage::readInt(4*this->id);
  this->max = Storage::readInt(4*this->id+2);
}

int Sensor::read() {
  return random(0,1024);
}

void Sensor::storeMin(int value) {
  if (this->max > value) {
    Storage::storeInt(4*this->id, value);
    this->min = value;
  }
}

void Sensor::storeMax(int value) {
  if (value > this->min) {
    Storage::storeInt(4*this->id+2, value);
    this->max = value;
  }
}

void Sensor::reset() {
  storeMin(0);
  storeMax(1024);
}

