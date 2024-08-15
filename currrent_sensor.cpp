#include "current_sensor.h"

CurrentSensor::CurrentSensor()
  : sensorPin(A0) {
  configPin(sensorPin);
}

void CurrentSensor::configPin(const float pin) {
  energyMonitor.current(pin, 111.11);
}

double CurrentSensor::getCurrentRms() {
  double iRms = energyMonitor.calcIrms(1480);
  Serial.printf("\nCurrent RMS: %f", iRms);
  return iRms;
}