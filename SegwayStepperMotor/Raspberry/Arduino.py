import Commands
import ArduinoCommunication

class Arduino:
    def __init__(self, communication):
        self.communication = communication

    @classmethod
    def GetArduinoController(cls):
        arduinoCom = ArduinoCommunication.ArduinoCommunication()
        return cls(arduinoCom)

    def SetPID(self, p,i,d):
        self.communication.SendData(Commands.CMD_SET_PID_P_LEVEL, p*4)
        self.communication.SendData(Commands.CMD_SET_PID_I_LEVEL, i*4)
        self.communication.SendData(Commands.CMD_SET_PID_D_LEVEL, d*4)

    def SetTest(self, testData):
        self.communication.SendData(Commands.CMD_SET_TEST_VALUE, testData)

    def SetBalanceMode(self, mode):
        self.communication.SendData(Commands.CMD_SET_ENABLE_BALANCE, mode)

    def GetTest(self):
        return self.communication.GetData(Commands.CMD_GET_TEST_VALUE)

    def GetBatteryLevel(self):
        return self.communication.GetData(Commands.CMD_GET_BATTERY_LEVEL)

    def Direction(self, forward, leftRight):
        directionData = 0
        if(forward == 1):
            directionData = 4
        
        if(forward == -1):
            directionData = 8

        if(leftRight == -1):
            directionData = directionData + 1

        if(leftRight == 1):
            directionData = directionData + 2

        self.communication.SendData(Commands.CMD_SET_MOVEMENT,directionData)
