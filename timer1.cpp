#if !defined(INCLUDE)

#include <Arduino.h>
#include <stdio.h>
#include "struct.h"
#include "config.h"

#define EXTC
#define EXT
#endif

EXTC void initTimer1(unsigned int val);
EXTC void stopTimer1();

#define TMR1_PWM_MAX 1024

#if !defined(INCLUDE)

void initTimer1(unsigned int dutyCycle)
{
 // printf("initTimer1 dutyCycle %d\n", val);
 // set pin b5 to an output
 T1_PWM_A_DDR |= T1_PWM_A_Mask;
 if (dutyCycle == 0)
 {
  TCCR1A = 0;
  TCCR1B = 0;
  
  T1_PWM_A_Port &= ~T1_PWM_A_Mask;
 }
 else if (dutyCycle >= (TMR1_PWM_MAX - 1))
 {
  TCCR1A = 0;
  TCCR1B = 0;
  T1_PWM_A_Port |= T1_PWM_A_Mask;
 }
 else
 {
  // set oc1a high on compare match
  // mode 7, fast pwm 10 bit
  TCCR1A = _BV(COM1A1) | _BV(WGM11) | _BV(WGM10);
  // set output compare a to duty cycle
  OCR1A = dutyCycle;
  // clear counter
  TCNT1 = 0;
  // mode 7, fast pwm
  // no prescaling and start clock no prescale
  TCCR1B = _BV(WGM12) | _BV(CS10);
 }
}

void stopTimer1()
{
 T1_PWM_A_DDR |= T1_PWM_A_Mask;	/* set pin to an output */
 TCCR1A = 0;			/* disaple pwm */
 TCCR1B = 0;			/* disable counter */
 T1_PWM_A_Port &= ~T1_PWM_A_Mask; /* clear output bit */
}

#endif
