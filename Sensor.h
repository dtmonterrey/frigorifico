#ifndef HEADER_SENSOR
  #define HEADER_SENSOR

#include "Arduino.h"

class Sensor {
  public:
    struct t_sensor {
      char name[15];
      byte min;
      byte max;
    };
};
#endif
