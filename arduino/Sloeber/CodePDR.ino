#include "Capteur.h"
#include "Moteur.h"
#include "BaseRoulante.h"
#include "StrategieDeplacement.h"
#include "GyroAndAccelerometer.h"




//pour le moteur :
//moteur de droite : moteur A
//moteur de gauche : moteur B
const unsigned char vitesseMoteurMax = 200;
const unsigned char vitesseMoteurMin = 150;

const unsigned char dirMotGauche = 12;
const unsigned char pwmMotGauche = 3;
const unsigned char blockageMotGauche = 9;
const unsigned char codeurAMotGauche = 18;

const unsigned char dirMotDroit = 13;
const unsigned char pwmMotDroit = 11;
const unsigned char blockageMotDroit = 8;
const unsigned char codeurAMotDroit = 19;

//Vue de face du robot
Moteur moteurGauche(vitesseMoteurMax, vitesseMoteurMin, dirMotGauche, pwmMotGauche, blockageMotGauche, codeurAMotGauche);
Moteur moteurDroit(vitesseMoteurMax, vitesseMoteurMin, dirMotDroit, pwmMotDroit, blockageMotDroit, codeurAMotDroit);


//pour les capteurs de proximité
CapteurProxi capteurProxiAvantDeDroite (52);
CapteurProxi capteurProxiAvantDeGauche (50);
//CapteursProxi capteurProxiDroite (48);
//CapteursProxi capteurProxiGauche (46);
//CapteursProxi capteurProxiArriere (44);


GyroAndAccelerometer gyroEtAcc = GyroAndAccelerometer();


BaseRoulante baseRoulante = BaseRoulante(&moteurDroit, &moteurGauche, &capteurProxiAvantDeDroite, &capteurProxiAvantDeGauche, &gyroEtAcc);



//Signature
void initInterrupt();
void interruptAD();
void interruptAG();
//void interruptBD();
//void interruptBG();

unsigned long lastUpdate;

StrategieDeplacement strDepla = StrategieDeplacement();
void setup() {
    //initialisation des moteur

    Serial.begin(9600);
    initInterrupt();
    
    lastUpdate = millis();
    
    gyroEtAcc.init();
    
    baseRoulante.applyStrat(&strDepla);
    

}


void loop() {
    
    
    moteurDroit.update();
    moteurGauche.update();
    
    gyroEtAcc.update();
    
    baseRoulante.update();
    
    
    
    if(baseRoulante.getEtat() != 5 && millis() - lastUpdate >= 1000)
    {
        lastUpdate = millis();
        /*Serial.print("Etat BaseRoulante: ");
        Serial.println(baseRoulante.getEtat());
        Serial.print("Moteur Droit status: ");
        Serial.println(moteurDroit.getCodeurRemain());
        Serial.print("Moteur Gauche status: ");
        Serial.println(moteurGauche.getCodeurRemain());*/
        if(baseRoulante.getEtat()==WAIT_START)
        {
            baseRoulante.start();
        }
    }
}


/*
 * Implémentation des signatures
 */
void initInterrupt()
{
    Serial.write("Initialisation des interrupts\n");

    pinMode(codeurAMotGauche, INPUT);
    pinMode(codeurAMotDroit, INPUT);

    attachInterrupt(digitalPinToInterrupt(codeurAMotGauche), interruptAG, FALLING);
    attachInterrupt(digitalPinToInterrupt(codeurAMotDroit), interruptAD, FALLING);
}

void interruptAD(){
    moteurDroit.interruptCodeurA();
}

void interruptAG(){
    moteurGauche.interruptCodeurA();
}
