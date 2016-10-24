import array

class SerialProtocol(object):
    
    def __init__(self, serial):
        self.serial = serial
        return
        
    def sendCharData(self, commandId, data):
        request = [0] * (1 + 2*len(data))
        request[0] = commandId + 128
        for index in range(0, len(data)):
            request[2*index+1] = (data[index] & 15)
            request[2*index+2] = (data[index] >> 4 + ((len(data)-1) << 4))
        self.__writeDataToSerial(request)
        
    def sendShortData(self, commandId, data):
        request = [0] * (1 + 4*len(data))
        request[0] = commandId + 128
        for index in range(0, len(data)):
            request[4*index+1] = (data[index] & 31)
            request[4*index+2] = ((data[index] & 255) >> 4 + ((len(data)-1) << 4))
            request[4*index+3] = ((data[index] >> 8) & 31)
            request[4*index+4] = (data[index] >> 12 + ((len(data)-1) << 4))
        self.__writeDataToSerial(request)

    def RequestChar(self, commandId, length):
        request = [0] * 3
        request[0] = commandId + 128
        request[1] = 32
        request[2] = (length-1) << 4
        self.__writeDataToSerial(request)
        response = self.__readSerialResponse()
        return self.__getResponse(response)

    def RequestShort(self, commandId, length):
        request = [0] * 3
        request[0] = commandId + 128
        request[1] =  32+16
        request[2] = (length-1) << 4
        self.__writeDataToSerial(request)
        response = self.__readSerialResponse()
        return self.__getResponse(response)
    
    def __readSerialResponse(self):
        firstPart = self.serial.read(3)
        dataType = (firstPart[1] >> 4) & 1
        length = firstPart[2] >> 4
        if(dataType == 0):
            bytesToRead = length*2
        else:
            bytesToRead = 2+length*4        
        secondPart = self.serial.read(bytesToRead)
        result = firstPart + secondPart
        return bytearray(result)
    
    def __getResponse(self, responseArray):
        commandId = responseArray[0]-128
        dataType = (responseArray[1] >> 4) & 1
        length = (responseArray[2] >> 4 & 7)+1
        response = [0] * length
        if(dataType == 0):
            for index in range(0, length):
                response[index] = (responseArray[1+index*2] & 15) + ((responseArray[2+index*2] & 15) << 4)
        else:
            for index in range(0, length):
                LSB_Low  = (responseArray[1+index*4] & 15)
                LSB_High = (responseArray[2+index*4] & 15) << 4
                MSB_Low  = (responseArray[3+index*4] & 15) << 8
                MSB_High = (responseArray[4+index*4] & 15) << 12
                response[index] = LSB_Low + LSB_High + MSB_Low + MSB_High

        return response    

    def __writeDataToSerial(self, data):
        serialArray = array.array('B', data)
        self.serial.write(serialArray)
    
