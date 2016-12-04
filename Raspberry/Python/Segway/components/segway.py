from arduinoCom.commands import arduinoCommands

class segway(object):

    def __init__(self, protocol):
        self.protocol = protocol 
        return
        
    def enable(self):
        self.protocol.sendCharData(arduinoCommands.SEGWAY_ENABLED_BYTE(), [1])

    def disable(self):
        self.protocol.sendCharData(arduinoCommands.SEGWAY_ENABLED_BYTE(), [0])
        
    def isEnabled(self):
        return self.protocol.RequestChar(arduinoCommands.SEGWAY_ENABLED_BYTE(),1)[0]

    def setSpeedFactor(self, speedFactor):
        self.protocol.sendCharData(arduinoCommands.SEGWAY_SPEED_FACTOR(), [speedFactor])
        
    def getSpeedFactor(self):
        return self.protocol.RequestChar(arduinoCommands.SEGWAY_SPEED_FACTOR(), 1)[0]