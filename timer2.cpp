#if !defined(INCLUDE)

#include <Arduino.h>
#include <stdio.h>
#include "config.h"
#include "struct.h"
#include "serial.h"

#define EXT
#define EXTC
#endif

#ifdef TCCR2A

EXTC void initTimer2();
EXTC void showTimer2();
EXTC void readTimer2();
EXTC void clrTimer2();

EXT uint8_t timer2High;
EXT CHAR_INT timer2Count;

#if !defined(INCLUDE)

void initTimer2()
{
 // stop timer
 TCCR2B = 0;
 // clear overflow counter
 timer2High = 0;
 // normal operation
 // ctc operation top set by ocra
 TCCR2A = _BV(WGM21);
 TCNT2 = 0;
 // 1 ms per rollover 250 * 4 usec
 OCR2A = 250 - 1;
 OCR2B = 0;
 // enable overflow interrupt
 TIMSK2 = _BV(OCF2A);
 // clear flag register
 TIFR2 = _BV(OCF2B) | _BV(OCF2A) | _BV(TOV2);
 // clock from internal clock
 ASSR = 0;
 // start timer
 // prescale by 64 4 usec per count
 TCCR2B = _BV(CS22);
}

void clrTimer2()
{
 TCCR2B = 0;			// stop timer
 timer2High = 0;		// clear overflow
 TCNT2 = 0;			// clear counter
 TCCR2B = _BV(CS22);		// restart
}

void readTimer2()
{
 TCCR2B = 0;			// stop timer
 timer2Count.hi = timer2High;	// read high part
 timer2Count.lo = TCNT2;	// read low part
 TCCR2B = _BV(CS22);		// restart
}

#if CONSOLE
void showTimer2()
{
 printf(F0("TCCR2A %02x TCCR2B %02x TCNT2 %02x TIMSK2 %02x TIFR2 %02x\n"),
	TCCR2A, TCCR2B, TCNT2, TIMSK2, TIFR2);
 printf(F0("OCR2A %02x OCR2B %02x\n"), OCR2A, OCR2B);
 printf(F0("ASSR %02x GTCCR %02x\n"), ASSR, GTCCR);
}
#endif

#endif

#endif
