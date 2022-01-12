#include <Arduino.h>

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
#define LED 13

void ledSetup() {
  DDRB = DDRB | (1 << 5);
}

// the setup routine runs once when you press reset:
void setup() {                
  ledSetup();    
}

void ledOn() {
  PORTB = PORTB | (1 << 5);
}

void ledOff() {
  PORTB = PORTB & ~ (1 << 5);
}

void toggle(){
  PINB |= (1<<5);
}

void loop() {
  toggle();
  delay(1000);
}