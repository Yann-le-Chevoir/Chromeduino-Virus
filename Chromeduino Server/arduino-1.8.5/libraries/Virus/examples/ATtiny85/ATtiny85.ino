#include <Virus.h>

ATtiny85 attiny85;

void setup()
{
  attiny85.init();
}

void loop()
{
  if(attiny85.isButtonPushed())
  {
    //if(!buttonValue) buttonValue = 1;
    attiny85.setColour(0, 255);
    attiny85.setColour(1, 255);
    attiny85.setColour(2, 255);
    delay(100);
  }
  else
  {
    //if(buttonValue) buttonValue = 0;    
    attiny85.setColour(0, 0);
    attiny85.setColour(1, 0);
    attiny85.setColour(2, 0);
    delay(100);
  }
}

/*void onI2CRequest() {
	TinyWire.send(buttonValue);
}*/