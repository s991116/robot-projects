from arduinoCom.commands import arduinoCommands

class motor(object):

    def __init__(self, protocol):
        self.protocol = protocol
        return

    def setPidMotorA(self, P, I, D):
        self.protocol.sendShortData(arduinoCommands.PID_ENCODER_A_SHORT(), [P, I, D])

    def setPidMotorB(self, P, I, D):
        self.protocol.sendShortData(arduinoCommands.PID_ENCODER_B_SHORT(), [P, I, D])
