/*
  Moteurs.h - Library for flashing Moteurs code.
  Created by Sébastien PACQUETEAU, May 2, 2018.
  Released into Club Robotique IMT Lille Douai.
*/
#ifndef Moteurs_h
#define Moteurs_h

#include "Arduino.h"

class Moteurs
{
  public:
    Moteurs(int motorSpeed);
    void reculer();
    void avancer();
    void moteurDeDroiteRecule();
    void moteurDeDroiteAvance();
    void moteurDeGaucheAvance();
    void moteurDeGaucheRecule();
    void arretMoteurDeDroite();
    void arretMoteurDeGauche();
    void arretDesMoteurs();

  private:
    const int _pinDirMoteurDeDroite;
    const int _pinDirMoteurDeGauche;
    const int _pinPwmMoteurDeDroite;
    const int _pinPwmMoteurDeGauche;
    const int _pinBlockageMoteurDeDroite;
    const int _pinBlockageMoteurDeGauche;
    int _moteurSpeed;
};

#endif
