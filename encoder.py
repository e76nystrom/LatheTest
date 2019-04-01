#!/cygdrive/c/Python27/Python.exe

class CmpTmr():
    def __init__(self):
        self.state = 0
        self.stateTbl = \
            (self.state0, self.state1, self.state2, self.state3, \
             self.state4)
        
        self.encCycle = 5
        self.encCount = 0

        self.clockCounter = 0
        self.encoderClocks = 0
        self.encCLocks = 0

        self.cycleClocks = 0

    def clock(self, encPulse = False):
        self.clockCounter += 1
        if encPulse:
            self.encoderClocks = self.clockCounter
            self.clockCounter = 0;
            self.state = 1
        else:
            if self.state != 0:
                self.stateTbl[self.statte]()

    def state0(self):
        pass

    def state1(self):
        self.clockTotal += self.encoderClocks
        self.Pulse -= 1
        if encCount > 0:
            self.state = 2
        else:
            self.state = 3

    def state2(self):
        self.cycleClocks = self.clockTotal + \
                           self.encoderClocks * self.encCount
        self.state = 1

    def state3(self):
        self.cycleClocks = self.encoderClocks
        self.encoderClocks = 0
        if self.startInt:
            self.state = 4
        else:
            self.state = 1

    def state4(self):
        self.startInt = False

class IntTmr():
    def __init__(self):
        pass

cmpTmr = CmpTmr()
for i in range(100):
    for k in range(50):
        cmpTmr.clockk()
    cmpTmr.clock(True)
