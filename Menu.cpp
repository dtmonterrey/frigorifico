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

#include "Menu.h"

Menu::Menu()
{
  // init menus
  menus[0].text = "0 Informacoes";
  menus[0].id   = MENU_INFO;
  menus[1].text = "1 Frio";
  menus[1].id   = MENU_SENSOR1;
  menus[2].text = "2 Gelo";
  menus[2].id   = MENU_SENSOR2;
  menus[3].text = "3 Ambiente";
  menus[3].id   = MENU_SENSOR3;
  menus[4].text = "* RESET";
  menus[4].id   = MENU_RESET;

  // init NTCs
  ntc1 = new Sensor(0, "Frio");
  ntc2 = new Sensor(1, "Gelo");
  ntc3 = new Sensor(2, "Ambiente");
}

void Menu::home() {
  Serial.println("\n\n\n==========");
  Serial.println("   ENTER   " + BLUETOOTH_PLAY);
  Serial.println("<- PREV    " + BLUETOOTH_PREV);
  Serial.println("-> NEXT    " + BLUETOOTH_NEXT);
  Serial.println("-  LESS    " + BLUETOOTH_LESS);
  Serial.println("+  MORE    " + BLUETOOTH_MORE);
  Serial.println("x  ESC     " + BLUETOOTH_ESC);
  Serial.println("   MAIN MENU");
  Serial.println(menus[menu_current].text);
}

void Menu::next()
{
  menu_current++;
  if (menu_current >= MENU_ITEMS) {
    menu_current = 0;
  }
  Serial.println("   MAIN MENU");
  Serial.println(menus[menu_current].text);
}

void Menu::prev()
{
  menu_current--;
  if (menu_current < 0) {
    menu_current = MENU_ITEMS - 1;
  }
  Serial.println("   MAIN MENU");
  Serial.println(menus[menu_current].text);
}

void Menu::clear(byte line)
{
  Serial.println("==========\n\n\n");
}

void Menu::exec()
{
  switch (menus[menu_selected].id)
  {
    case MENU_SENSOR1:
      showSensor(ntc1);
      break;
    case MENU_SENSOR2:
      showSensor(ntc2);
      break;
    case MENU_SENSOR3:
      showSensor(ntc3);
      break;
    case MENU_RESET:
      doReset();
      break;
    case MENU_RELAYS:
      showRelays();
      break;
  }
}

void Menu::showSensor(Sensor *sensor) {
  Serial.println(sensor->name);
  Serial.println(sensor->read());
  Serial.println(sensor->min);
  Serial.println(sensor->max);
}

void Menu::doReset() {
  Serial.print("Reset de Mins e Maximos... ");
  ntc1->reset();
  ntc2->reset();
  ntc3->reset();
  Serial.println("Feito!");
}

void Menu::storeMin() {
  switch (menu_current)
  {
    case MENU_SENSOR1:
      ntc1->storeMin(ntc1->read());
      break;
    case MENU_SENSOR2:
      ntc2->storeMin(ntc2->read());
      break;
    case MENU_SENSOR3:
      ntc3->storeMin(ntc3->read());
      break;
  }
  exec();
}

void Menu::storeMax() {
  switch (menu_current)
  {
    case MENU_SENSOR1:
      ntc1->storeMax(ntc1->read());
      break;
    case MENU_SENSOR2:
      ntc2->storeMax(ntc2->read());
      break;
    case MENU_SENSOR3:
      ntc3->storeMax(ntc3->read());
      break;
  }
  exec();
}

void Menu::decodeBluetooth(int command)
{
  switch (command) {
    case BLUETOOTH_NEXT:
      next();
      break;
    case BLUETOOTH_PREV:
      prev();
      break;
    case BLUETOOTH_PLAY:
      menu_selected = menu_current;
      exec();
      break;
    case BLUETOOTH_ESC:
      menu_selected = -1;
      home();
      break;
    case BLUETOOTH_LESS:
      storeMin();
      break;
    case BLUETOOTH_MORE:
      storeMax();
      break;
    default:
      break;
  }
}

