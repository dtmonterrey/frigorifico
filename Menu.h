#ifndef HEADER_MENU
  #define HEADER_MENU

#include "Arduino.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "Remote.h"
#include "Sensor.h"

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
    void decode(decode_results);
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
