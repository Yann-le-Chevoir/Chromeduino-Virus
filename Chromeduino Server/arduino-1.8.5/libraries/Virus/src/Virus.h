#ifndef VIRUS_H
#define VIRUS_H

#include <Arduino.h>

#ifdef __AVR_ATtiny85__

  class ATtiny85
  {
    public:
      void init();
      boolean isButtonPushed();
      void setColour(int colour, int intensity);
      void setOutput(int output, int intensity);
  };

#else //__AVR_ATtiny85__

  #include <SoftwareSerial.h>
  #include <Wire.h>

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
      void playTrack(uint8_t track);
      void volumeINC();
      void volumeDEC();
      
    private:
      int volume;  
      SoftwareSerial *mySerial;
      boolean _isPlaying;
      void execute_CMD(byte CMD, byte Par1, byte Par2);

  };

  class I2C_master
  {
    public:
      void init();
      uint8_t requestFrom(uint8_t address);
      void sendTo(uint8_t address, uint8_t data);
  };


  static uint8_t gSendData;
  static uint8_t gReceivedData;

  class I2C_slave
  {
    public:
      void init(uint8_t address);
      void setSendData(uint8_t data);
      uint8_t getReceivedData();
    private:
      static void requestEvent();
      static void receiveEvent(int howMany);
  };

  class EV3_master
  {
    public:
      void init();
      void setMotorSpeed(uint8_t motor, uint8_t speed);
  };

#endif //__AVR_ATtiny85__

#endif //VIRUS_H
