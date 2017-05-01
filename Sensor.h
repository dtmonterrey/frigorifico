#ifndef HEADER_SENSOR
  #define HEADER_SENSOR

#include "Arduino.h"
#include "Storage.h"

class Sensor {
  public:
    Sensor(int id, String name);
    byte id;
    String name;
    int min;
    int max;
    int read();
    void storeMin(int);
    void storeMax(int);
    void reset();
};
#endif
