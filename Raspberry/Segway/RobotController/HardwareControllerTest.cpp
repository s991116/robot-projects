#include "gtest/gtest.h"
#include <HardwareController.h>
#include <ComPort.h>
#include <Convert.h>
#include <exception>

class HardwareControllerFixture {
    
public:    
    HardwareController* CreateTarget()
    {
      ComPort* comPort = new ComPort();
      target = new HardwareController(comPort);
      return target;
    }
    
    ~HardwareControllerFixture()
    {
      delete target;
    }
    
private:
    HardwareController* target;

};

TEST(SerialIntegration, SendCommand_EchoController_Command) {
    //Arrange
    HardwareControllerFixture fixture = HardwareControllerFixture();
    HardwareController* target = fixture.CreateTarget();
    
    //Act
    short result = target->SendCommand(RobotCommandType::Get_Controller_Echo_Command_Test, 0);
    
    //Assert
    short expectedValue = (short)(RobotCommandType::Get_Controller_Echo_Command_Test) + RobotCommandTypeOffset;
    EXPECT_EQ(expectedValue, result);
}

TEST(SerialIntegration, SendCommand_EchoController_Data) {
    //Arrange
    HardwareControllerFixture fixture = HardwareControllerFixture();
    HardwareController* target = fixture.CreateTarget();
    short dataTest = 13;//256*42+212;
    
    //Act
    short result = target->SendCommand(RobotCommandType::Get_Controller_Echo_Data_Test, dataTest);

    //Assert
    EXPECT_EQ(dataTest, result);
}

TEST(SerialIntegration, SendCommand_EchoMotorController_Command) {
    //Arrange
    HardwareControllerFixture fixture = HardwareControllerFixture();
    HardwareController* target = fixture.CreateTarget();
    
    //Act
    short result = target->SendCommand(MotorCommandType::Get_Motor_Echo_Command_Test, 0);
    
    //Assert
    short expectedValue = (short)(MotorCommandType::Get_Motor_Echo_Command_Test);
    EXPECT_EQ(expectedValue, result);
}

TEST(SerialIntegration, SendCommand_EchoMotorController_Data) {
    //Arrange    
    HardwareControllerFixture fixture = HardwareControllerFixture();
    HardwareController* target = fixture.CreateTarget();
    short dataTest = 13;//21*256+25;
    
    //Act
    short result = target->SendCommand(MotorCommandType::Get_Motor_Echo_Data_Test, dataTest);
    
    //Assert
    EXPECT_EQ(dataTest, result);
}

TEST(SerialIntegration, ResetDataLogger_NrOfLoggingIsZero) {
    //Arrange    
    HardwareControllerFixture fixture = HardwareControllerFixture();
    HardwareController* target = fixture.CreateTarget();
    short logDataExpected = 12345;
    target->SendCommand(MotorCommandType::Reset_Logger, 0);
    target->SendCommand(MotorCommandType::Add_Logging_Data, logDataExpected);

    //Act
    target->SendCommand(MotorCommandType::Reset_Logger, 0);
    
    //Assert
    short nrOfMeasures = target->SendCommand(MotorCommandType::Get_Nr_Of_Logs, 0);
    
    EXPECT_EQ(0, nrOfMeasures);
}

TEST(SerialIntegration, AddTwoDataToLogger_GetLoggingData) {

    //Arrange    
    HardwareControllerFixture fixture = HardwareControllerFixture();
    HardwareController* target = fixture.CreateTarget();
    short logDataExpected1 = 123;
    short logDataExpected2 = 12321;
    target->SendCommand(MotorCommandType::Reset_Logger, 0);
    
    //Act
    target->SendCommand(MotorCommandType::Add_Logging_Data, logDataExpected1);
    target->SendCommand(MotorCommandType::Add_Logging_Data, logDataExpected2);
    
    //Assert
    short nrOfMeasures = target->SendCommand(MotorCommandType::Get_Nr_Of_Logs, 0);
    short logData1 = target->SendCommand(MotorCommandType::Get_Logging_Error, 0);
    target->SendCommand(MotorCommandType::Next_Logging, 0);
    short logData2 = target->SendCommand(MotorCommandType::Get_Logging_Error, 0);
    
    EXPECT_EQ(2, nrOfMeasures);
    EXPECT_EQ(logDataExpected1, logData1);
    EXPECT_EQ(logDataExpected2, logData2);
  
}

TEST(SerialIntegration, SendCommand_FastResend) {
    //Arrange    
    HardwareControllerFixture fixture = HardwareControllerFixture();
    HardwareController* target = fixture.CreateTarget();

    short dataTest = 256*42+212;
    short result;
    //Act
    for(int index=0; index < 10; index++)
      result = target->SendCommand(RobotCommandType::Get_Controller_Echo_Data_Test, dataTest);

    //Assert
    EXPECT_EQ(dataTest, result);
}

TEST(SerialIntegration, AddDataToLogger_GetErrorAndTargetLoggingData) {

    //Arrange    
    HardwareControllerFixture fixture = HardwareControllerFixture();
    HardwareController* target = fixture.CreateTarget();
    
    target->SendCommand(MotorCommandType::Reset_Logger, 0);

    short expectedLog = 42;
    target->SendCommand(MotorCommandType::Add_Logging_Data, expectedLog);
    
    //Act
    short resultError = target->SendCommand(MotorCommandType::Get_Logging_Error, 0);
    short resultTarget = target->SendCommand(MotorCommandType::Get_Logging_Target, 0);

    //Assert
    EXPECT_EQ(expectedLog, resultError);
    EXPECT_EQ(expectedLog, resultTarget);
}

TEST(SerialIntegration, AddMaxDataToLogger_GetAllLoggingData) {

    //Arrange    
    HardwareControllerFixture fixture = HardwareControllerFixture();
    HardwareController* target = fixture.CreateTarget();
    
    target->SendCommand(MotorCommandType::Reset_Logger, 0);
    bool LogNotFull = target->SendCommand(MotorCommandType::Logging_Full, 0);

    int arraySize = 250;
    short * expectedLog = new short[arraySize];
    for(int index = 0; index < arraySize; index++)
    {
        expectedLog[index] = index;
        target->SendCommand(MotorCommandType::Add_Logging_Data, expectedLog[index]);
    }
    
    //Act
    short nrOfMeasures = target->SendCommand(MotorCommandType::Get_Nr_Of_Logs, 0);
    bool LogFull = target->SendCommand(MotorCommandType::Logging_Full, 0);
    short * resultLog = new short[arraySize];
    for(int index = 0; index < arraySize; index++)
    {
        resultLog[index] = target->SendCommand(MotorCommandType::Get_Logging_Error, 0);
        target->SendCommand(MotorCommandType::Next_Logging, 0);
    } 

    //Assert
    EXPECT_EQ(true, LogFull);
    EXPECT_EQ(false, LogNotFull);
    EXPECT_EQ(arraySize, nrOfMeasures);
    for(int index = 0; index < arraySize; index++)
    {
        EXPECT_EQ(expectedLog[index], resultLog[index]);
    }
}

TEST(SerialIntegration, SendCommand_RepeatCommand) {

    //Arrange    
    HardwareControllerFixture fixture = HardwareControllerFixture();
    HardwareController* target = fixture.CreateTarget();

    //Act
    try{
      target->SendCommand(MotorCommandType::Set_MotorLeft_Speed, 0);
      target->SendCommand(MotorCommandType::Set_MotorLeft_Speed, 0);
      target->SendCommand(MotorCommandType::Set_Motor_Enabled, false);
      target->SendCommand(MotorCommandType::Set_Motor_Enabled, true); 
    }
    
    //Assert
    catch(std::exception& e)
    {
      EXPECT_EQ(true, false);
    }
}