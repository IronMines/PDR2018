/*
  Moteur.cpp - Library for flashing Moteur code.
  Created by Sébastien PACQUETEAU, May 2, 2018.
  Released into Club Robotique IMT Lille Douai.
*/

#include "Arduino.h"
#include "Moteur.h"

Moteur::Moteur(unsigned char _vitesseMax, unsigned char _vitesseMin, char _pinDirMoteur, char _pinPwmMoteur, char _pinBlockageMoteur, char _pinCodeurA)
    : vitesseMax(_vitesseMax), vitesseMin(_vitesseMin), pinDir(_pinDirMoteur) ,pinPwm(_pinPwmMoteur), pinBlockage(_pinBlockageMoteur), pinCodeurA(_pinCodeurA),
      codeurInit(0L), codeurRemain(0L), vitesse(0), isStop(false), isAvance(false)
{
    pinMode(this->pinDir, OUTPUT);
    pinMode(this->pinPwm, OUTPUT);
    pinMode(this->pinBlockage, OUTPUT);
    pinMode(this->pinCodeurA, INPUT_PULLUP);
    this->setAvance(true);
}

void Moteur::reculer(long limiteCodeur) {
    this->vitesse = this->calculeVitesse();
    this->setDir();
    digitalWrite(this->pinBlockage, LOW);   //On enlève le blockage du moteur
    analogWrite(this->pinPwm, this->vitesse);   //On fait tourner le moteur a _Moteurpeed/255 pourcent de la vitesse maximum du moteur
    this->codeurRemain = limiteCodeur;
    this->codeurInit = limiteCodeur;
}

void Moteur::avancerNTour(char n)
{
    this->avancer(ENCODEUR_RESOLUTION * n);
}


void Moteur::avancer(long limiteCodeur) {
    if(limiteCodeur<0)
    {
        this->setAvance(false);
    }
    else
    {
        this->setAvance(true);
    }
    
    limiteCodeur = abs(limiteCodeur);
    
    this->vitesse = this->calculeVitesse();
    digitalWrite(this->pinBlockage, LOW);   //On enlève le blockage du moteur
    analogWrite(this->pinPwm, this->vitesse);   //On fait tourner le moteur a _Moteurpeed/255 pourcent de la vitesse maximum du moteur
    this->codeurRemain = limiteCodeur;
    this->codeurInit = limiteCodeur;
    this->stop();
    this->reprendre();
}

void Moteur::stop()
{
    isStop = true;
    digitalWrite(this->pinBlockage, HIGH);   //Active le blockage de la roue
    analogWrite(this->pinPwm, 0);
}

void Moteur::reprendre(){
    isStop = false;
    digitalWrite(this->pinBlockage, LOW);
    if(this->codeurRemain!=0)
        analogWrite(this->pinPwm, this->vitesseMax);
}

void Moteur::arret() {
    digitalWrite(this->pinBlockage, HIGH);   //Active le blockage de la roue
    analogWrite(this->pinPwm, 0);
    this->codeurRemain=0L;
}

void Moteur::interruptCodeurA()
{
    this->codeurRemain--;
}
/*
void Moteur::interruptCodeurB()
{
    //codeurRemain--;
}
*/
void Moteur::update(){
    if(this->codeurRemain>=16000000L)
    {
        this->codeurRemain=0L;
    }
    if(this->codeurRemain < 0L)
    {
        this->arret();
        this->codeurRemain = 0L;
    }
    else
    {
        if(!this->isStop && this->vitesse != this->calculeVitesse())
        {
            this->vitesse = this->calculeVitesse();
            digitalWrite(this->pinBlockage, LOW);
            analogWrite(this->pinPwm, this->vitesse);
        }
    }
}

unsigned char Moteur::calculeVitesse()
{
    if(this->codeurInit==0L)
        return 0;
    
    float coef = ((float)this->codeurRemain)/((float)ENCODEUR_RESOLUTION);   //entre 0 et beaucoup;
    coef = (coef>=1.0f)?1.0f:coef;
    coef = (coef<=0.0f)?0.0f:coef;
    unsigned char spd = (unsigned char)(coef*this->vitesseMax);
    return (spd<this->vitesseMin)?this->vitesseMin:spd;
}


void Moteur::setVitesseMax(int _vitesseMax)
{
    this->vitesseMax = _vitesseMax;
}

bool Moteur::haveFinish()
{
    return (this->codeurInit!=this->codeurRemain)&&(this->codeurInit!=0L)&&(this->codeurRemain<=1L);
}

long Moteur::getCodeurRemain()
{
    return this->codeurRemain;
}

long Moteur::getEncodeurResolution()
{
    return ENCODEUR_RESOLUTION;
}

void Moteur::setAvance(bool mode)
{
    this->isAvance=mode;
    this->setDir();
}

void Moteur::setDir()
{
    if(!this->isAvance)
    {
        digitalWrite(pinDir, LOW);
    }
    else
    {
        digitalWrite(pinDir, HIGH);
    }
}
