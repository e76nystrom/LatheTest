#!/cygdrive/c/Python37/Python.exe

defineMega = \
[\
 ["ENCODER_TEST", 1],
 ["INDEX_TEST", 0],
]

pinsMega = \
[\
 ["A",    22, "out"],
 ["B",    23, "out"],
 ["SYNC", 24, "out"],
 ["PULSE", 25, "out"],
 ["INDEX", 9, "out"],
 ["T2",    8, "out"],
 ["T1_PWM_A", 11, "out"],
 ["T3_PWM_A",  5, "out"],       # spindle pwm simulator
 ["T4_PWM_A",  6, "out"],       # charge pump simulator

 ["CHG_PUMP", 20, ("exti, rising")],
 ["PWM",      21, ("exti, change")],

 ["SP_FWD",     54, "in, test"],
 ["SP_REV",     55, "in, test"],
 ["E_STOP_NO",  56, "in, test"],
 ["E_STOP_NC",  57, "in, test"],
 ["E_STOP_RST", 58, "in, test, low"],

 ["FAST_PWM",   11, "out"],
 ["VFD_FWD",    14, "out"],
 ["VFD_REV",    15, "out"],
 ["SP_ENA",     16, "out"],
 ["STEP_DIS",   17, "out"],
 ["E_STOP_RLY", 50, "out"],
 ["E_STOP_PC",  52, "out"],
 ["W_DOG",       2, "out"],

 ["LED",        13, "out"],     # built in led
 ["DBG0",       26, "out"],
 ["DBG1",       27, "out"],
 ["DBG2",       28, "out"],
]

defineMini = \
[\
 ["ENCODER_TEST", 1],
 ["INDEX_TEST", 0],
]

pinsMini = \
[\
 ["A",    12, "out"],
 ["B",    11, "out"],
 ["SYNC", 13, "out"],
 ["PULSE", -1, "out"],

 ["T1_PWM_A",  9, "out"],

 ["LED",        -1, "out"],     # built in led
 ["T2",         -1, "out"],
 ["DBG0",       -1, "out"],
 ["DBG1",       -1, "out"],
 ["DBG2",       -1, "out"],
]

defineMicro = \
[\
 ["ENCODER_TEST", 0],
 ["INDEX_TEST", 0],

 ["SPINDLE_PWM_TEST", 0],
 ["CHARGE_PUMP_TEST", 0],

 ["TMR2_MS_TIMER", 0],
 ["TMR3_MS_TIMER", 1],
]

pinsMicro = \
[\
 ["T1_PWM_A",  9, "out"],

 ["CHG_PUMP",  2, ("exti, rising")],
 ["PWM",       3, ("exti, change")],

 ["SP_FWD",      4, "in, test"],
 ["SP_REV",      5, "in, test"],
 ["E_STOP_NO",  18, "in, test"],
 ["E_STOP_NC",  19, "in, test"],
 ["E_STOP_RST",  8, "in, test, low"],

 ["FAST_PWM",    9, "out"],
 ["VFD_FWD",     6, "out"],
 ["VFD_REV",     7, "out"],
 ["SP_ENA",     14, "out"],
 ["STEP_DIS",   15, "out"],
 ["E_STOP_RLY", 17, "out"],
 ["E_STOP_PC",  16, "out"],
 ["W_DOG",      10, "out"],

 ["LED",        -1, "out"],     # built in led
 ["T2",         -1, "out"],
 ["DBG0",       -1, "out"],
 ["DBG1",       -1, "out"],
 ["DBG2",       -1, "out"],
]

outFile = "config"

commonDefines = \
[\
 ["DEBUG", 1],
 ["CONSOLE", 1],
 ["FLASH_STRINGS", 1],
]

configMega = {'def' : 'mega',
              'type' : 'ARDUINO_AVR_MEGA2560',
              'defines' : defineMega,
              'config' : pinsMega}

configMini = {'def' : 'mini',
              'type' : 'ARDUINO_AVR_PRO',
              'defines' : defineMini,
              'config' : pinsMini}

configMicro = {'def' : 'mini32u4',
               'type' : 'ARDUINO_AVR_PROMICRO16',
               'defines' : defineMicro,
               'config' : pinsMicro}

pinConfig = [configMega, configMini, configMicro]
