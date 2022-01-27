#include <Arduino.h>
 
const byte TRIGGER_PIN = 2; // Broche TRIGGER
const byte ECHO_PIN = 3;    // Broche ECHO
const byte LED_PIN = 12;  // Broche LED
 
 
/* Vitesse du son dans l'air en mm/microsecondes */
const float SOUND_SPEED = 340.0 / 1000;
 
void setup() {
  /* Initialise le port serie */
  Serial.begin(9600);
  /* Initialise les broches */
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); // La broche TRIGGER doit etre LOW au repos
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
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
  float distance_mm = measure / 2.0 * SOUND_SPEED;
 
  if(distance_mm/1000 < 0.10){ 
    digitalWrite(LED_PIN, HIGH); // si un obstacle est à moins de 10cm, allume la LED
  }
  else{
    digitalWrite(LED_PIN, LOW);
  }
 
  // Affiche des résultats en m 
  Serial.print("Distance: ");
  Serial.println(distance_mm / 1000.0, 2);
  Serial.print("m");
 
 
  /* Délai d'attente pour ne pas trop afficher de résultats */
  delay(500);
}