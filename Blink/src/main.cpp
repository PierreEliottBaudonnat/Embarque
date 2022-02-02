#include <Arduino.h>


const byte TRIGGER_PIN = 2; // Broche TRIGGER
const byte ECHO_PIN = 3;    // Broche ECHO
 
/* Vitesse du son dans l'air en mm/microsecondes */
const float SOUND_SPEED = 340.0 / 1000;
 
void setup() {
  /* Initialise le port serie */
  Serial.begin(9600);
  /* Initialise les broches */
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); // La broche TRIGGER doit etre LOW au repos
  pinMode(ECHO_PIN, INPUT);
}
 
void loop() {
 
  /* Mesure de distance avec une impulsion HIGH sur la broche TRIGGER */
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  /* Mesure du temps entre l'envoi de l'impulsion et sa réception */
  long measure = pulseIn(ECHO_PIN, HIGH);
 
  /* Calcule la distance grâce au temps mesuré */
  float distance = measure / 2.0 * SOUND_SPEED;
 
  if(distance/1000 < 0.10){
    Serial.println(distance / 1000.0, 2); 
    Serial.print("Vous êtes à moins de 10cm d'un obstacle, il faut s'arrêter"); // si un obstacle est à moins de 10cm, on change de direction
  }
  else{
    Serial.println(distance / 1000.0, 2);
    Serial.print("Vous pouvez continuer en ligne droite !"); // sinon, on va tout droit
  }
 
  /* Délai d'attente pour ne pas trop afficher de résultats */
  delay(500);
}