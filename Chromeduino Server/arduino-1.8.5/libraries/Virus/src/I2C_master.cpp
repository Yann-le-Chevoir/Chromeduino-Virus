#ifndef __AVR_ATtiny85__

#include "Virus.h"
#include <Wire.h>

void I2C_master::init()
{
  Wire.begin();
}

uint8_t I2C_master::requestFrom(uint8_t address)
{
  Wire.requestFrom(address, (uint8_t) 1);
  return (uint8_t) Wire.read();
}

void I2C_master::sendTo(uint8_t address, uint8_t data)
{
  Wire.beginTransmission(address);
  Wire.write(data);
  Wire.endTransmission();
}

#endif