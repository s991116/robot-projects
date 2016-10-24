#Arduino hardware test
import unittest
import serial
import SerialProtocol
from ArduinoCommands import ArduinoCommands

class ArduinoTester(object):

    def __init__(self, protocol):
        self.protocol = protocol
        return
        
    def setTestShortValue(self, value):
        self.protocol.sendShortData(ArduinoCommands.TEST_SHORT(),[value])
        
    def getTestShortValue(self):
        return self.protocol.RequestShort(ArduinoCommands.TEST_SHORT(),1)[0]

    def setTestCharValue(self, value):
        self.protocol.sendCharData(ArduinoCommands.TEST_SHORT(),[value])
        
    def getTestCharValue(self):
        return self.protocol.RequestChar(ArduinoCommands.TEST_SHORT(),1)[0]

class ArduinoFixture():

    def CreateTarget(self):
        port = serial.Serial("/dev/ttyAMA0", baudrate=115200, timeout=3.0)
        dataProtocol = SerialProtocol.SerialProtocol(port)
        return ArduinoTester(dataProtocol)

class Test(unittest.TestCase):

    def setUp(self):
        pass

    def test_Short_Data_To_Arduino(self):
        #Arrange
        fixture = ArduinoFixture()
        sut = fixture.CreateTarget()
        testValue = 1234
        
        #Act
        sut.setTestShortValue(testValue)
        
        #Assert
        result = sut.getTestShortValue()
        self.assertEqual(result, testValue)
        
    def test_Byte_Data_To_Arduino(self):
        #Arrange
        fixture = ArduinoFixture()
        sut = fixture.CreateTarget()
        testValue = 123
        
        #Act
        sut.setTestCharValue(testValue)
        
        #Assert
        result = sut.getTestCharValue()
        self.assertEqual(result, testValue)