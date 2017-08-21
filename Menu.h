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

#ifndef HEADER_MENU
  #define HEADER_MENU

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Sensor.h"
#include "Bluetooth.h"

#define MENU_INFO     0
#define MENU_SENSOR1  1
#define MENU_SENSOR2  2
#define MENU_SENSOR3  3
#define MENU_RESET    4
#define MENU_ITEMS    5

class Menu {
  public:
    Menu();
    int menu_selected = -1;
    void home();
    void next();
    void prev();
    void exec();
    void clear(byte);
    void decodeBluetooth(int);
  private:
    struct t_menu {
      String text;
      byte id;
    } menus[MENU_ITEMS];
    int menu_current = 1;
    LiquidCrystal_I2C *lcd = NULL;
    bool lcd_backlight = true;
    Sensor *ntc1 = NULL, *ntc2 = NULL, *ntc3 = NULL;
    void showSensor(Sensor *);
    void doReset();
    void storeMin();
    void storeMax();
    byte temp_low[8] = {
      B00100,
      B00100,
      B00100,
      B00100,
      B00100,
      B10101,
      B01110,
      B00100,
    };
    byte temp_high[8] = {
      B00100,
      B01110,
      B10101,
      B00100,
      B00100,
      B00100,
      B00100,
      B00100,
    };
};

#endif
