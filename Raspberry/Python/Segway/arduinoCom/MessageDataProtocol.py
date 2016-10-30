class Protocol(object):
    
    def sendCharData(self, commandId, data):
        response = [0] * (1 + 2*len(data))
        response[0] = commandId + 128
        for index in range(0, len(data)):
            response[2*index+1] = (data[index] & 15)
            response[2*index+2] = (data[index] >> 4 + ((len(data)-1) << 4))
        return response

    def sendShortData(self, commandId, data):
        response = [0] * (1 + 4*len(data))
        response[0] = commandId + 128
        for index in range(0, len(data)):
            response[4*index+1] = (data[index] & 31)
            response[4*index+2] = ((data[index] & 255) >> 4 + ((len(data)-1) << 4))
            response[4*index+3] = ((data[index] >> 8) & 31)
            response[4*index+4] = (data[index] >> 12 + ((len(data)-1) << 4))
        return response
        
    def RequestChar(self, commandId, length):
        response = [0] * 3
        response[0] = commandId + 128
        response[1] = 96
        response[2] = (length-1) << 4
        return response
        
    def RequestShort(self, commandId, length):
        response = [0] * 3
        response[0] = commandId + 128
        response[1] =  112
        response[2] = (length-1) << 4
        return response
        
    def GetResponse(self, responseArray):
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