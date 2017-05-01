#Arduino hardware test
import unittest
import serial
from arduinoCom.serialProtocol import serialProtocol
from arduinoCom.commands import arduinoCommands

class ArduinoTester(object):

    def __init__(self, protocol):
        self.protocol = protocol
        return
        
    def setTestShortValue(self, value):
        self.protocol.sendShortData(arduinoCommands.TEST_SHORT(),[value])
        
    def getTestShortValue(self):
        return self.protocol.RequestShort(arduinoCommands.TEST_SHORT(),1)[0]

    def setTestCharValue(self, value):
        self.protocol.sendCharData(arduinoCommands.TEST_SHORT(),[value])
        
    def getTestCharValue(self):
        return self.protocol.RequestChar(arduinoCommands.TEST_SHORT(),1)[0]

class ArduinoFixture():

    def CreateTarget(self):
        port = serial.Serial("/dev/ttyAMA0", baudrate=115200, timeout=3.0)
        dataProtocol = serialProtocol(port)
        return ArduinoTester(dataProtocol)

class ArduinoComTest(unittest.TestCase):

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

def TestSuite():
    return unittest.TestLoader().loadTestsFromTestCase(ArduinoComTest)
