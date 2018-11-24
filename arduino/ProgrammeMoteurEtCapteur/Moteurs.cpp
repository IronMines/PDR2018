/*
  Moteurs.cpp - Library for flashing Moteurs code.
  Created by Sébastien PACQUETEAU, May 2, 2018.
  Released into Club Robotique IMT Lille Douai.
*/

#include "Arduino.h"
#include "Moteurs.h"

Moteurs::Moteurs(int motorSpeed) :_pinDirMoteurDeDroite(12), _pinDirMoteurDeGauche (13), _pinPwmMoteurDeDroite (3), _pinPwmMoteurDeGauche (11), _pinBlockageMoteurDeDroite (9), _pinBlockageMoteurDeGauche (8), _moteurSpeed (motorSpeed) {
  pinMode(_pinDirMoteurDeDroite, OUTPUT);
  pinMode(_pinPwmMoteurDeDroite, OUTPUT);
  pinMode(_pinBlockageMoteurDeDroite, OUTPUT);
  pinMode(_pinDirMoteurDeGauche, OUTPUT);
  pinMode(_pinPwmMoteurDeGauche, OUTPUT);
  pinMode(_pinBlockageMoteurDeGauche, OUTPUT);

}

void Moteurs::reculer() {
  moteurDeDroiteRecule();
  moteurDeGaucheRecule();
}

void Moteurs::avancer() {
  moteurDeDroiteAvance();
  moteurDeGaucheAvance();
}

void Moteurs::moteurDeDroiteRecule() {
  digitalWrite(_pinDirMoteurDeDroite, HIGH); //On met le sens recule dans la direction du moteur de droite
  digitalWrite(_pinBlockageMoteurDeDroite, LOW);   //On enlève le blockage du moteur de droite
  analogWrite(_pinPwmMoteurDeDroite, _moteurSpeed);   //On fait tourner le moteur a _moteurSpeed/256 pourcent de la vitesse maximum du moteur
}

void Moteurs::moteurDeDroiteAvance() {
  digitalWrite(_pinDirMoteurDeDroite, LOW); //On met le sens avance dans la direction du moteur de droite
  digitalWrite(_pinBlockageMoteurDeDroite, LOW);   //On enlève le blockage du moteur de droite
  analogWrite(_pinPwmMoteurDeDroite, _moteurSpeed);   //On fait tourner le moteur a _moteurSpeed/256 pourcent de la vitesse maximum du moteur
}

void Moteurs::moteurDeGaucheAvance() {
  digitalWrite(_pinDirMoteurDeGauche, HIGH); //On met le sens avance dans la direction du moteur de gauche
  digitalWrite(_pinBlockageMoteurDeGauche, LOW);   //On enlève le blockage du moteur de droite
  analogWrite(_pinPwmMoteurDeGauche, _moteurSpeed);   //On fait tourner le moteur a _moteurSpeed/256 pourcent de la vitesse maximum du moteur
}

void Moteurs::moteurDeGaucheRecule() {
  digitalWrite(_pinDirMoteurDeGauche, LOW); //On met le sens recule dans la direction du moteur de gauche
  digitalWrite(_pinBlockageMoteurDeGauche, LOW);   //On enlève le blockage du moteur de droite
  analogWrite(_pinPwmMoteurDeGauche, _moteurSpeed);   //On fait tourner le moteur a _moteurSpeed/256 pourcent de la vitesse maximum du moteur
}

void Moteurs::arretMoteurDeDroite() {
  digitalWrite(_pinBlockageMoteurDeDroite, HIGH);   //Active le blockage de la roue de droite
}

void Moteurs::arretMoteurDeGauche() {
  digitalWrite(_pinBlockageMoteurDeGauche, HIGH);   //Active le blockage de la roue de gauche
}

void Moteurs::arretDesMoteurs() {
  arretMoteurDeGauche();
  arretMoteurDeDroite();
}
