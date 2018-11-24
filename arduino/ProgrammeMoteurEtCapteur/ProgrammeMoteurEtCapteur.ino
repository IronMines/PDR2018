//#include <SPI.h>
//Pour l'accéléromètre et le gyroscope 
#include "SparkFunLSM6DS3.h"
#include "Wire.h"
#include "Moteurs.h"
#include "Capteurs.h"

//pour le moteur : 
//moteur de droite : moteur A
//moteur de gauche : moteur B
const int motorSpeed = 200;
Moteurs moteurs(motorSpeed);

//pour les capteurs de proximité
CapteursProxi capteurProxiAvantDeDroite (52);
CapteursProxi capteurProxiAvantDeGauche (50);
//CapteursProxi capteurProxiDroite (48);
//CapteursProxi capteurProxiGauche (46);
//CapteursProxi capteurProxiArriere (44);

//Pour les codeurs des moteurs
/*
Codeur codeurMoteurDroite(29, 27);
Codeur codeurMoteurGauche(33, 31);
*/

//Données 
/*
int accX;
int accY;
int gyrZ;
*/
  

//Pour l'accéléromètre et le gyroscope 
//Create a instance of class LSM6DS3
LSM6DS3 myIMU( I2C_MODE, 0x6A );  //I2C device address 0x6A


bool i=true;

void setup() {
  //initialisation des moteurs 
  moteurs.arretDesMoteurs();
  
  Serial.begin(9600);

}


void loop() {

  if(capteurProxiAvantDeDroite.absenceObstacle() && capteurProxiAvantDeGauche.absenceObstacle() &&i){
    moteurs.avancer();
  }
  else if(capteurProxiAvantDeDroite.detecteObstacle() || capteurProxiAvantDeGauche.detecteObstacle() ){
    moteurs.arretDesMoteurs();
    moteurs.reculer();
    delay(1000);
    moteurs.moteurDeDroiteAvance();
    moteurs.moteurDeGaucheRecule();
    delay(470);
    moteurs.arretDesMoteurs();
    i=false;
  }

}

