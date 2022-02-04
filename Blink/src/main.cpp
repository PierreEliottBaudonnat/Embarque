#include <Arduino.h>


const byte TRIGGER_PIN = 2; // Broche TRIGGER
const byte ECHO_PIN = 3;    // Broche ECHO

// Bits pour le moteur A
int MA0 = 10;
int MA1 = 11;

// Bits pour le moteur B
int MB0 = 13;
int MB1 = 12;

long randomNumber;  // Nombre random pour choisir de partir à droite ou à gauche
 
/* Vitesse du son dans l'air en mm/microsecondes */
const float SOUND_SPEED = 340.0 / 1000;
 
void setup() {
  /* Initialise le port serie */
  Serial.begin(9600);
  /* Initialise les broches */
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); // La broche TRIGGER doit etre LOW au repos
  pinMode(ECHO_PIN, INPUT);
  
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

  // Il n'y a pas de delay, la roue tourne infiniement tant qu'elle ne rencontre pas d'obstacle
}

void stop(){
  // On indique au moteur A de se stopper
  digitalWrite(MA0, LOW);
  digitalWrite(MA1, LOW);
  
  // On indique au moteur B de se stopper
  digitalWrite(MB0, LOW);
  digitalWrite(MB1, LOW);

  // On se stoppe pendant une demi-seconde
  delay(500);
}

void goBackward(){
  // On indique au moteur A de faire marche arrière
  digitalWrite(MA0, HIGH);
  digitalWrite(MA1, LOW);
  
  // On indique au moteur B de faire marche arrière
  digitalWrite(MB0, HIGH);
  digitalWrite(MB1, LOW); 

  // On fait marche arrière pendant une seconde et demi
  delay(1500);
}

void turnOnTheLeft(){
  // Le moteur A fait la marche avant
  digitalWrite(MA0, LOW);
  digitalWrite(MA1, HIGH);
  
  // Le moteur B fait la marche arrière
  digitalWrite(MB0, HIGH);
  digitalWrite(MB1, LOW);
  
  // On tourne sur la gauche pendant une seconde
  delay(1000);
}

void turnOnTheRight(){
  // Le moteur A fait la marche arrière
  digitalWrite(MA0, HIGH);
  digitalWrite(MA1, LOW);
  
  // Le moteur B fait la marche avant
  digitalWrite(MB0, LOW);
  digitalWrite(MB1, HIGH);
  
  // On tourne sur la droite pendant une seconde
  delay(1000);
}
 
void changeDirection(){
  stop();   // En premier lieu, on se stoppe à la vue d'un obstacle
  goBackward();   // Puis on fait une marche arrière
  randomNumber = random(2.0);   // On choisit un nombre au hasard entre 0 et 1 (que l'on affiche dans la console par la suite)
  Serial.println(randomNumber);
  if(randomNumber < 1.0){
    turnOnTheLeft();    // Si le nombre choisit est 0, on va sur la gauche
  }
  else{
    turnOnTheRight();   // Sinon, on va sur la droite
  }
  stop();   // Enfin, on se stoppe une dernière fois, prêt à repartir 
}

void loop() {
 
  /* Mesure de distance avec une impulsion HIGH sur la broche TRIGGER */
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  long measure = pulseIn(ECHO_PIN, HIGH);   // Mesure du temps entre l'envoi de l'impulsion et sa réception
 
  float distance = measure / 2.0 * SOUND_SPEED;   // Calcul de la distance grâce au temps mesuré
 
  if(distance/1000 < 0.15){
    Serial.println("Vous êtes à moins de 15cm d'un obstacle, il faut s'arrêter"); 
    changeDirection();    // Si un obstacle est à moins de 10cm, on change de direction
  }
  else{
    Serial.println("Vous pouvez continuer en ligne droite !"); 
    goForward();    // Sinon, on va tout droit
  }

  // Délai d'attente pour ne pas afficher trop de résultats à la seconde
  delay(500);
}