/*
  GyroAndAccelerometer.h - Library for flashing Moteurs code.
  Created by S�bastien PACQUETEAU, May 2, 2018.
  Released into Club Robotique IMT Lille Douai.
*/
#ifndef GyroAndAccelerometer_h
#define GyroAndAccelerometer_h

#include "Arduino.h"
#include "SparkFunLSM6DS3.h"

class GyroAndAccelerometer
{
  public:
	GyroAndAccelerometer();
	int getTetaZ();
	float getTetaPointZ();
	float getAccX();
	float getAccY();

	void update();// met a jour les variables du capteur du robot
	void init();//initialise l'erreur d'offset de chaque axe utile du capteur
	void reInit();// r�initialise les variables du capteur du robot


  private:

	void updateTetaZ(float t);
	void updateTetaPointZ();
	void updateAccX();
	void updateAccY();
	LSM6DS3 myIMU;
	int tetaZ; //l'angle actuel par rapport � la position initial suivant Z
	float tetaPointZ;
	float accX; //L'acc�l�ration suivant X
	float accY; //L'acc�l�ration suivant Y
	float time; // le temps depuis le pr�c�dant appel

	/*
	 * Les valeurs correctifs (pour supprimer les valeurs d�tecter par l'acc�l�ration
	 */

	float tetaPointZInit;
	float accXInit;
	float accYInit;
};

#endif
