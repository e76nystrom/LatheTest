#include <Arduino.h>
#include "config.h"
#include "serial.h"
#include "struct.h"
#include "timer1.h"
#include "timer2.h"
#include "timer3.h"
#include "timer4.h"

void setup1();
void loop1();

#define ARDUINO_ARCH_AVR 1

#define RESET_DEBOUNCE_TIME 20
#define PWM_INACTIVITY_TIME 500
#define CHARGE_PUMP_TIMEOUT 20
#define LED_BLINK_TIME 500

#define USEC_MIN (60L * 1000000L)

T_TIMER_CTL tmr1;
long int period1;

#if ENCODER_TEST
void encoderStart();
void encoderStop();

int rpm;
char encRun;
int encRunCount;
int encCounter;
int encLines;
int encMax;
int encRevCounter;
char encState;
char encRev;
#define encStart() encRun = 1
#define encStop() encRun = 0

unsigned int pwm3Counter;

long int period3;
unsigned int dutyCycle3;
T_TIMER_CTL tmr3;
#endif

#if defined(TCCR4A) && !defined(TCCR4E)
#define INDEX_COUNT 64
unsigned int pwm4Counter;
int indexCounter;
int indexCount;

long int period4;
unsigned int dutyCycle4;
T_TIMER_CTL tmr4;
#endif

void showTimer0();
void showTimer(P_TIMER_CTL tmr);
void showPort(P_PORT port, const char *name);

extern volatile unsigned long timer0_millis;

T_SHORT_LONG fDutyCycle;

uint16_t ledTime;		/* last led update time */

uint16_t intMillis();		/* short integer milliseconds */
void procLoop();		/* processing loop */

#if CONSOLE
void cmdLoop();			/* command loop */
#endif
void ctlStatus();		/* control status */

#if CONSOLE == 0
#define putx0(ch)
#endif

void setup()
{
#if CONSOLE
 initSerial(19200);
 puts(F0("\nstarting 0\n"));
#endif

 P_TIMER_CTL t;
#ifdef ARDUINO_AVR_PRO
 t = &tmr1;
 t->timer = (P_TMR) &TCCR1A;
 t->timsk = (uint8_t *) &TIMSK1;
 t->tifr = (uint8_t *) &TIFR1;
 t->aPort = (P_PORT) &OC1A_Port;
 t->aMask = OC1A_Mask;
#endif

#ifdef TCCR3A
 t = &tmr3;
 t->timer = (P_TMR) &TCCR3A;
 t->timsk = (uint8_t *) &TIMSK3;
 t->tifr = (uint8_t *) &TIFR3;
 t->aPort = (P_PORT) &OC3A_Port;
 t->aMask = OC3A_Mask;

#if CONSOLE
 showTimer(&tmr3);
#endif
#endif

#if INDEX_TEST
#if defined(TCCR4A) && !defined(TCCR4E)
 t = &tmr4;
 t->timer = (P_TMR) &TCCR4A;
 t->timsk = (uint8_t *) &TIMSK4;
 t->tifr = (uint8_t *) &TIFR4;
 t->aPort = (P_PORT) &OC4A_Port;
 t->aMask = OC4A_Mask;

 indexCounter = INDEX_COUNT;
 indexCount = INDEX_COUNT;
#endif
#endif

#if ENCODER_TEST
 encLines = 100;
 rpm = 100;
#endif

 pinConfig();

 ledTime = 0;

#if CONSOLE
 puts(F0("C for command mode\n"));
 fflush(stdout);
#endif
}

void loop()
{
#if CONSOLE
 while (DBGPORT.available())
 {
  char ch = DBGPORT.read();
  if (ch == 'C')
  {
   while (DBGPORT.available())
    ch = DBGPORT.read();
   cmdLoop();
  }
 }
#endif

 procLoop();

#if ledRead
 uint16_t curTime = intMillis();
 if ((curTime - ledTime) > LED_BLINK_TIME)
 {
  ledTime = curTime;
  if (ledRead())
   ledClr();
  else
   ledSet();
 }
#endif
}

#if CONSOLE

void cmdLoop()
{
 puts(F0("command loop\n"));
 while (1)
 {
  procLoop();
  if (DBGPORT.available())
  {
   char ch = DBGPORT.read();
   DBGPORT.write(ch);
   newLine();
   if (ch == 'x')		/* exit */
    break;
   else if (ch == 't')		/* control bits, inputs, and outputs */
   {
    ctlStatus();
   }
#if ENCODER_TEST
   else if (ch == 's')		/* start encoder */
   {
    encoderStart();
   }
   else if (ch == 'r')		/* reverse encoder */
   {
    encRev ^= 1;
    printf(F0("encoder reverse %d\n"), encRev);
   }
   else if (ch == 'q')		/* stop encoder */
   {
    encoderStop();
   }
   else if (ch == 'e')
   {
    if (query(&getnum, F1("encoder [%d] lines : "), encLines))
    {
     encLines = val;
    }
   }
#ifdef TCCR3A
   else if (ch == 'R')
   {
    if (period3 != 0)
    {
     printf("period3 %ld encLines %d encPulse %d\n",
	    period3, encLines, encLines * 4);
     rpm = (unsigned int) (USEC_MIN / (period3 * encLines * 4));
    }
    if (query(&getnum, F1("rpm [%d]: "), rpm))
    {
     rpm = val;
    }
    /*
      usecPulse = (usec / min) / ((rev / min) * (pulse / rev))
      revMin = (usec / min) / ((usec / pulse) * (pulse / rev))
    */
    printf("rpm %d encLines %d encPulse %d\n",
	   rpm, encLines, encLines * 4);
    long int pulseMin = (long int) rpm * encLines * 4;
    long int period =  (long int) USEC_MIN / ((long int) rpm * encLines * 4);
    printf("pulseMin %ld pulsePeriod %ld usec\n", pulseMin, period);
    if (period != period3)
    {
     period3 = period;
     stopTimer3();
     initTimer3(period3);
     showTimer(&tmr3);
    }
   }
#endif
#endif
   else if (ch == 'E')
   {
    printf(F0("setup1()\n"));
    setup1();
    printf(F0("loop1()\n"));
    loop1();
    printf(F0("done\n"));
   }
#ifdef ARDUINO_AVR_PRO
   else if (ch == '1')		/* control timer 3 spindle pwm test */
   {
    ch = query(F1("init: "));
    if (ch == 'y')
    {
     if (query(&getnum, F1("period [%ld] us: "), period1))
     {
      period1 = val;
     }
     if (period1 != 0)
     {
      stopTimer1();
      initTimer1(period1);
     }
     else
     {
      stopTimer1();
     }
    }
    showTimer(&tmr1);
   }
#endif
#ifdef TCCR3A
   else if (ch == '3')		/* control timer 3 spindle pwm test */
   {
    ch = query(F1("init: "));
    if (ch == 'y')
    {
     if (query(&getnum, F1("period [%ld] us: "), period3))
     {
      period3 = val;
     }
     if (period3 != 0)
     {
      stopTimer3();
      initTimer3(period3);
     }
     else
     {
      stopTimer3();
     }
    }
    showTimer(&tmr3);
   }
#endif
#if defined(TCCR4A) && !defined(TCCR4E)
   else if (ch == '4')		/* control timer 4 charge pump test */
   {
    ch = query(F1("init: "));
    if (ch == 'y')
    {
     if (query(&getLong, F1("timer 4 period [%ld] us: "), period4))
     {
      period4 = lVal;
     }
     if (period4 > 0)
     {
#if INDEX_TEST
      if (query(&getnum, F1("cycle length [%d]: "), indexCount))
      {
       indexCount = val;
       indexCounter = val;
      }
#endif
      printf(F0("period %ld\n"), period4);
      stopTimer4();
      initTimer4(period4);
     }
     else
     {
      stopTimer4();
     }
    }
#if INDEX_TEST
    printf(F0("indexCounter %d pwmCounter %u\n"), indexCounter, pwm4Counter);
#endif
   }
#endif
   else if (ch == '?')
   {
#ifdef TCCR3A
#if ENCODER_TEST
    printf(F0("encCounter %d encRevCounter %d\n"), encCounter, encRevCounter);
#endif
#endif
#ifdef PINA
    showPort((P_PORT) &PINA, "A");
#endif
    showPort((P_PORT) &PINB, "B");
    showPort((P_PORT) &PINC, "C");
    showPort((P_PORT) &PIND, "D");
#ifdef PINE
    showPort((P_PORT) &PINE, "E");
#endif
#ifdef PINF
    showPort((P_PORT) &PINF, "F");
#endif
#ifdef PING
    showPort((P_PORT) &PING, "G");
#endif
#ifdef PINH
    showPort((P_PORT) &PINH, "H");
#endif
#ifdef PINJ
    showPort((P_PORT) &PINJ, "J");
#endif
#ifdef PINK
    showPort((P_PORT) &PINK, "K");
#endif
#ifdef PINL
    showPort((P_PORT) &PINL, "L");
#endif
   }
  }
 }
}

void ctlStatus()
{
 procLoop();			/* run loop in case an input changed */
}

#endif

void procLoop()
{
}

#if ENCODER_TEST

void encoderStart()
{
 encState = 0;
 aClr();
 bClr();
 syncClr();
 encMax = encLines * 4;
 encCounter = 0;
 encRevCounter = 0;
 encRunCount = 0;
 encStart();
#if CONSOLE
 puts(F0("encoder start\n"));
#endif
}

void encoderStop()
{
 encStop();
#if CONSOLE
 puts(F0("encoder stop\n"));
#endif
}

#endif

#ifdef ARDUINO_AVR_PRO
ISR(TIMER1_OVF_vect)
#endif
#ifdef ARDUINO_AVR_MEGA2560
ISR(TIMER3_OVF_vect)
#endif
{
#if ENCODER_TEST
 if (encRun)			/* if encoder running */
 {
  pulseSet();
  if (encRunCount != 0)		/* if encoder counting */
  {
   if (--encRunCount == 0)	/* if count is now zero */
   {
    encStop();			/* stop encoder */
   }
  }

  encCounter += 1;		/* update counter */
  if (encCounter >= encMax)	/* if at maximum */
  {
   syncSet();			/* set the sync bit */
   encCounter = 0;		/* reset */
   encRevCounter += 1;		/* count a revolution */
  }
  else				/* if not at maximum */
  {
   syncClr();			/* clear sync bit */
  }

  if (!encRev)			/* if forwared */
  {
   /* 00   01   11   10   */
   /* 0010 0100 1101 1011 */
   /*    2    4    d    b */
   switch (encState)		/* select on state */
   {
   case 0:			/* 00 */
    aSet();			/* 01 0100 4 */
    break;
   case 1:			/* 01 */
    bSet();			/* 11 1101 d */
    break;
   case 2:			/* 11 */
    aClr();			/* 10 1011 b */
    break;
   case 3:			/* 10 */
    bClr();			/* 00 0010 2 */
    break;
   }
  }
  else
  {
   /* 00   10   11   01   */
   /* 0001 1000 1110 0111 */
   /*    1    8    e    7 */
   switch (encState)		/* select on state */
   {
   case 0:			/* 00 */
    bSet();			/* 10 1000 8 */
    break;
   case 1:			/* 10 */
    aSet();			/* 11 1110 e */
    break;
   case 2:			/* 11 */
    bClr();			/* 01 0111 7 */
    break;
   case 3:			/* 01 */
    aClr();			/* 00 0001 1 */
    break;
   }
  }
  encState += 1;		/* update state */
  encState &= 0x3;		/* mask in range */
  pulseClr();
 }
#endif
}

#if defined(TCCR4A) && !defined(TCCR4E)

ISR(TIMER4_OVF_vect)
{
#if INDEX_TEST
 if (indexCounter <= 0)
 {
  indexSet();
  indexCounter = indexCount;
 }
 else
 {
  indexClr();
  --indexCounter;
 }
#endif
}

#endif

uint16_t intMillis()
{
 uint16_t m;
 uint8_t oldSREG = SREG;	// save interrupt flag
 cli();				// disable interrupts
 m = ((P_SHORT_LONG) &timer0_millis)->low; // read low part of millis
 SREG = oldSREG;		// enable interrupts
 return(m);			// return value
}

#if CONSOLE

void showTimer0()
{
 printf(F0("TCCR0A %02x TCCR0B %02x TCNT0 %02x TIMSK0 %02x TIFR0 %02x\n"),
	TCCR0A, TCCR0B, TCNT0, TIMSK0, TIFR0);
 printf(F0("OCR0A %02x OCR0b %02x\n"),
	OCR0A, OCR0B);
}

void showTimer(P_TIMER_CTL tmr)
{
 P_TMR t = tmr->timer;
 P_PORT p = tmr->aPort;
 printf(F0("aPort %02x aDDR %02x aMask %02x "
	   "tccra %02x tccrb %02x tccrc %02x\n"),
	p->port, p->ddr, tmr->aMask,
	t->tccra, t->tccrb, t->tccrc);
 printf(F0("tctn %04x ocra %04x ocrb %04x ocrc %04x icr %04X\n"),
	t->tcnt, t->ocra, t->ocrb, t->ocrc, t->icr);
 printf(F0("timsk %02x tifr %02x\n"),
	*tmr->timsk, *tmr->tifr);
}

void showPort(P_PORT port, const char *name)
{
 printf(F0("%s port %02x ddr %02x pinc %0x\n"),
	name, port->port, port->ddr, port->pin);
}

#endif

char input;
char lastInput;
unsigned char index;
char count;
char tmp;

void setup1()
{                
#ifdef ARDUINO_AVR_ATTINYX5

 pinMode(0, OUTPUT);
 pinMode(1, OUTPUT);
 pinMode(2, OUTPUT);
 pinMode(5, OUTPUT);

 pinMode(3, INPUT);
 pinMode(4, INPUT);

#endif
#ifdef ARDUINO_AVR_MEGA2560

 pinMode(53, OUTPUT);
 pinMode(52, OUTPUT);
 pinMode(51, OUTPUT);
 pinMode(11, OUTPUT);

 pinMode(50, INPUT);
 pinMode(10, INPUT);

#endif
}

#define FWD 0
#define REV _BV(1)
#define CLK _BV(2)

#define dbg0aSet() PORTB |= _BV(0)
#define dbg0aClr() PORTB &= ~_BV(0)

#define dbg1aSet() PORTB |= _BV(5)
#define dbg1aClr() PORTB &= ~_BV(5)

/* forward */
/* 00   01   11   10   */
/* 0010 0100 1101 1011 */
/*    2    4    d    b */

/* reverse */
/* 00   10   11   01   */
/* 0001 1000 1110 0111 */
/*    1    8    e    7 */

char decoder[16] =
{		/* ccll */
 0,		/* 0000 0 */
 REV | CLK,	/* 0001 1	r0 */
 FWD | CLK,	/* 0010 2 f0 */
 0,		/* 0011 3 */
 FWD | CLK,	/* 0100 4 f1 */
 0,		/* 0101 5 */
 0,		/* 0110 6 */
 REV | CLK,	/* 0111 7	r3 */
 REV | CLK,	/* 1000 8	r1 */
 0,		/* 1001 9 */
 0,		/* 1010 a */
 FWD | CLK,	/* 1011 b f3 */
 0,		/* 1100 c */
 FWD | CLK,	/* 1101 d f2 */
 REV | CLK,	/* 1110 e	r2 */
 0,		/* 1111 f */
};

#define A _BV(3)
#define B _BV(4)

void loop1()
{
 count = 0;
 tmp = 0;
 lastInput = (PINB & (A | B)) >> 1;
 while (1)
 {
  if (tmp & 1)
  {
   tmp = 0;
   dbg0aClr();
  }
  else
  {
   tmp = 1;
   dbg0aSet();
  }
  input = (PINB & (A | B)) >> 1;
  if (input != lastInput)
  {
   index = input | (lastInput >> 2);
   lastInput = input;
   PORTB = decoder[index];
   count = 2;
  }
  else
  {
   if (count != 0)
   {
    if (--count <= 0)
     PORTB &= ~CLK;
   }
  }
  if (DBGPORT.available())
  {
   char ch = DBGPORT.read();
   DBGPORT.write(ch);
   newLine();
   if (ch == 3)			/* exit */
    break;
  }
 }
}
