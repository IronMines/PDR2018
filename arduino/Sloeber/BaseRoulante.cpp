/*
 * BaseRoulante.cpp
 *
 *  Created on: 14 mai 2018
 *      Author: william
 */

#include "BaseRoulante.h"

BaseRoulante::BaseRoulante(Moteur *_moteurDroit, Moteur *_moteurGauche, CapteurProxi *_capteurProxiAVDroit, CapteurProxi *_capteurProxiAVGauche, GyroAndAccelerometer *_gyroEtAcc) : 
    moteurDroit(_moteurDroit), moteurGauche(_moteurGauche),
    capteurProxiAVDroit(_capteurProxiAVDroit), capteurProxiAVGauche(_capteurProxiAVGauche),
    stratDeplacement(), timeDebut(millis()), timeDelayWant(0), etat(WAIT_START),
    posX(0), posY(0), vitesseMax(120), toCheck(0), gyroEtAcc(_gyroEtAcc), rotVoulue(0), valeur(0)
{
    this->moteurDroit->stop();
    this->moteurGauche->stop();
}



void BaseRoulante::applyStrat(StrategieDeplacement *_stratDepla)
{
    this->stratDeplacement = _stratDepla;
}


void BaseRoulante::update()
{
    switch(this->etat)
    {
    case WAIT_START:
        break;
        
    case EXECUTE_ACTION:
        this->execNextAction();
        this->stratDeplacement->nextAction();
        break;
        
    case WAIT_WHILE_EXEC:
        if(this->verifActionCondition()==true)
        {
            this->etat = EXECUTE_ACTION;
            this->moteurDroit->arret();
            this->moteurGauche->arret();
        }
        else
        {
            this->checkCapteur();
        }
        break;
        
    case EXEC_INTERRUPT:
        this->checkCapteur();
        break;
        
    case ON_PAUSE:
        
        break;
    case RESUME:
        this->etat = EXEC_INTERRUPT;
        break;
    
    case STOPPED:
        return;
        break;
        
    default:
        this->etat = STOPPED;
        break;
    }
}

void BaseRoulante::pause(){
    this->etat = ON_PAUSE;
}

void BaseRoulante::start(){
    this->etat = EXECUTE_ACTION;
}

void BaseRoulante::resume()
{
    this->etat = RESUME;
}

void BaseRoulante::stop(){
    this->etat = STOPPED;
}

void BaseRoulante::execNextAction(){
    char* action  = this->stratDeplacement->getAction();
    
    memcpy(&ordre, action, 4);
    valeur = atoi(action+5);
    
    
    if(strcmp(ordre, "MVTC")==0)
    {
        this->avancerNCodeur(valeur);
        this->toCheck = 1;
        this->etat = WAIT_WHILE_EXEC;
    }
    else if(strcmp(ordre, "MVTN")==0)
    {
        this->avancerNCodeur(valeur*moteurDroit->getEncodeurResolution());
        this->toCheck = 1;
        this->etat = WAIT_WHILE_EXEC;
    }
    else if(strcmp(ordre, "ROTA")==0)
    {
        this->rotVoulue = valeur;
        
        this->gyroEtAcc->reInit();
        //Serial.print("Rotation voulue: ");
        //Serial.println((float)this->LARGEUR_ROBOT/(float)this->DIAMETRE_ROUE);
        float nbTick = ((float)this->moteurDroit->getEncodeurResolution()/(360))*((float)this->LARGEUR_ROBOT/(float)this->DIAMETRE_ROUE)*abs(this->rotVoulue);
        nbTick *= 1.6f;
        //Serial.print("Nombre de tick demande: ");
        //Serial.println(nbTick);
        
        //nbTick += 100;
        
        if(this->rotVoulue > 0)
        {
            this->moteurDroit->avancer(floor(nbTick));
            this->moteurGauche->avancer(floor(-nbTick));
        }
        else
        {
            this->moteurDroit->avancer(floor(-nbTick));
            this->moteurGauche->avancer(floor(nbTick));
        }
        
        this->rotVoulue=abs(this->rotVoulue);
        
        this->toCheck = 3;
        this->etat = WAIT_WHILE_EXEC;

    }
    else if(strcmp(ordre, "DELA")==0)
    {
        this->timeDebut = millis();
        this->timeDelayWant = valeur;
        /*Serial.print("Debut wait temps: ");
        Serial.println(this->timeDebut);
        Serial.println(this->timeDelayWant);*/
        this->toCheck = 2;
        this->etat = WAIT_WHILE_EXEC;
    }
    else if(strcmp(ordre, "CHAN")==0)
    {
        this->etat=STOPPED;
    }
}

void BaseRoulante::checkCapteur(){
    if(capteurProxiAVDroit->detecteObstacle() || capteurProxiAVGauche->detecteObstacle())
    {
        this->etat = EXEC_INTERRUPT;
        this->moteurDroit->stop();
        this->moteurGauche->stop();
    }
    else
    {
        if(this->etat == EXEC_INTERRUPT)
        {
            this->moteurDroit->reprendre();
            this->moteurGauche->reprendre();
            this->etat = WAIT_WHILE_EXEC;
        }
     }
}

unsigned char BaseRoulante::getEtat()
{
    return this->etat;
}

void BaseRoulante::avancerNCodeur(int nCodeur)
{
    this->moteurDroit->avancer(nCodeur);
    this->moteurGauche->avancer(nCodeur);
}



/*
 * Fonctions de verification de la fin d'une action
 */


bool BaseRoulante::verifActionCondition()
{
    switch(this->toCheck)
    {
    case 1:
        return this->checkMot();
    case 2:
        return this->checkDelay();
    case 3:
        return this->checkRotation();
    default:
        return true;
    }
}


bool BaseRoulante::checkMot()
{
    /*Serial.print("haveFinish && haveFinish: ");
    Serial.println(moteurDroit->haveFinish()&&moteurGauche->haveFinish());*/
    return moteurDroit->haveFinish()&&moteurGauche->haveFinish();
}

bool BaseRoulante::checkDelay()
{
    /*Serial.print("CheckDelay: ");
    Serial.println((millis()-this->timeDebut)>=this->timeDelayWant);*/
    return (millis()-this->timeDebut)>=this->timeDelayWant;
}

bool BaseRoulante::checkRotation()
{
    /*Serial.print("CheckRotation Delta: ");
    Serial.println(this->rotVoulue-abs(gyroEtAcc->getTetaZ()) || checkMot());*/
    return this->rotVoulue-abs(gyroEtAcc->getTetaZ())<=5 || checkMot();
}


