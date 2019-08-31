import serial
import Commands

class ArduinoCommunication:
    def __init__(self):
        self.port = serial.Serial(port='/dev/serial0')

    def Reset(self):
        self.port.reset_input_buffer()
        self.port.reset_output_buffer()

    def SendData(self,cmd,data):
        cmd = cmd+Commands.CMD_TYPE_SET_VALUE
        cmd = self.__byteRange__(cmd)
        data = self.__byteRange__(data)
        self.port.write([cmd,data])

    def GetData(self,cmd):
        cmd = cmd+Commands.CMD_TYPE_GET_VALUE
        cmd = self.__byteRange__(cmd)
        self.port.write([cmd])
        while(self.port.in_waiting<1):
            pass
        receive = self.port.read(1)
        return ord(receive)
   
    def __byteRange__(self, value):
        value = round(value,0)
        return max(0, min(255, int(value)))