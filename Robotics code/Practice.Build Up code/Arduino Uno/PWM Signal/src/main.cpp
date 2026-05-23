/*
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

double dutyCycle = 1;
int main(){

  DDRD = (1 << PORTD6);

  TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
  TIMSK0 = (1 << TOIE0);

  OCR0A = (dutyCycle/100)*255;

  sei();

  TCCR0B= (1 << CS00) | (1 << CS02);
  while(1){
    _delay_ms(1000);
    dutyCycle += 1;
  }

  return 0;
}
ISR(TIMER0_OVF_vect){
  OCR0A = (dutyCycle/100*255);
}
*/
#include <Arduino.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  for (pos = 0; pos <= 180; pos += 5) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(25);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 5) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(25);                       // waits 15ms for the servo to reach the position
  }
}