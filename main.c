//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                Notes and comments by Henjie Agadan
// Refer to ATMega328p datasheet pages 108 - 114. For registers and
//
// The Timer in this one is 16-bit, the details about it is also at the
// datasheet starting from 89.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <avr/io.h>
#include <avr/interrupt.h>

int main(void) {
  
  cli();
  
  // Normal port operation OC1A/OC1B disconnected
  TCCR1A = 0;
  TCCR1B = 0;
  // Note that WGM10-WGM12 are also set to 0, therefore, Normal port operation
  
  TCCR1B |= (1 << CS12); // Prescaler is set to 256
  
  TCNT1 = 3035; // Accesses the Timer/Counter value, instead of
  // starting from 0, we start from a defined value, the factor
  // in order for the each period to precisely end at 1-sec.
    
  TIMSK1 |= (1 << TOIE1); // Timer/Counter1, Overflow Interrupt Enbable
  // Interrupt is triggered every period

  DDRB |= (1 << 5); // Built-in LED, PIN13, set to OUTPUT
  
  sei();

  while(1) {
  	// ...
  }
}


ISR(TIMER1_OVF_vect){
  PORTB ^= 0b00100000; // Toggle ON-OFF Built-in LED every period
  TCNT1 = 3035; // Since counter reached max-value, set value back to start
} 
