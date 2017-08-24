/*
    Copyright 2017 Evandro Pires Alves

    This file is part of Frigorifico.

    Foobar is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <IRremote.h>
#include <Wire.h> 
#include "Menu.h"
#include "Sensor.h"
#include "Storage.h"

#define VERSION     0.1

Menu *menu = NULL;
unsigned long lcd_update_previous = 0;
unsigned long lcd_update_current = 0;

void setup()
{
  // Relays
  pinMode(RELAY_1, OUTPUT);  // Relay 1
  pinMode(RELAY_2, OUTPUT);  // Relay 2
  pinMode(RELAY_3, OUTPUT);  // Relay 3
  pinMode(RELAY_4, OUTPUT);  // Relay 4
  // Bluetooth
  Serial.begin(9600);
  menu = new Menu();
  menu->home();
}

void loop()
{
  if (Serial.available() > 0) {
    menu->decodeBluetooth(Serial.read());
  }

  // if we are inside a sensor menu, keep updating the value every 5 seconds
  lcd_update_current = millis();
  if (lcd_update_current > 5000 && lcd_update_current - 5000 > lcd_update_previous) {
    lcd_update_previous = lcd_update_current;
    if (menu->menu_selected == MENU_SENSOR1 || menu->menu_selected == MENU_SENSOR2 || menu->menu_selected == MENU_SENSOR3) {
      menu->exec();
    }
  }
}



