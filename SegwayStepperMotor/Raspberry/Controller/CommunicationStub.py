
class CommunicationStub:

    cmd = 0
    data = 0

    def SendData(self,cmd,data):
        self.cmd = cmd
        self.data = data

    def GetData(self,cmd):
        self.cmd = cmd
        return 0