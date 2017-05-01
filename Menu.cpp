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

  // init LCD
  lcd = new LiquidCrystal_I2C(0x3F,16,2);
  lcd->init();
  if (lcd_backlight) lcd->backlight(); else lcd->noBacklight();
  lcd->createChar(0, temp_low);
  lcd->createChar(1, temp_high);

  // init NTCs
  ntc1 = new Sensor(0, "Frio");
  ntc2 = new Sensor(1, "Gelo");
  ntc3 = new Sensor(2, "Ambiente");
}

void Menu::home() {
  lcd->clear();
  lcd->backlight();
  lcd->print("   MAIN MENU");
  lcd->setCursor(0,1);
  lcd->print(menus[menu_current].text);
}

void Menu::next()
{
  menu_current++;
  if (menu_current >= MENU_ITEMS) {
    menu_current = 0;
  }
  lcd->clear();
  lcd->print("   MAIN MENU");
  lcd->setCursor(0,1);
  lcd->print(menus[menu_current].text);
}

void Menu::prev()
{
  menu_current--;
  if (menu_current < 0) {
    menu_current = MENU_ITEMS - 1;
  }
  lcd->clear();
  lcd->print("   MAIN MENU");
  lcd->setCursor(0,1);
  lcd->print(menus[menu_current].text);
}

void Menu::clear(byte line)
{
  for (byte c = 0; c < 16; c++) {
    lcd->setCursor(c, line);
    lcd->print(" ");
  }
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
  }
}

void Menu::showSensor(Sensor *sensor) {
  lcd->clear();
  lcd->print(sensor->name);
  lcd->setCursor(12,0);
  lcd->print(sensor->read());
  lcd->setCursor(0,1);
  lcd->write(byte(0));
  lcd->print(" ");
  lcd->print(sensor->min);
  lcd->setCursor(7,1);
  lcd->write(byte(1));
  lcd->print(" ");
  lcd->print(sensor->max);
}

void Menu::doReset() {
  lcd->clear();
  lcd->print("Reset de Mins");
  lcd->setCursor(0,1);
  lcd->print("e Maximos...");
  ntc1->reset();
  ntc2->reset();
  ntc3->reset();
  lcd->clear();
  lcd->print("Terminado!");
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

void Menu::decode(decode_results result)
{
  switch (result.value)
  {
    case REMOTE_ON:
      if (lcd_backlight) {
        lcd->clear();
        lcd->noBacklight();
        lcd->noDisplay();
        lcd_backlight = false;
      } else {
        lcd->display();
        home();
        lcd_backlight = true;
      }
      break;
    case REMOTE_NEXT:
      next();
      break;
    case REMOTE_PREV:
      prev();
      break;
    case REMOTE_PLAY:
      menu_selected = menu_current;
      exec();
      break;
    case REMOTE_SHUF:
      menu_selected = -1;
      home();
      break;
    case REMOTE_LESS:
      storeMin();
      break;
    case REMOTE_MORE:
      storeMax();
      break;
    case REMOTE_1:
      menu_current = 1;
      menu_selected = 1;
      exec();
      break;
    case REMOTE_2:
      menu_current = 2;
      menu_selected = 2;
      exec();
      break;
    case REMOTE_3:
      menu_current = 3;
      menu_selected = 3;
      exec();
      break;
    case 0xFFFFFFFF:
      // received remote signal unknown
      break;
    default:
      break;
  }
}
