#include <Arduino.h>

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);    
}

void ledOn() {
  PORTB = PORTB | (1 << 5);
}

void ledOff() {
  PORTB = PORTB & ~ (1 << 5);
}

void loop() {
  ledOn();
  delay(1000);
  ledOff();
  delay(1000);
}