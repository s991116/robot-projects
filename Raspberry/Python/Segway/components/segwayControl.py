from arduinoCom.commands import arduinoCommands

class segwayControl(object):

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
        self.protocol.sendCharData(arduinoCommands.SEGWAY_SPEED_FACTOR_BYTE(), [speedFactor])
        
    def getSpeedFactor(self):
        return self.protocol.RequestChar(arduinoCommands.SEGWAY_SPEED_FACTOR_BYTE(), 1)[0]
        
    def setSegwaySpeed(self, segwaySpeed):
        self.protocol.sendCharData(arduinoCommands.SEGWAY_SPEED_BYTE(), [segwaySpeed+127])

    def getSegwaySpeed(self):
        return self.protocol.RequestChar(arduinoCommands.SEGWAY_SPEED_BYTE(), 1)[0]-127

    def setSegwayTurnSpeed(self, segwayTurnSpeed):
        self.protocol.sendCharData(arduinoCommands.SEGWAY_TURN_BYTE(), [segwayTurnSpeed+127])

    def getSegwayTurnSpeed(self):
        return self.protocol.RequestChar(arduinoCommands.SEGWAY_TURN_BYTE(), 1)[0]-127
