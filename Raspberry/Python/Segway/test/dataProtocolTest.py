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
