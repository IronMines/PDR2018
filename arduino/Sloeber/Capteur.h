/*
  Capteurs.h - Library for flashing Moteurs code.
  Created by Sébastien PACQUETEAU, May 2, 2018.
  Released into Club Robotique IMT Lille Douai.
*/
#ifndef Capteur_h
#define Capteur_h

#include "Arduino.h"

class CapteurProxi
{
  public:
    CapteurProxi(int _pin);
    bool detecteObstacle();
    bool absenceObstacle();
    
  private:
    char pin;

};


#endif
