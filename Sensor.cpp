#include "Sensor.h"

Sensor::Sensor(int id, String name) {
  this->id = id;
  this->name = name;
  this->min = Storage::readInt(4*this->id);
  this->max = Storage::readInt(4*this->id+2);
}

int Sensor::read() {
  return random(0,1024);
}

void Sensor::storeMin(int value) {
  if (this->max > value) {
    Storage::storeInt(4*this->id, value);
    this->min = value;
  }
}

void Sensor::storeMax(int value) {
  if (value > this->min) {
    Storage::storeInt(4*this->id+2, value);
    this->max = value;
  }
}

void Sensor::reset() {
  storeMin(0);
  storeMax(1024);
}

