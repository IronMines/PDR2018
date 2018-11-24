
const int pinCaptProxi = A0;



void setup() {
  // put your setup code here, to run once:
  pinMode(pinCaptProxi, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  // 0 si détection d'obstacle, 1 si rien 
  Serial.println(digitalRead(pinCaptProxi));
}
