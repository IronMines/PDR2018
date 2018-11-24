/*
  GyroAndAccelerometer.cpp - Library for flashing Moteurs code.
  Created by S�bastien PACQUETEAU, May 2, 2018.
  Released into Club Robotique IMT Lille Douai.
*/

#include "GyroAndAccelerometer.h"


GyroAndAccelerometer::GyroAndAccelerometer() :
 myIMU(LSM6DS3( I2C_MODE, 0x6A )),tetaZ(0), tetaPointZ(0.0f), accX(0.0f), accY(0.0f), time (millis()*0.001),tetaPointZInit(0.0f),accXInit(0.0f),accYInit(0.0f)
{


}


/*
 *
 * Les getter
 *
 */

void GyroAndAccelerometer::init(){
	if( myIMU.begin() != 0 )
			  {
				  Serial.println("Device error");
			  }
			  else
			  {
			      Serial.println("Device OK!");
			  }
	this->tetaPointZInit = this->myIMU.readFloatGyroZ();
	this->accXInit = this->myIMU.readFloatAccelX();
	this->accYInit = this->myIMU.readFloatAccelY();
}


int GyroAndAccelerometer::getTetaZ()
{
	return tetaZ;
}
float GyroAndAccelerometer::getTetaPointZ()
{
	return tetaPointZ;
}

float GyroAndAccelerometer::getAccX()
{
	return accX;
}

float GyroAndAccelerometer::getAccY()
{
	return accY;
}

/*
 *
 * Les fonctions de mise a jours des variables du capteur
 *
 */

// met a jour les variables du capteur du robot
void GyroAndAccelerometer::update()
{
	float t = millis()*0.001;// si on a besoin d'int�grer les variables temporelles dans plusieurs fonctions ...
	this->updateTetaPointZ();
	this->updateTetaZ(t); // on appelle la mise a jour de l'angle du robot
	this->updateAccX(); // on appelle la mise a jour de l'angle du robot
	this->updateAccY(); // on appelle la mise a jour de l'angle du robot
	time = t;
}


void GyroAndAccelerometer::updateTetaZ(float t)
{
	//la biblioth�que SparkFun renvoit la vitesse angulaire suivant Z et on veut la position ... on int�gre
	// Remarque il faut faire attention, la vitesse angulaire n'est pas nul quand le robot est � l'arr�t !!!
	float dTetaZ=this->getTetaPointZ(); //on mesure une premiere fois la dZ/dt
	int tmp = dTetaZ * (t - time);
	tetaZ += static_cast<int>(tmp);

}

void GyroAndAccelerometer::updateTetaPointZ()
{
	//il faudra ajouter un correctif, histoire d'�tre sur que la valeur en acc�l�ration est nulle � l'arr�t ^^
	tetaPointZ = myIMU.readFloatGyroZ()-tetaPointZInit;
}

void GyroAndAccelerometer::updateAccX()
{
	//il faudra ajouter un correctif, histoire d'�tre sur que la valeur en acc�l�ration est nulle � l'arr�t ^^
	accX = myIMU.readFloatAccelX()-accXInit;
}

void GyroAndAccelerometer::updateAccY()
{
	//il faudra ajouter un correctif, histoire d'�tre sur que la valeur en acc�l�ration est nulle � l'arr�t ^^
	accY = myIMU.readFloatAccelY()-accYInit;
}




// r�initialise les variables du capteur du robot
void GyroAndAccelerometer::reInit()
{
	tetaZ = 0;
}




