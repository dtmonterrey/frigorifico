    #include <Wire.h> 
    #include <LiquidCrystal_I2C.h>
#include <IRremote.h>
#include "Menu.h"
#include "Remote.h"
#include "Sensor.h"
#include "Storage.h"

#define VERSION     0.1

    String menus[MENU_ITEMS];
    int menu_current = 1;
    int menu_selected = -1;

Menu menu;

// LCD
    LiquidCrystal_I2C lcd(0x3F,16,2);
    bool lcd_backlight = true;

// IrDA
IRrecv irda(2);

Sensor::t_sensor ntc1;

void setup()
{
  // menu
  menus[MENU_INFO]     = "0 Informacoes";
  menus[MENU_SENSORS]  = "1 Sondas";
  menus[MENU_DEBUG]    = "* Debug";
  // serial
  Serial.begin(9600);
  // LCD
      lcd.init();
      if (lcd_backlight) lcd.backlight(); else lcd.noBacklight();
  //menuInit();
  // IrDA
  irda.enableIRIn();
  // sensors
  String("Congelacao").toCharArray(ntc1.name, 15);
  ntc1.min = 0;
  ntc1.max = 255;
}

/*
 * Menu
 */
 /*
void menuInit()
{
  lcd.clear();
  lcd.backlight();
  lcd.print("   MAIN MENU");
  lcd.setCursor(0,1);
  menu_current = 1;
  lcd.print(menus[menu_current]); 
}
*/
void menuNext()
{
  menu_current++;
  if (menu_current >= MENU_ITEMS) {
    menu_current = 0;
  }
  lcd.clear();
  lcd.print("   MAIN MENU");
  lcd.setCursor(0,1);
  lcd.print(menus[menu_current]);
}

void menuPrev()
{
  menu_current--;
  if (menu_current < 0) {
    menu_current = MENU_ITEMS - 1;
  }
  lcd.clear();
  lcd.print("   MAIN MENU");
  lcd.setCursor(0,1);
  lcd.print(menus[menu_current]);
}

void menuClear(byte line)
{
  for (byte c = 0; c < 16; c++) {
    lcd.setCursor(c, line);
    lcd.print(" ");
  }
}

void menuPrintValue(unsigned long value, int format)
{
  menuClear(1);
  lcd.setCursor(0,1);
  lcd.print(value, format);
}

void menuPrint(String text)
{
  menuClear(1);
  lcd.setCursor(0,1);
  lcd.print(text);
}

void menuSelect()
{
  menu_selected = menu_current;
  menuShow(menu_selected);
}

void menuShow(int show_menu)
{
  lcd.clear();
  lcd.print(menus[show_menu]);
  switch (show_menu)
  {
    case MENU_INFO:
      menuInfo();
      break;
    case MENU_SENSORS:
      menuSensors();
      break;
    case MENU_DEBUG:
      menuDebug();
      break;
  }
}

void menuInfo()
{
  lcd.clear();
  lcd.print("0 Informacoes");
  lcd.setCursor(0,1);
  lcd.print("Firmware v"+String(VERSION));
}

void menuSensors()
{
  lcd.clear();
  lcd.print("1 Sondas");
  lcd.setCursor(0,1);
  lcd.print("1 "+String(ntc1.name));
}

void menuDebug()
{
  lcd.clear();
  lcd.print("* Debug");
}
/*
void menuDecode(unsigned long value)
{
  switch (value)
  {
    case REMOTE_ON:
      if (lcd_backlight) {
        lcd.clear();
        lcd.noBacklight();
        lcd_backlight = false;
      } else {
        menuInit();
        lcd_backlight = true;
      }
      break;
    case REMOTE_NEXT:
      menuNext();
      break;
    case REMOTE_PREV:
      menuPrev();
      break;
    case REMOTE_PLAY:
      menuSelect();
      break;
    case REMOTE_SHUF:
      menu_selected = -1;
      menuInit();
      break;
    case 0xFFFFFFFF:
      // received remote signal unknown
      break;
    default:
      menuPrintValue(value, HEX);
      break;
  }
}
*/
void loop()
{
  decode_results irda_result;
  
  if (irda.decode(&irda_result)) {
    //menuDecode(irda_result.value);
    menu.decode(irda_result);
    delay(600);
    irda.resume();
  }
}



