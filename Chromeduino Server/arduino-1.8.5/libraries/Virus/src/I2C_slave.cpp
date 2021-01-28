#ifndef __AVR_ATtiny85__

#include "Virus.h"

void I2C_slave::init(uint8_t address)
{
  Serial.begin(9600);
  gSendData = 0;
  gReceivedData = 0;
  Wire.begin(address);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}

void I2C_slave::setSendData(uint8_t data)
{
  gSendData = data;
  Serial.println(gSendData);
}

uint8_t I2C_slave::getReceivedData()
{
  Serial.println(gReceivedData);
  return gReceivedData;
}

static void I2C_slave::requestEvent()
{
  Wire.write(gSendData);
}
static void I2C_slave::receiveEvent(int howMany)
{
  gReceivedData = (uint8_t) Wire.read();
}

#endif