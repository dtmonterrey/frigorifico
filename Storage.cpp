#include "Storage.h"

void Storage::clear()
{
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.update(i, 0);
  }
}

void Storage::storeInt(int address, int value) {
  Serial.begin(9600);
  Serial.println(address);
  Serial.println(value);
  EEPROM.update(address+1, value);
  value = value >> 8;
  EEPROM.update(address, value);
}

int Storage::readInt(int address) {
  int value = 0;
  byte b0 = EEPROM.read(address);
  value = b0;
  value = value << 8;
  byte b1 = EEPROM.read(address+1);
  return value + b1;
}

