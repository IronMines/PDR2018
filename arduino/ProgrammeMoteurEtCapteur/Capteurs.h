/*
  Capteurs.h - Library for flashing Moteurs code.
  Created by Sébastien PACQUETEAU, May 2, 2018.
  Released into Club Robotique IMT Lille Douai.
*/
#ifndef Capteurs_h
#define Capteurs_h

#include "Arduino.h"

class CapteursProxi
{
  public:
  CapteursProxi(int pin);
  bool CapteursProxi::detecteObstacle();
  bool CapteursProxi::absenceObstacle();
  private:
  int _pinCaptProxi;
};

class Codeur
{
  public:
  Codeur(int pinA, int pinB);
  int Codeur::vitesse ();
  private:
  int _pinCodeurA;
  int _pinCodeurB;
  
};

#endif
