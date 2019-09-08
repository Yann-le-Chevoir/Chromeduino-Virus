/***************************************************
 *                                                 *
 *                Bienvenue Virus !                *
 *                                                 *
 *  Voici un exemple de code pour faire clignoter  *
 *  la DEL sur ton Arduino nano (pin 13).          *
 *  Branche ton arduino, appuie sur "Programmer"   *
 *  et observe ce que fait ce code !               *
 *                                                 *
 ***************************************************/

void setup()
{
  pinMode(13, OUTPUT);
}

void loop()
{
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}