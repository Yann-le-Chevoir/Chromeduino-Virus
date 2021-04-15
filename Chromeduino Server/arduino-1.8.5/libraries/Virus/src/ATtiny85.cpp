#include "Virus.h"
#ifdef __AVR_ATtiny85__
//#include <TinyWire.h>
#endif

#define LIMIT_SWITCH 900

#ifdef __AVR_ATtiny85__
#define OUTPUT_0 1
#define OUTPUT_1 3
#define OUTPUT_2 4
#define INPUT_0 0
volatile uint8_t* Port[] = {&OCR1B, &OCR0B, &OCR1A};
#else
#define OUTPUT_0 9
#define OUTPUT_1 10
#define OUTPUT_2 11
#define INPUT_0 0
uint8_t Port[] = {OUTPUT_0, OUTPUT_1, OUTPUT_2};
#endif

void ATtiny85::init()
{
	//TinyWire.begin(10);
	//TinyWire.onRequest(onI2CRequest);

  pinMode(OUTPUT_0, OUTPUT);
  pinMode(OUTPUT_1, OUTPUT);
  pinMode(OUTPUT_2, OUTPUT);
  
#ifdef __AVR_ATtiny85__
  // Configure counter/timer0 for fast PWM on PB0 and PB1
  TCCR0A = 3<<COM0A0 | 3<<COM0B0 | 3<<WGM00;
  TCCR0B = 0<<WGM02 | 3<<CS00; // Optional; already set
  // Configure counter/timer1 for fast PWM on PB4
  TCCR1 = 1<<CTC1 | 1<<PWM1A | 3<<COM1A0 | 7<<CS10;
  GTCCR = 1<<PWM1B | 3<<COM1B0;
  // Interrupts on OC1A match and overflow
  TIMSK = TIMSK | 1<<OCIE1A | 1<<TOIE1;
#endif

  setOutput(0, 0);
  setOutput(1, 0);
  setOutput(2, 0);
}

#ifdef __AVR_ATtiny85__
ISR(TIMER1_COMPA_vect)
{
  if (!bitRead(TIFR,TOV1)) bitSet(PORTB, 3);
}

ISR(TIMER1_OVF_vect)
{
  bitClear(PORTB, 3);
}
#endif

void ATtiny85::setColour(int colour, int intensity)
{
  uint8_t value = 0;
  if(intensity >= 255)
  {
    value = 255;
  }
  else
  {
    value = intensity/2;
  }
  setOutput(colour, value);
}

void ATtiny85::setOutput(int output, int intensity)
{  
#ifdef __AVR_ATtiny85__
  *Port[output] = 255-intensity;
#else
  analogWrite(Port[output], intensity);
#endif
}

boolean ATtiny85::isButtonPushed()
{
  return analogRead(INPUT_0) > LIMIT_SWITCH;
}
