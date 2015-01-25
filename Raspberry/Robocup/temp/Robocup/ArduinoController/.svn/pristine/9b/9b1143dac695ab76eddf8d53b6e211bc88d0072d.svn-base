#include <gtest/gtest.h>
#include "ComController.h"
#include "ComMessage.h"
#include "MotorControllerCmd.h"

TEST(GenerateComMessage, GenerateMessage) {
    
    //Arrange
    char* comMessage = new char[3];
    char command = 244;
    short data = 985;
            
    //Act
    ComMessage::GenerateMessage(command, data, comMessage);
    
    //Assert
    EXPECT_EQ(command, comMessage[0]);
    EXPECT_EQ(data & 0x00FF, comMessage[1]);
    EXPECT_EQ(data >> 8, comMessage[2]);
}     