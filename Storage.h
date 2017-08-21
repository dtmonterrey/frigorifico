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

#ifndef HEADER_STORAGE
  #define HEADER_STORAGE

#include <EEPROM.h>
#include <Arduino.h>

class Storage {
  public:
    static void clear();
    static void storeInt(int address, int value);
    static int readInt(int address);
};

#endif
