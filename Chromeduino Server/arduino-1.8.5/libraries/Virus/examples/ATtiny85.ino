#include <TinyWire.h>

volatile uint8_t* Port[] = {&OCR0B, &OCR1A, &OCR1B};

void setup() {
	TinyWire.begin(10);
	TinyWire.onRequest(onI2CRequest);

  pinMode(1, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  // Configure counter/timer0 for fast PWM on PB0 and PB1
  TCCR0A = 3<<COM0A0 | 3<<COM0B0 | 3<<WGM00;
  TCCR0B = 0<<WGM02 | 3<<CS00; // Optional; already set
  // Configure counter/timer1 for fast PWM on PB4
  TCCR1 = 1<<CTC1 | 1<<PWM1A | 3<<COM1A0 | 7<<CS10;
  GTCCR = 1<<PWM1B | 3<<COM1B0;
  // Interrupts on OC1A match and overflow
  TIMSK = TIMSK | 1<<OCIE1A | 1<<TOIE1;
}

ISR(TIMER1_COMPA_vect) {
  if (!bitRead(TIFR,TOV1)) bitSet(PORTB, 3);
}

ISR(TIMER1_OVF_vect) {
  bitClear(PORTB, 3);
}

void SetColour (int colour, int intensity) {
  *Port[colour] = intensity;
} 

uint8_t buttonValue = 0;
#define LIMIT_SWITCH 900

void loop() {
  if(analogRead(0) < LIMIT_SWITCH)
  {
    if(!buttonValue) buttonValue = 1;
    SetColour (0, 255);
    delay(1000);
    SetColour (0, 0);
    SetColour (1, 255);
    delay(1000);
    SetColour (1, 0);
    SetColour (2, 255);
    delay(1000);
    SetColour (2, 0);
  }
  else
  {
    if(buttonValue) buttonValue = 0;
    delay(100);
  }
}

void onI2CRequest() {
	TinyWire.send(buttonValue);
}
