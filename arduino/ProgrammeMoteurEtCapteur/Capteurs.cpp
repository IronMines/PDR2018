/*
  Capteurs.cpp - Library for flashing Moteurs code.
  Created by Sébastien PACQUETEAU, May 2, 2018.
  Released into Club Robotique IMT Lille Douai.
*/

#include "Arduino.h"
#include "Capteurs.h"


/*
 * 
 * 
 * Capteur de proximité
 * 
 * 
 */

 
CapteursProxi::CapteursProxi(int pin) :_pinCaptProxi (pin){
  pinMode(_pinCaptProxi, INPUT);
}

bool CapteursProxi::detecteObstacle(){
  return not(digitalRead(_pinCaptProxi));
}

bool CapteursProxi::absenceObstacle(){
  return digitalRead(_pinCaptProxi);
}

/*
 * 
 * 
 * Codeur
 * 
 * 
 */



Codeur::Codeur(int pinA, int pinB) : _pinCodeurA (pinA), _pinCodeurB (pinB) {
  pinMode(_pinCodeurA, INPUT);
  pinMode(_pinCodeurB, INPUT);
}

int Codeur::vitesse (){
  /* 
   *  
   *  La vitesse du moteur est proportionnelle à la fréquence des impulsions ... il faut trouver un moyenne de mesure la fréquence des impulsions sur un pin
   *  et le décalage entre les deux pins nous donne le sens de rotation (à voire si on en a besoin ^^ )
   *  
   */
   return 0;
}

