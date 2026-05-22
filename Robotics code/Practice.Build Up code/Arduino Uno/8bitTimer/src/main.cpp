#include <avr/io.h>
#include <avr/interrupt.h>

int extra = 0;
int main(){

  DDRB = 0x02;
  TCCR0A = (1 << WGM01);
  OCR0A = 195;
  TIMSK0 = (1 << OCIE0A);

  sei();

  TCCR0B = (1 << CS02) | (1 << CS00); // Starts at 1024 prescaler

  while (1){
  }
  return 0;
}

ISR(TIMER0_COMPA_vect){
  extra ++;
  if (extra > 10){
    PORTB ^= (1 << PORTB1);
    extra = 0;
  }
}