extern void pinConfig();

#define DEBUG                1
#define CONSOLE              1
#define FLASH_STRINGS        1

#ifdef ARDUINO_AVR_MEGA2560

#define ENCODER_TEST         1
#define INDEX_TEST           0

#define OC0A_Port PINB
#define OC0A_Mask _BV(PB7)

#define OC0B_Port PING
#define OC0B_Mask _BV(PG5)

#define OC1A_Port PINB
#define OC1A_Mask _BV(PB5)

#define OC1B_Port PINB
#define OC1B_Mask _BV(PB6)

#define OC1C_Port PINB
#define OC1C_Mask _BV(PB7)

#define OC2A_Port PINB
#define OC2A_Mask _BV(PB4)

#define OC2B_Port PINH
#define OC2B_Mask _BV(PH6)

#define OC3A_Port PINE
#define OC3A_Mask _BV(PE3)

#define OC3B_Port PINE
#define OC3B_Mask _BV(PE4)

#define OC3C_Port PINE
#define OC3C_Mask _BV(PE5)

#define OC4A_Port PINH
#define OC4A_Mask _BV(PH3)

#define OC4B_Port PINH
#define OC4B_Mask _BV(PH4)

#define OC4C_Port PINH
#define OC4C_Mask _BV(PH5)

#define OC5A_Port PINL
#define OC5A_Mask _BV(PL3)

#define OC5B_Port PINL
#define OC5B_Mask _BV(PL4)

#define OC5C_Port PINL
#define OC5C_Mask _BV(PL5)

#define A_Pin 22
#define A_Port PORTA
#define A_DDR DDRA
#define A_In PINA
#define A_Bit PA0
#define A_Mask _BV(A_Bit)
#define aRead() ((A_Port & A_Mask) != 0)
#define aSet() A_Port |= A_Mask
#define aClr() A_Port &= ~A_Mask

#define B_Pin 23
#define B_Port PORTA
#define B_DDR DDRA
#define B_In PINA
#define B_Bit PA1
#define B_Mask _BV(B_Bit)
#define bRead() ((B_Port & B_Mask) != 0)
#define bSet() B_Port |= B_Mask
#define bClr() B_Port &= ~B_Mask

#define SYNC_Pin 24
#define SYNC_Port PORTA
#define SYNC_DDR DDRA
#define SYNC_In PINA
#define SYNC_Bit PA2
#define SYNC_Mask _BV(SYNC_Bit)
#define syncRead() ((SYNC_Port & SYNC_Mask) != 0)
#define syncSet() SYNC_Port |= SYNC_Mask
#define syncClr() SYNC_Port &= ~SYNC_Mask

#define PULSE_Pin 25
#define PULSE_Port PORTA
#define PULSE_DDR DDRA
#define PULSE_In PINA
#define PULSE_Bit PA3
#define PULSE_Mask _BV(PULSE_Bit)
#define pulseRead() ((PULSE_Port & PULSE_Mask) != 0)
#define pulseSet() PULSE_Port |= PULSE_Mask
#define pulseClr() PULSE_Port &= ~PULSE_Mask

#define INDEX_Pin 9
#define INDEX_Port PORTH
#define INDEX_DDR DDRH
#define INDEX_In PINH
#define INDEX_Bit PH6
#define INDEX_Mask _BV(INDEX_Bit)
#define indexRead() ((INDEX_Port & INDEX_Mask) != 0)
#define indexSet() INDEX_Port |= INDEX_Mask
#define indexClr() INDEX_Port &= ~INDEX_Mask

#define T2_Pin 8
#define T2_Port PORTH
#define T2_DDR DDRH
#define T2_In PINH
#define T2_Bit PH5
#define T2_Mask _BV(T2_Bit)
#define t2Read() ((T2_Port & T2_Mask) != 0)
#define t2Set() T2_Port |= T2_Mask
#define t2Clr() T2_Port &= ~T2_Mask

#define T1_PWM_A_Pin 11
#define T1_PWM_A_Port PORTB
#define T1_PWM_A_DDR DDRB
#define T1_PWM_A_In PINB
#define T1_PWM_A_Bit PB5
#define T1_PWM_A_Mask _BV(T1_PWM_A_Bit)
#define t1PwmARead() ((T1_PWM_A_Port & T1_PWM_A_Mask) != 0)
#define t1PwmASet() T1_PWM_A_Port |= T1_PWM_A_Mask
#define t1PwmAClr() T1_PWM_A_Port &= ~T1_PWM_A_Mask

#define T3_PWM_A_Pin 5
#define T3_PWM_A_Port PORTE
#define T3_PWM_A_DDR DDRE
#define T3_PWM_A_In PINE
#define T3_PWM_A_Bit PE3
#define T3_PWM_A_Mask _BV(T3_PWM_A_Bit)
#define t3PwmARead() ((T3_PWM_A_Port & T3_PWM_A_Mask) != 0)
#define t3PwmASet() T3_PWM_A_Port |= T3_PWM_A_Mask
#define t3PwmAClr() T3_PWM_A_Port &= ~T3_PWM_A_Mask

#define T4_PWM_A_Pin 6
#define T4_PWM_A_Port PORTH
#define T4_PWM_A_DDR DDRH
#define T4_PWM_A_In PINH
#define T4_PWM_A_Bit PH3
#define T4_PWM_A_Mask _BV(T4_PWM_A_Bit)
#define t4PwmARead() ((T4_PWM_A_Port & T4_PWM_A_Mask) != 0)
#define t4PwmASet() T4_PWM_A_Port |= T4_PWM_A_Mask
#define t4PwmAClr() T4_PWM_A_Port &= ~T4_PWM_A_Mask

#define CHG_PUMP_Pin 20
#define CHG_PUMP_In PIND
#define CHG_PUMP_Bit PD1
#define CHG_PUMP_Mask _BV(CHG_PUMP_Bit)
#define chgPumpIn() ((CHG_PUMP_In & CHG_PUMP_Mask) != 0)
#define chgPumpIntInit() EICRA &= ~((_BV(ISC01) | _BV(ISC00)) << 2);\
	EICRA |= (_BV(ISC01)|_BV(ISC00)) << 2;\
	EIMSK |= (_BV(INT0) << 1)

#define PWM_Pin 21
#define PWM_In PIND
#define PWM_Bit PD0
#define PWM_Mask _BV(PWM_Bit)
#define pwmIn() ((PWM_In & PWM_Mask) != 0)
#define pwmIntInit() EICRA &= ~((_BV(ISC01) | _BV(ISC00)) << 0);\
	EICRA |= (_BV(ISC00)) << 0;\
	EIMSK |= (_BV(INT0) << 0)

#define SP_FWD_Pin 54
#define SP_FWD_In PORTF
#define SP_FWD_Bit PF0
#define SP_FWD_Mask _BV(SP_FWD_Bit)
#define spFwdIn() ((SP_FWD_In & SP_FWD_Mask) != 0)
#define spFwdSet() PORTF |= SP_FWD_Mask
#define spFwdClr() PORTF &= ~SP_FWD_Mask

#define SP_REV_Pin 55
#define SP_REV_In PORTF
#define SP_REV_Bit PF1
#define SP_REV_Mask _BV(SP_REV_Bit)
#define spRevIn() ((SP_REV_In & SP_REV_Mask) != 0)
#define spRevSet() PORTF |= SP_REV_Mask
#define spRevClr() PORTF &= ~SP_REV_Mask

#define E_STOP_NO_Pin 56
#define E_STOP_NO_In PORTF
#define E_STOP_NO_Bit PF2
#define E_STOP_NO_Mask _BV(E_STOP_NO_Bit)
#define eStopNoIn() ((E_STOP_NO_In & E_STOP_NO_Mask) != 0)
#define eStopNoSet() PORTF |= E_STOP_NO_Mask
#define eStopNoClr() PORTF &= ~E_STOP_NO_Mask

#define E_STOP_NC_Pin 57
#define E_STOP_NC_In PORTF
#define E_STOP_NC_Bit PF3
#define E_STOP_NC_Mask _BV(E_STOP_NC_Bit)
#define eStopNcIn() ((E_STOP_NC_In & E_STOP_NC_Mask) != 0)
#define eStopNcSet() PORTF |= E_STOP_NC_Mask
#define eStopNcClr() PORTF &= ~E_STOP_NC_Mask

#define E_STOP_RST_Pin 58
#define E_STOP_RST_In PORTF
#define E_STOP_RST_Bit PF4
#define E_STOP_RST_Mask _BV(E_STOP_RST_Bit)
#define eStopRstIn() ((E_STOP_RST_In & E_STOP_RST_Mask) == 0)
#define eStopRstClr() PORTF |= E_STOP_RST_Mask
#define eStopRstSet() PORTF &= ~E_STOP_RST_Mask

#define FAST_PWM_Pin 11
#define FAST_PWM_Port PORTB
#define FAST_PWM_DDR DDRB
#define FAST_PWM_In PINB
#define FAST_PWM_Bit PB5
#define FAST_PWM_Mask _BV(FAST_PWM_Bit)
#define fastPwmRead() ((FAST_PWM_Port & FAST_PWM_Mask) != 0)
#define fastPwmSet() FAST_PWM_Port |= FAST_PWM_Mask
#define fastPwmClr() FAST_PWM_Port &= ~FAST_PWM_Mask

#define VFD_FWD_Pin 14
#define VFD_FWD_Port PORTJ
#define VFD_FWD_DDR DDRJ
#define VFD_FWD_In PINJ
#define VFD_FWD_Bit PJ1
#define VFD_FWD_Mask _BV(VFD_FWD_Bit)
#define vfdFwdRead() ((VFD_FWD_Port & VFD_FWD_Mask) != 0)
#define vfdFwdSet() VFD_FWD_Port |= VFD_FWD_Mask
#define vfdFwdClr() VFD_FWD_Port &= ~VFD_FWD_Mask

#define VFD_REV_Pin 15
#define VFD_REV_Port PORTJ
#define VFD_REV_DDR DDRJ
#define VFD_REV_In PINJ
#define VFD_REV_Bit PJ0
#define VFD_REV_Mask _BV(VFD_REV_Bit)
#define vfdRevRead() ((VFD_REV_Port & VFD_REV_Mask) != 0)
#define vfdRevSet() VFD_REV_Port |= VFD_REV_Mask
#define vfdRevClr() VFD_REV_Port &= ~VFD_REV_Mask

#define SP_ENA_Pin 16
#define SP_ENA_Port PORTH
#define SP_ENA_DDR DDRH
#define SP_ENA_In PINH
#define SP_ENA_Bit PH1
#define SP_ENA_Mask _BV(SP_ENA_Bit)
#define spEnaRead() ((SP_ENA_Port & SP_ENA_Mask) != 0)
#define spEnaSet() SP_ENA_Port |= SP_ENA_Mask
#define spEnaClr() SP_ENA_Port &= ~SP_ENA_Mask

#define STEP_DIS_Pin 17
#define STEP_DIS_Port PORTH
#define STEP_DIS_DDR DDRH
#define STEP_DIS_In PINH
#define STEP_DIS_Bit PH0
#define STEP_DIS_Mask _BV(STEP_DIS_Bit)
#define stepDisRead() ((STEP_DIS_Port & STEP_DIS_Mask) != 0)
#define stepDisSet() STEP_DIS_Port |= STEP_DIS_Mask
#define stepDisClr() STEP_DIS_Port &= ~STEP_DIS_Mask

#define E_STOP_RLY_Pin 50
#define E_STOP_RLY_Port PORTB
#define E_STOP_RLY_DDR DDRB
#define E_STOP_RLY_In PINB
#define E_STOP_RLY_Bit PB3
#define E_STOP_RLY_Mask _BV(E_STOP_RLY_Bit)
#define eStopRlyRead() ((E_STOP_RLY_Port & E_STOP_RLY_Mask) != 0)
#define eStopRlySet() E_STOP_RLY_Port |= E_STOP_RLY_Mask
#define eStopRlyClr() E_STOP_RLY_Port &= ~E_STOP_RLY_Mask

#define E_STOP_PC_Pin 52
#define E_STOP_PC_Port PORTB
#define E_STOP_PC_DDR DDRB
#define E_STOP_PC_In PINB
#define E_STOP_PC_Bit PB1
#define E_STOP_PC_Mask _BV(E_STOP_PC_Bit)
#define eStopPcRead() ((E_STOP_PC_Port & E_STOP_PC_Mask) != 0)
#define eStopPcSet() E_STOP_PC_Port |= E_STOP_PC_Mask
#define eStopPcClr() E_STOP_PC_Port &= ~E_STOP_PC_Mask

#define W_DOG_Pin 2
#define W_DOG_Port PORTE
#define W_DOG_DDR DDRE
#define W_DOG_In PINE
#define W_DOG_Bit PE4
#define W_DOG_Mask _BV(W_DOG_Bit)
#define wDogRead() ((W_DOG_Port & W_DOG_Mask) != 0)
#define wDogSet() W_DOG_Port |= W_DOG_Mask
#define wDogClr() W_DOG_Port &= ~W_DOG_Mask

#define LED_Pin 13
#define LED_Port PORTB
#define LED_DDR DDRB
#define LED_In PINB
#define LED_Bit PB7
#define LED_Mask _BV(LED_Bit)
#define ledRead() ((LED_Port & LED_Mask) != 0)
#define ledSet() LED_Port |= LED_Mask
#define ledClr() LED_Port &= ~LED_Mask

#define DBG0_Pin 26
#define DBG0_Port PORTA
#define DBG0_DDR DDRA
#define DBG0_In PINA
#define DBG0_Bit PA4
#define DBG0_Mask _BV(DBG0_Bit)
#define dbg0Read() ((DBG0_Port & DBG0_Mask) != 0)
#define dbg0Set() DBG0_Port |= DBG0_Mask
#define dbg0Clr() DBG0_Port &= ~DBG0_Mask

#define DBG1_Pin 27
#define DBG1_Port PORTA
#define DBG1_DDR DDRA
#define DBG1_In PINA
#define DBG1_Bit PA5
#define DBG1_Mask _BV(DBG1_Bit)
#define dbg1Read() ((DBG1_Port & DBG1_Mask) != 0)
#define dbg1Set() DBG1_Port |= DBG1_Mask
#define dbg1Clr() DBG1_Port &= ~DBG1_Mask

#define DBG2_Pin 28
#define DBG2_Port PORTA
#define DBG2_DDR DDRA
#define DBG2_In PINA
#define DBG2_Bit PA6
#define DBG2_Mask _BV(DBG2_Bit)
#define dbg2Read() ((DBG2_Port & DBG2_Mask) != 0)
#define dbg2Set() DBG2_Port |= DBG2_Mask
#define dbg2Clr() DBG2_Port &= ~DBG2_Mask

#endif

#ifdef ARDUINO_AVR_PRO

#define ENCODER_TEST         1
#define INDEX_TEST           0

#define OC0A_Port PIND
#define OC0A_Mask _BV(PD6)

#define OC0B_Port PIND
#define OC0B_Mask _BV(PD5)

#define OC1A_Port PINB
#define OC1A_Mask _BV(PB1)

#define OC1B_Port PINB
#define OC1B_Mask _BV(PB2)

#define OC2A_Port PINB
#define OC2A_Mask _BV(PB3)

#define OC2B_Port PIND
#define OC2B_Mask _BV(PD3)

#define A_Pin 12
#define A_Port PORTB
#define A_DDR DDRB
#define A_In PINB
#define A_Bit PB4
#define A_Mask _BV(A_Bit)
#define aRead() ((A_Port & A_Mask) != 0)
#define aSet() A_Port |= A_Mask
#define aClr() A_Port &= ~A_Mask

#define B_Pin 11
#define B_Port PORTB
#define B_DDR DDRB
#define B_In PINB
#define B_Bit PB3
#define B_Mask _BV(B_Bit)
#define bRead() ((B_Port & B_Mask) != 0)
#define bSet() B_Port |= B_Mask
#define bClr() B_Port &= ~B_Mask

#define SYNC_Pin 13
#define SYNC_Port PORTB
#define SYNC_DDR DDRB
#define SYNC_In PINB
#define SYNC_Bit PB5
#define SYNC_Mask _BV(SYNC_Bit)
#define syncRead() ((SYNC_Port & SYNC_Mask) != 0)
#define syncSet() SYNC_Port |= SYNC_Mask
#define syncClr() SYNC_Port &= ~SYNC_Mask

#define pulseRead() 0
#define pulseSet()
#define pulseClr()

#define T1_PWM_A_Pin 9
#define T1_PWM_A_Port PORTB
#define T1_PWM_A_DDR DDRB
#define T1_PWM_A_In PINB
#define T1_PWM_A_Bit PB1
#define T1_PWM_A_Mask _BV(T1_PWM_A_Bit)
#define t1PwmARead() ((T1_PWM_A_Port & T1_PWM_A_Mask) != 0)
#define t1PwmASet() T1_PWM_A_Port |= T1_PWM_A_Mask
#define t1PwmAClr() T1_PWM_A_Port &= ~T1_PWM_A_Mask

#define ledRead() 0
#define ledSet()
#define ledClr()

#define t2Read() 0
#define t2Set()
#define t2Clr()

#define dbg0Read() 0
#define dbg0Set()
#define dbg0Clr()

#define dbg1Read() 0
#define dbg1Set()
#define dbg1Clr()

#define dbg2Read() 0
#define dbg2Set()
#define dbg2Clr()

#endif

#ifdef ARDUINO_AVR_PROMICRO16

#define ENCODER_TEST         0
#define INDEX_TEST           0
#define SPINDLE_PWM_TEST     0
#define CHARGE_PUMP_TEST     0
#define TMR2_MS_TIMER        0
#define TMR3_MS_TIMER        1

#define OC0A_Port PINB
#define OC0A_Mask _BV(PB7)

#define OC0B_Port PIND
#define OC0B_Mask _BV(PD0)

#define OC1A_Port PINB
#define OC1A_Mask _BV(PB5)

#define OC1B_Port PINB
#define OC1B_Mask _BV(PB6)

#define OC1C_Port PINB
#define OC1C_Mask _BV(PB7)

#define OC3A_Port PINC
#define OC3A_Mask _BV(PC6)

#define OC4A_Port PINC
#define OC4A_Mask _BV(PC7)

#define OC4AC_Port PINC
#define OC4AC_Mask _BV(PC6)

#define OC4B_Port PINB
#define OC4B_Mask _BV(PB6)

#define OC4D_Port PIND
#define OC4D_Mask _BV(PD7)

#define OC4DC_Port PIND
#define OC4DC_Mask _BV(PD6)

#define T1_PWM_A_Pin 9
#define T1_PWM_A_Port PORTB
#define T1_PWM_A_DDR DDRB
#define T1_PWM_A_In PINB
#define T1_PWM_A_Bit PB5
#define T1_PWM_A_Mask _BV(T1_PWM_A_Bit)
#define t1PwmARead() ((T1_PWM_A_Port & T1_PWM_A_Mask) != 0)
#define t1PwmASet() T1_PWM_A_Port |= T1_PWM_A_Mask
#define t1PwmAClr() T1_PWM_A_Port &= ~T1_PWM_A_Mask

#define CHG_PUMP_Pin 2
#define CHG_PUMP_In PIND
#define CHG_PUMP_Bit PD1
#define CHG_PUMP_Mask _BV(CHG_PUMP_Bit)
#define chgPumpIn() ((CHG_PUMP_In & CHG_PUMP_Mask) != 0)
#define chgPumpIntInit() EICRA &= ~((_BV(ISC01) | _BV(ISC00)) << 2);\
	EICRA |= (_BV(ISC01)|_BV(ISC00)) << 2;\
	EIMSK |= (_BV(INT0) << 1)

#define PWM_Pin 3
#define PWM_In PIND
#define PWM_Bit PD0
#define PWM_Mask _BV(PWM_Bit)
#define pwmIn() ((PWM_In & PWM_Mask) != 0)
#define pwmIntInit() EICRA &= ~((_BV(ISC01) | _BV(ISC00)) << 0);\
	EICRA |= (_BV(ISC00)) << 0;\
	EIMSK |= (_BV(INT0) << 0)

#define SP_FWD_Pin 4
#define SP_FWD_In PORTD
#define SP_FWD_Bit PD4
#define SP_FWD_Mask _BV(SP_FWD_Bit)
#define spFwdIn() ((SP_FWD_In & SP_FWD_Mask) != 0)
#define spFwdSet() PORTD |= SP_FWD_Mask
#define spFwdClr() PORTD &= ~SP_FWD_Mask

#define SP_REV_Pin 5
#define SP_REV_In PORTC
#define SP_REV_Bit PC6
#define SP_REV_Mask _BV(SP_REV_Bit)
#define spRevIn() ((SP_REV_In & SP_REV_Mask) != 0)
#define spRevSet() PORTC |= SP_REV_Mask
#define spRevClr() PORTC &= ~SP_REV_Mask

#define E_STOP_NO_Pin 18
#define E_STOP_NO_In PORTF
#define E_STOP_NO_Bit PF7
#define E_STOP_NO_Mask _BV(E_STOP_NO_Bit)
#define eStopNoIn() ((E_STOP_NO_In & E_STOP_NO_Mask) != 0)
#define eStopNoSet() PORTF |= E_STOP_NO_Mask
#define eStopNoClr() PORTF &= ~E_STOP_NO_Mask

#define E_STOP_NC_Pin 19
#define E_STOP_NC_In PORTF
#define E_STOP_NC_Bit PF6
#define E_STOP_NC_Mask _BV(E_STOP_NC_Bit)
#define eStopNcIn() ((E_STOP_NC_In & E_STOP_NC_Mask) != 0)
#define eStopNcSet() PORTF |= E_STOP_NC_Mask
#define eStopNcClr() PORTF &= ~E_STOP_NC_Mask

#define E_STOP_RST_Pin 8
#define E_STOP_RST_In PORTB
#define E_STOP_RST_Bit PB4
#define E_STOP_RST_Mask _BV(E_STOP_RST_Bit)
#define eStopRstIn() ((E_STOP_RST_In & E_STOP_RST_Mask) == 0)
#define eStopRstClr() PORTB |= E_STOP_RST_Mask
#define eStopRstSet() PORTB &= ~E_STOP_RST_Mask

#define FAST_PWM_Pin 9
#define FAST_PWM_Port PORTB
#define FAST_PWM_DDR DDRB
#define FAST_PWM_In PINB
#define FAST_PWM_Bit PB5
#define FAST_PWM_Mask _BV(FAST_PWM_Bit)
#define fastPwmRead() ((FAST_PWM_Port & FAST_PWM_Mask) != 0)
#define fastPwmSet() FAST_PWM_Port |= FAST_PWM_Mask
#define fastPwmClr() FAST_PWM_Port &= ~FAST_PWM_Mask

#define VFD_FWD_Pin 6
#define VFD_FWD_Port PORTD
#define VFD_FWD_DDR DDRD
#define VFD_FWD_In PIND
#define VFD_FWD_Bit PD7
#define VFD_FWD_Mask _BV(VFD_FWD_Bit)
#define vfdFwdRead() ((VFD_FWD_Port & VFD_FWD_Mask) != 0)
#define vfdFwdSet() VFD_FWD_Port |= VFD_FWD_Mask
#define vfdFwdClr() VFD_FWD_Port &= ~VFD_FWD_Mask

#define VFD_REV_Pin 7
#define VFD_REV_Port PORTE
#define VFD_REV_DDR DDRE
#define VFD_REV_In PINE
#define VFD_REV_Bit PE6
#define VFD_REV_Mask _BV(VFD_REV_Bit)
#define vfdRevRead() ((VFD_REV_Port & VFD_REV_Mask) != 0)
#define vfdRevSet() VFD_REV_Port |= VFD_REV_Mask
#define vfdRevClr() VFD_REV_Port &= ~VFD_REV_Mask

#define SP_ENA_Pin 14
#define SP_ENA_Port PORTB
#define SP_ENA_DDR DDRB
#define SP_ENA_In PINB
#define SP_ENA_Bit PB3
#define SP_ENA_Mask _BV(SP_ENA_Bit)
#define spEnaRead() ((SP_ENA_Port & SP_ENA_Mask) != 0)
#define spEnaSet() SP_ENA_Port |= SP_ENA_Mask
#define spEnaClr() SP_ENA_Port &= ~SP_ENA_Mask

#define STEP_DIS_Pin 15
#define STEP_DIS_Port PORTB
#define STEP_DIS_DDR DDRB
#define STEP_DIS_In PINB
#define STEP_DIS_Bit PB1
#define STEP_DIS_Mask _BV(STEP_DIS_Bit)
#define stepDisRead() ((STEP_DIS_Port & STEP_DIS_Mask) != 0)
#define stepDisSet() STEP_DIS_Port |= STEP_DIS_Mask
#define stepDisClr() STEP_DIS_Port &= ~STEP_DIS_Mask

#define E_STOP_RLY_Pin 17
#define E_STOP_RLY_Port PORTB
#define E_STOP_RLY_DDR DDRB
#define E_STOP_RLY_In PINB
#define E_STOP_RLY_Bit PB0
#define E_STOP_RLY_Mask _BV(E_STOP_RLY_Bit)
#define eStopRlyRead() ((E_STOP_RLY_Port & E_STOP_RLY_Mask) != 0)
#define eStopRlySet() E_STOP_RLY_Port |= E_STOP_RLY_Mask
#define eStopRlyClr() E_STOP_RLY_Port &= ~E_STOP_RLY_Mask

#define E_STOP_PC_Pin 16
#define E_STOP_PC_Port PORTB
#define E_STOP_PC_DDR DDRB
#define E_STOP_PC_In PINB
#define E_STOP_PC_Bit PB2
#define E_STOP_PC_Mask _BV(E_STOP_PC_Bit)
#define eStopPcRead() ((E_STOP_PC_Port & E_STOP_PC_Mask) != 0)
#define eStopPcSet() E_STOP_PC_Port |= E_STOP_PC_Mask
#define eStopPcClr() E_STOP_PC_Port &= ~E_STOP_PC_Mask

#define W_DOG_Pin 10
#define W_DOG_Port PORTB
#define W_DOG_DDR DDRB
#define W_DOG_In PINB
#define W_DOG_Bit PB6
#define W_DOG_Mask _BV(W_DOG_Bit)
#define wDogRead() ((W_DOG_Port & W_DOG_Mask) != 0)
#define wDogSet() W_DOG_Port |= W_DOG_Mask
#define wDogClr() W_DOG_Port &= ~W_DOG_Mask

#define ledRead() 0
#define ledSet()
#define ledClr()

#define t2Read() 0
#define t2Set()
#define t2Clr()

#define dbg0Read() 0
#define dbg0Set()
#define dbg0Clr()

#define dbg1Read() 0
#define dbg1Set()
#define dbg1Clr()

#define dbg2Read() 0
#define dbg2Set()
#define dbg2Clr()

#endif
