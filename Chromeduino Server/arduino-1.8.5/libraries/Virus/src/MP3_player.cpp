#include "Virus.h"

# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]

void MP3_player::init(uint8_t rxPin, uint8_t txPin)
{
  volume = 15;
  _isPlaying = false;  
  
  mySerial = new SoftwareSerial(rxPin, txPin);
  mySerial->begin (9600);
  delay(1000);
  execute_CMD(0x3F, 0, 0);
  delay(500);
  execute_CMD(0x06, 0, volume);
  delay(500);
}

boolean MP3_player::isPlaying()
{
  return _isPlaying;
}

void MP3_player::pause()
{
  execute_CMD(0x0E,0,0);
  delay(500);
  _isPlaying = false;
}

void MP3_player::play()
{
  execute_CMD(0x0D,0,1); 
  delay(500);  
  _isPlaying = true;
}

void MP3_player::playFirst()
{
  execute_CMD(0x11,0,1);
  delay(500);
  _isPlaying = true;
}

void MP3_player::playNext()
{
  execute_CMD(0x01,0,1);
  delay(500);
  _isPlaying = true;
}

void MP3_player::playPrevious()
{
  execute_CMD(0x02,0,1);
  delay(500);
  _isPlaying = true;
}

void MP3_player::playTrack(uint8_t track)
{
  execute_CMD(0x03,0,track);
  delay(500);
  _isPlaying = true;
}

void MP3_player::volumeINC()
{
  volume = volume+1;
  if(volume==31)
  {
    volume=30;
  }
  execute_CMD(0x06, 0, volume);
  delay(500);
}

void MP3_player::volumeDEC()
{
  volume = volume-1;
  if(volume==-1)
  {
    volume=0;
  }
  execute_CMD(0x06, 0, volume);
  delay(500);
}

// Excecute the command and parameters
void MP3_player::execute_CMD(byte CMD, byte Par1, byte Par2)
{
  // Calculate the checksum (2 bytes)
  word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);
  // Build the command line
  byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge, Par1, Par2, highByte(checksum), lowByte(checksum), End_Byte};
  //Send the command line to the module
  for (byte k=0; k<10; k++)
  {
    mySerial->write( Command_line[k]);
  }
}