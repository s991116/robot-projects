#include <gtest/gtest.h>
#include <HardwareController.h>
#include <ComPort.h>

TEST(SerialIntegration, SendCommand_EchoController_Command) {
    //Arrange
    ComPort* comPort = new ComPort();
    HardwareController* target = new HardwareController(comPort);
    
    //Act
    short result = target->SendCommand(CommandType::Get_Controller_Echo_Command_Test, 0);
    
    //Assert
    short expectedValue = (short)(CommandType::Get_Controller_Echo_Command_Test);
    EXPECT_EQ(expectedValue, result);
    delete target;
}

TEST(SerialIntegration, SendCommand_EchoController_Data) {
    //Arrange
    ComPort* comPort = new ComPort();
    HardwareController* target = new HardwareController(comPort);
    short dataTest = 212;
    
    //Act
    short result = target->SendCommand(CommandType::Get_Controller_Echo_Data_Test, dataTest);
    
    //Assert
    EXPECT_EQ(dataTest, result);
    delete target;
}

TEST(SerialIntegration, SendCommand_EchoMotorController_Command) {
    //Arrange
    ComPort* comPort = new ComPort();
    HardwareController* target = new HardwareController(comPort);
    
    //Act
    short result = target->SendCommand(CommandType::Get_Motor_Echo_Command_Test, 0);
    
    //Assert
    short expectedValue = (short)(CommandType::Get_Motor_Echo_Command_Test);
    EXPECT_EQ(expectedValue, result);
    delete target;
}        

TEST(SerialIntegration, SendCommand_EchoMotorController_Data) {
    //Arrange
    ComPort* comPort = new ComPort();
    HardwareController* target = new HardwareController(comPort);
    short dataTest = 212;
    
    //Act
    short result = target->SendCommand(CommandType::Get_Motor_Echo_Data_Test, dataTest);
    
    //Assert
    EXPECT_EQ(dataTest, result);
    delete target;
}        
