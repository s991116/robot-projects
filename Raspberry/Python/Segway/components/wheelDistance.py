from arduinoCom.commands import arduinoCommands
from arduinoCom.numericalConverter import numericalConverter

class wheelDistance(object):

    def __init__(self, protocol):
        self.protocol = protocol
        return

    def getDistance(self):
        return map(numericalConverter.ToSignedShort, self.protocol.RequestShort(arduinoCommands.DISTANCE(), 2))
        
    def getDistanceAndReset(self):
        return map(numericalConverter.ToSignedShort, self.protocol.RequestShort(arduinoCommands.DISTANCE_RESET(), 2))
