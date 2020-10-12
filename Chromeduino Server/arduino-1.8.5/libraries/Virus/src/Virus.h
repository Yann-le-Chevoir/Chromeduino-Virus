#ifndef VIRUS_h
#define VIRUS_h

#include "Arduino.h"
#include "SoftwareSerial.h"

class MP3_player
{
public:
  void init(uint8_t rxPin, uint8_t txPin);
  void playFirst();
  boolean isPlaying();
  void pause();
  void play();
  void playNext();
  void playPrevious();
  void volumeINC();
  void volumeDEC();
  
private:
  int volume;  
  SoftwareSerial *mySerial;
  boolean _isPlaying;
  void execute_CMD(byte CMD, byte Par1, byte Par2);

};

#endif
