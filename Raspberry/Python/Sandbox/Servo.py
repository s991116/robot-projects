from ArduinoCommands import ArduinoCommands

class Servo(object):

    def __init__(self, protocol):
        self.protocol = protocol
        self.horizontalMax = 160
        self.horizontalMin = 40
        self.verticalMax = 160
        self.verticalMin = 40        
        return
        
    def setVerticalPosition(self, position):
        position = self.__clamp(position, self.verticalMin, self.verticalMax)
        self.protocol.sendCharData(ArduinoCommands.SERVO_VERTICAL_BYTE(), [position])

    def setHorizontalPosition(self, position):
        position = self.__clamp(position, self.horizontalMin, self.horizontalMax)
        self.protocol.sendCharData(ArduinoCommands.SERVO_HORIZONTAL_BYTE(), [position])

    def __clamp(self, n, minn, maxn):
        if n < minn:
            return minn
        elif n > maxn:
            return maxn
        else:
            return n
        