#include "Menu.h"

Menu::Menu()
{
  // init LCD
  lcd.init();
  if (lcd_backlight) lcd.backlight(); else lcd.noBacklight();
  // init menus
  menu[MENU_INFO]     = "0 Informacoes";
  menu[MENU_SENSORS]  = "1 Sondas";
  menu[MENU_DEBUG]    = "* Debug";
}

void Menu::init() {
  lcd.clear();
  lcd.backlight();
  lcd.print("   MAIN MENU");
  lcd.setCursor(0,1);
  menu_current = 1;
  lcd.print(menu[menu_current]); 
}

void Menu::next()
{
  menu_current++;
  if (menu_current >= MENU_ITEMS) {
    menu_current = 0;
  }
  lcd.clear();
  lcd.print("   MAIN MENU");
  lcd.setCursor(0,1);
  lcd.print(menu[menu_current]);
}

void Menu::decode(decode_results result)
{
  switch (result.value)
  {
    case REMOTE_ON:
      if (lcd_backlight) {
        lcd.clear();
        lcd.noBacklight();
        lcd_backlight = false;
      } else {
        init();
        lcd_backlight = true;
      }
      break;
    case REMOTE_NEXT:
      //menuNext();
      break;
    case REMOTE_PREV:
      //menuPrev();
      break;
    case REMOTE_PLAY:
      //menuSelect();
      break;
    case REMOTE_SHUF:
      menu_selected = -1;
      init();
      break;
    case 0xFFFFFFFF:
      // received remote signal unknown
      break;
    default:
      //menuPrintValue(value, HEX);
      break;
  }
}
