#ifndef __AVR_ATtiny85__

#include "Virus.h"

byte TRIGGER_PIN; // Broche TRIGGER
byte ECHO_PIN;    // Broche ECHO

/* Constantes pour le timeout */
//const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s

/* Vitesse du son dans l'air en mm/us */
const float SOUND_SPEED = 340.0 / 1000;

void Ultrason_capteur::init(uint8_t echoPin, uint8_t triggerPin)
{
  TRIGGER_PIN = triggerPin;
  ECHO_PIN = echoPin;
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PIN, INPUT);
}

float Ultrason_capteur::getDistance()
{
  /* 1. Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER */
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  /* 2. Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe) */
  long measure = pulseIn(ECHO_PIN, HIGH/*, MEASURE_TIMEOUT*/);
   
  /* 3. Calcul la distance à partir du temps mesuré */
  float distance_mm = measure / 2.0 * SOUND_SPEED;

  return distance_mm;
}

#endif