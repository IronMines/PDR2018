/*
  Moteurs.h - Library for flashing Moteurs code.
  Created by Sébastien PACQUETEAU, May 2, 2018.
  Released into Club Robotique IMT Lille Douai.
*/
#ifndef Moteur_h
#define Moteur_h

#include "Arduino.h"

class Moteur
{
  public:
    Moteur(unsigned char _vitesseMax, unsigned char _vitesseMin, char _pinDir, char _pinPwm, char _pinBlockage, char _codeurA);
    void reculer(long limiteCodeur);
    void avancer(long limiteCodeur);
    void arret();
    void stop();
    void reprendre();
    void interruptCodeurA();
    void update();
    void setVitesseMax(int _vitesseMax);
    void avancerNTour(char n);
    bool haveFinish();
    long getCodeurRemain();
    long getEncodeurResolution();
    void setAvance(bool mode);

    
  private:
    unsigned char vitesseMax;
    unsigned char vitesseMin;
    char pinDir;
    char pinPwm;
    char pinBlockage;
    char pinCodeurA;
    const long ENCODEUR_RESOLUTION = 860;
    long codeurInit;
    long codeurRemain;
    unsigned char vitesse;
    bool isStop;
    bool isAvance;
    
    unsigned char calculeVitesse();
    void setDir();

};

#endif
