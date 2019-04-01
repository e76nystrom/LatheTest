#!/cygdrive/c/Python27/Python.exe

from sys import stdout

debug = False

class Config():
        def readPins(self, pinList):
            global pins, ports
            pins = {}
            ports = {}
            for i in range(len(pinList)):
                data = pinList[i]
                (pin, port) = data
                pins[pin] = port
                ports[port] = pin
                # print "pin %2d port %s" % (pin, port)

        def readAlt(self, altList):
            global pins, ports, functions
            functions = {}
            for i in range(len(altList)):
                data = altList[i]
                (function, port) = data
                try:
                    pin = int(ports[port])
                except KeyError:
                    pin = -1
                functions[function] = port
                # print "function %6s port %s pin %d" % (function, port, pin)
                if function.startswith("OC"):
                    p = port[1:2]
                    portName = "PIN" + p
                    portMask = "_BV(" + port + ")"
                    f.write("#define %s_Port %s\n" % (function, portName))
                    f.write("#define %s_Mask %s\n" % (function, portMask))
                    f.write("\n")

        def varName(self, name):
            varName = name.lower()
            tmp = varName.split("_")
            if len(tmp) > 1:
                varName = ""
                first = True
                for s in tmp:
                    if first:
                        varName = s.lower()
                        first = False
                    else:
                        varName = varName + s[0].upper() + s[1:].lower()
            return(varName)

        def outPin(self, name, pin):
            global f, f1, pins, debug
            funcName = self.varName(name)
            if not pin in pins:
                f.write(("#define %sRead() 0\n" % \
                         (funcName)))
                f.write(("#define %sSet()\n" % \
                         (funcName)))
                f.write(("#define %sClr()\n" % \
                         (funcName)))
                return
            port = pins[pin]
            p = port[1:2]
            portName = "PORT" + p
            portDDR = "DDR" + p
            portIn = "PIN" + p
            configPin = name + "_Pin"
            configPort = name + "_Port"
            configDDR = name + "_DDR"
            configBit = name + "_Bit"
            configIn = name + "_In"
            configMask = name + "_Mask"
            mask = "_BV(" + configBit + ")"
            if debug:
                f1.write(" puts(F(\"%-10s %2d %s out\\n\"));\n" % (name, pin, port));
            f1.write(" pinMode(%s, OUTPUT);\n" % (configPin))
            f.write("#define %s %s\n" % (configPin, pin))
            f.write("#define %s %s\n" % (configPort, portName))
            f.write("#define %s %s\n" % (configDDR, portDDR))
            f.write("#define %s %s\n" % (configIn, portIn))
            f.write("#define %s_Bit %s\n" % (name, port))
            f.write("#define %s %s\n" % (configMask, mask))
            f.write(("#define %sRead() ((%s & %s) != 0)\n" % \
                     (funcName, configPort, configMask)))
            f.write(("#define %sSet() %s |= %s\n" % \
                     (funcName, configPort, configMask)))
            f.write(("#define %sClr() %s &= ~%s\n" % \
                     (funcName, configPort, configMask)))

        def inPin(self, name, pin, option=None):
            global f, f1, pins, debug
            funcName = self.varName(name)
            options = {}
            if option != None:
                for i in option:
                    options[i.strip()] = 1
            port = pins[pin]
            p = port[1:2]
            portName = "PORT" + p
            # portDDR = "DDR" + p
            portIn = "PIN" + p
            configPin = name + "_Pin"
            configIn = name + "_In"
            configBit = name + "_Bit"
            configMask = name + "_Mask"
            mask = "_BV(" + configBit + ")"
            mode = "INPUT"
            if 'test' in options:
                mode = "OUTPUT"
                portIn = portName
            high = True
            if 'low' in options:
                high = False
            if debug:
                f1.write(" puts(F(\"%-10s %2d %s in\\n\"));\n" % (name, pin, port));
            f1.write(" pinMode(%s, %s);\n" % (configPin, mode))
            f.write("#define %s %s\n" % (configPin, pin))
            f.write("#define %s %s\n" % (configIn, portIn))
            f.write("#define %s_Bit %s\n" % (name, port))
            f.write("#define %s_Mask %s\n" % (name, mask))
            f.write("#define %sIn() ((%s & %s) %s= 0)\n" % \
                    (funcName, configIn, configMask, ('=', '!')[high]))
            if 'test' in options:
                polarity = ('Clr', 'Set')
                f.write(("#define %s%s() %s |= %s\n" % \
                         (funcName, polarity[high], portName, configMask)))
                f.write(("#define %s%s() %s &= ~%s\n" % \
                         (funcName, polarity[not high], portName, configMask)))

        def extiPin(self, name, pin, option):
            global f, f1, pins, functions
            port = pins[pin]
            if len(option) == 1:
                option = option[0].strip()
            for key, val in functions.items():
                if val == port and key.startswith("INT"):
                    intNum = int(key[3])
                    reg = "EICR" + ("A", "B")[intNum >= 4]
                    # print "'%s'" % option
                    try:
                        mask = {'low' : '0',
                                'change' : '_BV(ISC00)',
                                'falling' : '_BV(ISC01)',
                                'rising' : '_BV(ISC01)|_BV(ISC00)'}[option]
                    except KeyError:
                        mask = '0'
                    shift = (intNum & 3) * 2
                    val = "(%s) << %d" % (mask, shift)
                    stm0 = "%s &= ~((_BV(ISC01) | _BV(ISC00)) << %d)" % \
                           (reg, shift)
                    stm1 = "%s |= %s" % (reg, val)
                    stm2 = "EIMSK |= (_BV(INT0) << %d)" % (intNum)
                    f.write("#define %sIntInit() %s;\\\n\t%s;\\\n\t%s\n" % \
                            (self.varName(name), stm0, stm1, stm2))

        def readConfig(self,config):
            used = {}
            for i in range(len(config)):
                data = config[i]
                (name, pin, dir) = data
                tmp = dir.split(",")
                option = None
                if len(tmp) > 1:
                    dir = str(tmp[0])
                    option = tmp[1:]
                    dir = dir.strip()
                # print "%10s pin %2d dir %s" % (name, pin, dir)
                if pin in pins:
                    if pin in used:
                        (first, firstDir) = used[pin]
                        if firstDir != dir:
                            print "%s pin %d already used for %s" % (name, pin, first)
                    else:
                        used[pin] = (name, dir)
                if dir == "out":
                    self.outPin(name, pin)
                    f.write("\n")
                elif dir == "in":
                    self.inPin(name, pin, option)
                    f.write("\n")
                elif dir == "exti":
                    self.inPin(name, pin)
                    self.extiPin(name, pin, option)
                    f.write("\n")


cfg = __import__("lathe")

fName = cfg.outFile

f = open(fName + '.h', 'w')
f.write("extern void pinConfig();\n\n")

f1 = open(fName + '.cpp', 'w')
f1.write("#include <Arduino.h>\n")
f1.write("#include \"%s.h\"\n" % (fName))
f1.write("#include \"serial.h\"\n")
f1.write("\nvoid pinConfig()\n{\n")

for configDef in cfg.commonDefines:
    (name, value) = configDef
    f.write("#define %-20s %s\n" % (name, value))

for info in cfg.pinConfig:

    pins = None
    analog = None
    ports = None
    functions = None

    procType = info['type']
    f.write("\n#ifdef %s\n\n" % (procType))
    f1.write("\n#ifdef %s\n\n" % (procType))

    defines = info['defines']
    for configDef in defines:
        (name, value) = configDef
        f.write("#define %-20s %s\n" % (name, value))
    f.write("\n")

    boardDef = info['def']
    board = __import__(boardDef)

    c = Config()
    c.readPins(board.digitalDef)
    c.readAlt(board.altDef)

    config = info['config']
    c.readConfig(config)

    f1.write("\n#endif\n")
    f.write("#endif\n")

#f.write("#endif\n")
f.close()

#f1.write("\n#endif\n")
f1.write("}\n")
f1.close()
