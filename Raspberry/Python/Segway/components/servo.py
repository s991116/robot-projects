from arduinoCom.commands import arduinoCommands

class servo(object):

    def __init__(self, protocol):
        self.protocol = protocol
        self.horizontalMax = 160
        self.horizontalMin = 40
        self.verticalMax = 160
        self.verticalMin = 40        
        return
        
    def setVerticalPosition(self, position):
        position = self.__clamp(position, self.verticalMin, self.verticalMax)
        self.protocol.sendCharData(arduinoCommands.SERVO_VERTICAL_BYTE(), [position])

    def getVerticalPosition(self):
        return self.protocol.RequestChar(arduinoCommands.SERVO_VERTICAL_BYTE(), 1)[0]
        
    def moveRight(self):
        pos = self.getHorizontalPosition() + 4
        self.setHorizontalPosition(pos)

    def moveLeft(self):
        pos = self.getHorizontalPosition() - 4
        self.setHorizontalPosition(pos)
        
    def setHorizontalPosition(self, position):
        position = self.__clamp(position, self.horizontalMin, self.horizontalMax)
        self.protocol.sendCharData(arduinoCommands.SERVO_HORIZONTAL_BYTE(), [position])

    def getHorizontalPosition(self):
        return self.protocol.RequestChar(arduinoCommands.SERVO_HORIZONTAL_BYTE(), 1)[0]

    def moveUp(self):
        pos = self.getVerticalPosition() + 4
        self.setVerticalPosition(pos)

    def moveDown(self):
        pos = self.getVerticalPosition() - 4
        self.setVerticalPosition(pos)
        
    def setServoSpeed(self, vertical, horizontal):
        self.protocol.sendCharData(arduinoCommands.SERVO_SPEED_BYTE(), [vertical, horizontal])

    def getVerticalSpeed(self):
        return self.protocol.RequestChar(arduinoCommands.SERVO_SPEED_BYTE(), 2)[0]

    def getHorizontalSpeed(self):
        return self.protocol.RequestChar(arduinoCommands.SERVO_SPEED_BYTE(), 2)[1]
        
    def __clamp(self, n, minn, maxn):
        if n < minn:
            return minn
        elif n > maxn:
            return maxn
        else:
            return n
        