#include <Arduino.h>

int trigger_pin = 2;
int echo_pin = 3;
int buzzer_pin = 10; 
int led =  13;
int time;
int distance; 

void setup(){
  pinMode (trigger_pin, OUTPUT); 
  pinMode (echo_pin, INPUT);
  pinMode (buzzer_pin, OUTPUT);
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}


void loop(){
  digitalWrite (trigger_pin, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigger_pin, LOW);
  time = pulseIn (echo_pin, HIGH);
  distance = (time * 0.034)/2;

  if (distance <= 10) {    
    Serial.print (" Distance = ");              
    Serial.println (distance);   
    digitalWrite(led, HIGH);
    delay (500);
  }
  else {   
    Serial.print (" Distance = ");              
    Serial.println (distance);  
    digitalWrite(led, LOW);
    delay (500);        
  } 
}