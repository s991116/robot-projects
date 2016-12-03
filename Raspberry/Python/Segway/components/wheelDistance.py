from arduinoCom.commands import arduinoCommands

class wheelDistance(object):

    def __init__(self, protocol):
        self.protocol = protocol
        return

    def getDistance(self):
        self.protocol.RequestShort(arduinoCommands.DISTANCE(), 2)

    def getDistanceAndReset(self):
        self.protocol.RequestShort(arduinoCommands.DISTANCE_RESET(), 2)