#ifndef CURRENT_SENSOR_H
#define CURRENT_SENSOR_H

#include "EmonLib.h"

class CurrentSensor {
public:
  CurrentSensor();
  void configPin(const float pin);
  double getCurrentRms();

private:
  EnergyMonitor energyMonitor;
  float sensorPin;
};

#endif