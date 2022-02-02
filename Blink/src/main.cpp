#include <Arduino.h>


const byte TRIGGER_PIN = 2; // Broche TRIGGER
const byte ECHO_PIN = 3;    // Broche ECHO

int MSL = 9; // Micro-switch de gauche
int MSR = 8; // Micro-switch de droite

// Bits pour le moteur A
int MA0 = 10;
int MA1 = 11;

// Bits pour le moteur B
int MB0 = 13;
int MB1 = 12;
 
/* Vitesse du son dans l'air en mm/microsecondes */
const float SOUND_SPEED = 340.0 / 1000;
 
void setup() {
  /* Initialise le port serie */
  Serial.begin(9600);
  /* Initialise les broches */
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); // La broche TRIGGER doit etre LOW au repos
  pinMode(ECHO_PIN, INPUT);
  // INPUTS
  pinMode(MSL, INPUT);
  pinMode(MSR, INPUT);
  
  // OUTPUTS
  pinMode(MA0, OUTPUT);
  pinMode(MA1, OUTPUT);
  pinMode(MB0, OUTPUT);
  pinMode(MB1, OUTPUT);
}

void goForward(){
  // On indique au moteur A de mettre la marche avant
  digitalWrite(MA0, LOW);
  digitalWrite(MA1, HIGH);
  
  // On indique au moteur B de mettre la marche avant
  digitalWrite(MB0, LOW);
  digitalWrite(MB1, HIGH);
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
    Serial.print("Vous êtes à moins de 10cm d'un obstacle, il faut s'arrêter"); // si un obstacle est à moins de 10cm, on change de direction
    //changeDirection();
  }
  else{
    Serial.print("Vous pouvez continuer en ligne droite !"); // sinon, on va tout droit
    goForward();
  }
 
  /* Délai d'attente pour ne pas trop afficher de résultats */
  delay(500);
}