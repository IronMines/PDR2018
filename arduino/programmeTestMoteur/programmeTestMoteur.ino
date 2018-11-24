#include <SPI.h>


const int pinDirA = 12;
const int pinDirB = 13; 
const int pinPwmA = 3;
const int pinPwmB = 11;
const int pinBrakeA = 9;
const int pinBrakeB = 8;

const int motorSpeed = 200;
const int stepsDelay = 500;

void setup() {
  //Initialize serial and wait for port to open:
  //Put motor shield pins as output
  pinMode(pinDirA, OUTPUT);
  pinMode(pinPwmA, OUTPUT);
  pinMode(pinBrakeA, OUTPUT);
  pinMode(pinDirB, OUTPUT);
  pinMode(pinPwmB, OUTPUT);
  pinMode(pinBrakeB, OUTPUT);
  brake();
  
  Serial.begin(9600);

}


void loop() {
  goDown();
  delay(1000);
  //goUp();
  delay(1000);
}




void goDown(void) {
  motorAforward();
  motorBforward();
  delay(stepsDelay);
  Serial.println("avancer");
  brake();
}

void goUp(void) {
  motorBbackward();
  motorBbackward();
  delay(stepsDelay);
  Serial.println("reculer");
  brake();
}

void goLeft(void) {
  motorAforward();
  motorBbackward();
  delay(2*stepsDelay);
  brake();
}

void goRight(void) {
  motorBforward();
  motorAbackward();
  delay(2*stepsDelay);
  brake();
}

void motorAforward(void) {
  digitalWrite(pinDirA, HIGH); //Establishes forward direction of Channel A
  digitalWrite(pinBrakeA, LOW);   //Disengage the Brake for Channel A
  analogWrite(pinPwmA, motorSpeed);   //Spins the motor on Channel A at full motorSpeed
}

void motorAbackward(void) {
  digitalWrite(pinDirA, LOW); //Establishes forward direction of Channel A
  digitalWrite(pinBrakeA, LOW);   //Disengage the Brake for Channel A
  analogWrite(pinPwmA, motorSpeed);   //Spins the motor on Channel A at full motorSpeed
}

void motorBforward(void) {
  digitalWrite(pinDirB, LOW); //Establishes forward direction of Channel A
  digitalWrite(pinBrakeB, LOW);   //Disengage the Brake for Channel A
  analogWrite(pinPwmB, motorSpeed);   //Spins the motor on Channel A at full motorSpeed
}

void motorBbackward(void) {
  digitalWrite(pinDirB, HIGH); //Establishes forward direction of Channel A
  digitalWrite(pinBrakeB, LOW);   //Disengage the Brake for Channel A
  analogWrite(pinPwmB, motorSpeed);   //Spins the motor on Channel A at full motorSpeed
}

void brake(void) {
  digitalWrite(pinBrakeA, HIGH);   //Engage the Brake for Channel A
  digitalWrite(pinBrakeB, HIGH);   //Engage the Brake for Channel B
  Serial.println("stop");
}
