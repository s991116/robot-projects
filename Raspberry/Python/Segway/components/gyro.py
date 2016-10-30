from arduinoCom.commands import arduinoCommands
from arduinoCom.numericalConverter import numericalConverter

class gyro(object):

    def __init__(self, protocol):
        self.protocol = protocol
        return
        
    def enableGyro(self):
        self.protocol.sendCharData(arduinoCommands.SEGWAY_ENABLED_BYTE(),[1])

    def disableGyro(self):
        self.protocol.sendCharData(arduinoCommands.SEGWAY_ENABLED_BYTE(),[0])

    def setPidGyroAccelration(self, P, I, D):
        self.protocol.sendShortData(arduinoCommands.PID_GYRO_SHORT(), [P, I, D])

    def getPidGyroAccelration(self):
        return self.protocol.RequestShort(arduinoCommands.PID_GYRO_SHORT(), 3)
        
    def setPidGyroSpeed(self, P, I, D):
        self.protocol.sendShortData(arduinoCommands.PID_SPEED_SHORT(), [P, I, D])
        
    def getPidGyroSpeed(self):
        return self.protocol.RequestShort(arduinoCommands.PID_SPEED_SHORT(), 3)
        
    def angleOffset(self):
        return self.protocol.RequestShort(arduinoCommands.ANGLE_OFFSET_SHORT(), 1)[0]
        
    def measure(self):
        return map(numericalConverter.ToSignedShort, self.protocol.RequestShort(arduinoCommands.GYRO_MEASURE_SHORT(), 2))