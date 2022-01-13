#include <Arduino.h>

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
#define LED 13

void ledSetup() {
  DDRB = DDRB | (1 << 5);
}

// the setup routine runs once when you press reset:

void ledOn() {
  PORTB = PORTB | (1 << 5);
}

void ledOff() {
  PORTB = PORTB & ~ (1 << 5);
}

void toggle(){
  PINB |= (1<<5);
}

void timerSetup(){
  TCCR1A = 0;
  TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
  OCR1A = 15625;
  TCNT1 = 0;
  TIMSK1 = (1 << OCIE1A);
}

ISR(TIMER1_COMPA_vect){
  toggle();
}

void setup() {                
  ledSetup(); 
  timerSetup();   
}

void loop() {
}