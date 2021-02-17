#include "Virus.h"

#ifndef __AVR_ATtiny85__

#include <Wire.h>

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

#else

#include <TinyWire.h>

void I2C_slave::init(uint8_t address)
{
  gSendData = 0;
  gReceivedData = 0;
  TinyWire.begin(address);
  TinyWire.onRequest(requestEvent);
  TinyWire.onReceive(receiveEvent);
}

void I2C_slave::setSendData(uint8_t data)
{
  gSendData = data;
}

uint8_t I2C_slave::getReceivedData()
{
  return gReceivedData;
}

static void I2C_slave::requestEvent()
{
  TinyWire.send(gSendData);
}
static void I2C_slave::receiveEvent(int howMany)
{
  gReceivedData = (uint8_t) TinyWire.receive();
}

#endif