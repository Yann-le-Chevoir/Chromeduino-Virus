#include "Virus.h"

void EV3_master::init()
{
  Serial.begin(9600);
}

void EV3_master::setMotorSpeed(uint8_t motor, uint8_t speed)
{
  uint8_t wBuffer[] = {motor, speed};
  Serial.write(wBuffer, sizeof(wBuffer));
}
