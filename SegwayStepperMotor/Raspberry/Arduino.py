import Commands

class Arduino:
    def __init__(self, communication):
        self.communication = communication

    def SetPID(self, p,i,d):
        self.communication.SendData(Commands.CMD_SET_PID_P_LEVEL, p*4)
        self.communication.SendData(Commands.CMD_SET_PID_I_LEVEL, i*4)
        self.communication.SendData(Commands.CMD_SET_PID_D_LEVEL, d*4)

    def SetTest(self, testData):
        self.communication.SendData(Commands.CMD_SET_TEST_VALUE, testData)

    def GetTest(self):
        return self.communication.GetData(Commands.CMD_GET_TEST_VALUE)
