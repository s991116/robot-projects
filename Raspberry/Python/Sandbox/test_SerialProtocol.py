import unittest
import serialProtocol
import mock
import array

class SerialMock():
    def __init__(self):
        self.length = 0
    
    def read(self, length=1):
        result = self.readData[0:length]
        self.readData = self.readData[length:len(self.readData)]
        self.length = self.length - length
        return result
        
    def write(self, data):
        self.writtenData = data
    
    def inWaiting(self):
        return self.length

    def dataToRead(self, data):
        self.readData = data
        length = len(data)        
        return
        
class SerialFixture():
    def CreateTarget(self):
        self.serialMock = SerialMock()
        return serialProtocol.serialProtocol(self.serialMock)

    def SetupReceivedShortDataFromSerial(self, commandId, expectedResponse):
        length = len(expectedResponse)-1
        LowByteLowPart_1    =  expectedResponse[0] & 15
        LowByteHighPart_1   = (expectedResponse[0] >> 4) & 15
        HighByteLowPart_1   = (expectedResponse[0] >> 8) & 15
        HighByteHighPart_1  = (expectedResponse[0] >> 12) & 15
        LowByteLowPart_2    =  expectedResponse[1] & 15
        LowByteHighPart_2   = (expectedResponse[1] >> 4) & 15
        HighByteLowPart_2   = (expectedResponse[1] >> 8) & 15
        HighByteHighPart_2  = (expectedResponse[1] >> 12) & 15
        responseArray = [128+commandId, 32+16+(LowByteLowPart_1), ((length) << 4) + (LowByteHighPart_1), HighByteLowPart_1 ,HighByteHighPart_1, LowByteLowPart_2, LowByteHighPart_2, HighByteLowPart_2 ,HighByteHighPart_2 ]
        self.serialMock.dataToRead(responseArray)

    def SetupReceivedCharDataFromSerial(self, commandId, expectedResponse):
        length = len(expectedResponse)-1
        responseArray = [128+commandId,
                 32+(expectedResponse[0] & 15),
                 (length << 4) + (expectedResponse[0] >> 4),
                 32+(expectedResponse[1] & 15), 
                 (length << 4) + (expectedResponse[1] >> 4)]
        self.serialMock.dataToRead(responseArray)

        
    def WrittenDataToSerial(self):
        bytedata = self.serialMock.writtenData
        written = []
        for index in range(0, len(self.serialMock.writtenData)):
            written.append(self.serialMock.writtenData[index])
        return written
        

class Test(unittest.TestCase):

    def setUp(self):
        pass
        
    def test_Protocol_Send_Char_Data(self):
        #Arrange
        fixture = SerialFixture()
        sut = fixture.CreateTarget()
        commandId = 122
        data = [112, 41]

        #Act
        sut.sendCharData(commandId, data)

        #Assert
        expectedData = [128+commandId, 
                        data[0] & 15,
                        data[0] >> 4 + 16,
                        data[1] & 15,
                        data[1] >> 4 + 16]
        written = fixture.WrittenDataToSerial()
        self.assertListEqual(written, expectedData)
                
    def test_Protocol_Send_Short_Data(self):
        #Arrange
        fixture = SerialFixture()
        sut = fixture.CreateTarget()

        commandId = 42
        data = [2222, 3333]

        #Act
        sut.sendShortData(commandId, data)

        #Assert
        expectedData = [128+commandId,
                        ((data[0] & 255) & 15) + 16,
                        ((data[0] & 255) >> 4) + 16,
                        ((data[0] >> 8) & 15),
                        ((data[0] >> 8) >> 4),
                        ((data[1] & 255) & 15) + 16,
                        ((data[1] & 255) >> 4) + 16,
                        ((data[1] >> 8) & 15),
                        ((data[1] >> 8) >> 4)]
                
        written = fixture.WrittenDataToSerial()
        self.assertListEqual(written, expectedData)

    def test_Protocol_Request_Char_Data(self):
        #Arrange
        fixture = SerialFixture()
        sut = fixture.CreateTarget()

        commandId = 42        
        length = 1
        expectedResponse = [42, 222]

        fixture.SetupReceivedCharDataFromSerial(commandId, expectedResponse)
        
        #Act
        response = sut.RequestChar(commandId, length)
        
        #Assert
        expectedData = [128+commandId,
                        32,
                        (length-1) << 4]
 
        written = fixture.WrittenDataToSerial()
        self.assertListEqual(written, expectedData)


    def test_Protocol_Request_Short_Data(self):
        #Arrange
        fixture = SerialFixture()
        sut = fixture.CreateTarget()
        expectedResponse = [2222, 4444]
        commandId = 42        
        length = 2
                
        fixture.SetupReceivedShortDataFromSerial(commandId, expectedResponse)

        #Act
        d = sut.RequestShort(commandId, length)
        
        #Assert
        expectedData = [128+commandId,
                            32+16,
                            (length-1) << 4]

        written = fixture.WrittenDataToSerial()
        self.assertListEqual(written, expectedData)

        
#if __name__ == '__main__':
#    unittest.main()
