/*
 * BaseRoulante.h
 *
 *  Created on: 14 mai 2018
 *      Author: william
 */

#ifndef BASEROULANTE_H_
#define BASEROULANTE_H_

#include "Arduino.h"
#include "Capteur.h"
#include "Moteur.h"
#include "StrategieDeplacement.h"
#include "string.h"
#include "GyroAndAccelerometer.h"


#define     WAIT_START          0
#define     EXECUTE_ACTION      1
#define     WAIT_WHILE_EXEC     2
#define     EXEC_INTERRUPT      3
#define     ON_PAUSE            4
#define     STOPPED             5
#define     RESUME              6


class BaseRoulante {
    public:
        BaseRoulante(Moteur *_moteurDroit, Moteur *_moteurGauche, CapteurProxi *_capteurProxiAVDroit, CapteurProxi *_capteurProxiAVG, GyroAndAccelerometer *_gyroEtAcc);
        void update();
        void applyStrat(StrategieDeplacement *_stratDeplacement);
        unsigned char getEtat();
        void start();
        void pause();
        void stop();
        void resume();
        
    private:
        Moteur *moteurDroit;
        Moteur *moteurGauche;
        CapteurProxi *capteurProxiAVDroit;
        CapteurProxi *capteurProxiAVGauche;
        StrategieDeplacement *stratDeplacement;
        GyroAndAccelerometer *gyroEtAcc;
        
        unsigned long timeDebut;
        unsigned long timeDelayWant;
        int rotVoulue;
        unsigned char etat;
        
        unsigned int posX;
        unsigned int posY;
        unsigned char vitesseMax;
        unsigned char toCheck;
        
        int DIAMETRE_ROUE  = 100;    //mm
        int LARGEUR_ROBOT  = 165;    //mm
        
        char ordre[5] = {' ', ' ', ' ', ' ', '\0'};
        int valeur;
        
        void execNextAction();
        void avancerNCodeur(int nCodeur);
        
        bool verifActionCondition();
        void checkCapteur();
        
        bool checkMot();
        bool checkDelay();
        bool checkRotation();
        
};

#endif /* BASEROULANTE_H_ */
