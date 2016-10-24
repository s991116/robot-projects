from ArduinoCommands import ArduinoCommands
from numericalConverter import numericalConverter

class Gyro(object):

    def __init__(self, protocol):
        self.protocol = protocol
        return
        
    def enableGyro(self):
        self.protocol.sendCharData(ArduinoCommands.SEGWAY_ENABLED_BYTE(),[1])

    def disableGyro(self):
        self.protocol.sendCharData(ArduinoCommands.SEGWAY_ENABLED_BYTE(),[0])

    def setPidGyroAccelration(self, P, I, D):
        self.protocol.sendShortData(ArduinoCommands.PID_GYRO_SHORT(), [P, I, D])

    def getPidGyroAccelration(self):
        return self.protocol.RequestShort(ArduinoCommands.PID_GYRO_SHORT(), 3)
        
    def setPidGyroSpeed(self, P, I, D):
        self.protocol.sendShortData(ArduinoCommands.PID_SPEED_SHORT(), [P, I, D])
        
    def getPidGyroSpeed(self):
        return self.protocol.RequestShort(ArduinoCommands.PID_SPEED_SHORT(), 3)
        
    def angleOffset(self):
        return self.protocol.RequestShort(ArduinoCommands.ANGLE_OFFSET_SHORT(), 1)[0]
        
    def measure(self):
        return map(numericalConverter.ToSignedShort, self.protocol.RequestShort(ArduinoCommands.GYRO_MEASURE_SHORT(), 2))