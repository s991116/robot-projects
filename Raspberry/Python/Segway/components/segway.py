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
        return self.dataProtocol.RequestChar(arduinoCommands.SEGWAY_ENABLED_BYTE(),1)[0]
