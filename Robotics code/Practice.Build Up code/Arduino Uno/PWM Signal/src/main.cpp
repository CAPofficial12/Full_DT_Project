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