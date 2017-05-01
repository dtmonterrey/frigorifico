#include <IRremote.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "Menu.h"
#include "Remote.h"
#include "Sensor.h"
#include "Storage.h"

#define VERSION     0.1

IRrecv irda(2);
Menu *menu = NULL;
unsigned long lcd_update_previous = 0;
unsigned long lcd_update_current = 0;

void setup()
{
  irda.enableIRIn();
  menu = new Menu();
  menu->home();
}

void loop()
{
  decode_results irda_result;
  
  if (irda.decode(&irda_result)) {
    menu->decode(irda_result);
    delay(600);
    irda.resume();
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



