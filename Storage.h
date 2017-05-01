#ifndef HEADER_STORAGE
  #define HEADER_STORAGE

#include <EEPROM.h>
#include "Arduino.h"

class Storage {
  public:
    static void clear();
    static void storeInt(int address, int value);
    static int readInt(int address);
};

#endif
