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

#include "Storage.h"

void Storage::clear()
{
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.update(i, 0);
  }
}

void Storage::storeInt(int address, int value) {
  Serial.begin(9600);
  Serial.println(address);
  Serial.println(value);
  EEPROM.update(address+1, value);
  value = value >> 8;
  EEPROM.update(address, value);
}

int Storage::readInt(int address) {
  int value = 0;
  byte b0 = EEPROM.read(address);
  value = b0;
  value = value << 8;
  byte b1 = EEPROM.read(address+1);
  return value + b1;
}

