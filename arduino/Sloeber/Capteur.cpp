/*
  Capteurs.cpp - Library for flashing Moteurs code.
  Created by Sébastien PACQUETEAU, May 2, 2018.
  Released into Club Robotique IMT Lille Douai.
*/

#include "Capteur.h"


/*
 * 
 * 
 * Capteur de proximité
 * 
 * 
 */


CapteurProxi::CapteurProxi(int _pin) :
  pin (_pin){
    pinMode(pin, INPUT);
}

bool CapteurProxi::detecteObstacle()
{
    return not(digitalRead(pin));
}

bool CapteurProxi::absenceObstacle()
{
    return digitalRead(pin);
}
