#include <Arduino.h>
#include "config.h"
#include "serial.h"

void pinConfig()
{

#ifdef ARDUINO_AVR_MEGA2560

 pinMode(A_Pin, OUTPUT);
 pinMode(B_Pin, OUTPUT);
 pinMode(SYNC_Pin, OUTPUT);
 pinMode(PULSE_Pin, OUTPUT);
 pinMode(INDEX_Pin, OUTPUT);
 pinMode(T2_Pin, OUTPUT);
 pinMode(T1_PWM_A_Pin, OUTPUT);
 pinMode(T3_PWM_A_Pin, OUTPUT);
 pinMode(T4_PWM_A_Pin, OUTPUT);
 pinMode(CHG_PUMP_Pin, INPUT);
 pinMode(PWM_Pin, INPUT);
 pinMode(SP_FWD_Pin, OUTPUT);
 pinMode(SP_REV_Pin, OUTPUT);
 pinMode(E_STOP_NO_Pin, OUTPUT);
 pinMode(E_STOP_NC_Pin, OUTPUT);
 pinMode(E_STOP_RST_Pin, OUTPUT);
 pinMode(FAST_PWM_Pin, OUTPUT);
 pinMode(VFD_FWD_Pin, OUTPUT);
 pinMode(VFD_REV_Pin, OUTPUT);
 pinMode(SP_ENA_Pin, OUTPUT);
 pinMode(STEP_DIS_Pin, OUTPUT);
 pinMode(E_STOP_RLY_Pin, OUTPUT);
 pinMode(E_STOP_PC_Pin, OUTPUT);
 pinMode(W_DOG_Pin, OUTPUT);
 pinMode(LED_Pin, OUTPUT);
 pinMode(DBG0_Pin, OUTPUT);
 pinMode(DBG1_Pin, OUTPUT);
 pinMode(DBG2_Pin, OUTPUT);

#endif

#ifdef ARDUINO_AVR_PRO

 pinMode(A_Pin, OUTPUT);
 pinMode(B_Pin, OUTPUT);
 pinMode(SYNC_Pin, OUTPUT);
 pinMode(T1_PWM_A_Pin, OUTPUT);

#endif

#ifdef ARDUINO_AVR_PROMICRO16

 pinMode(T1_PWM_A_Pin, OUTPUT);
 pinMode(CHG_PUMP_Pin, INPUT);
 pinMode(PWM_Pin, INPUT);
 pinMode(SP_FWD_Pin, OUTPUT);
 pinMode(SP_REV_Pin, OUTPUT);
 pinMode(E_STOP_NO_Pin, OUTPUT);
 pinMode(E_STOP_NC_Pin, OUTPUT);
 pinMode(E_STOP_RST_Pin, OUTPUT);
 pinMode(FAST_PWM_Pin, OUTPUT);
 pinMode(VFD_FWD_Pin, OUTPUT);
 pinMode(VFD_REV_Pin, OUTPUT);
 pinMode(SP_ENA_Pin, OUTPUT);
 pinMode(STEP_DIS_Pin, OUTPUT);
 pinMode(E_STOP_RLY_Pin, OUTPUT);
 pinMode(E_STOP_PC_Pin, OUTPUT);
 pinMode(W_DOG_Pin, OUTPUT);

#endif
}
