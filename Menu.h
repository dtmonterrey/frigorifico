#ifndef HEADER_MENU
  #define HEADER_MENU

#include "Arduino.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "Remote.h"

#define MENU_INFO     0
#define MENU_SENSORS  1
#define MENU_DEBUG    2
#define MENU_ITEMS    3

class Menu {
  public:
    Menu();
    void init();
    void next();
    void decode(decode_results);
  private:
    String menu[MENU_ITEMS];
    int menu_current = 1;
    int menu_selected = -1;
    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3F,16,2);
    bool lcd_backlight = true;
};

#endif
