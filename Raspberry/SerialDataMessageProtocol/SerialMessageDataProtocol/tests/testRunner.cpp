 #include <gtest/gtest.h>
#include <MessageDataProtocol.h>
#include <SerialConnectorMock.h>
#include <SerialBufferMock.h>
#include <SerialComMock.h>
#include <HandlerMock.h>
#include <DataPackets.h>
#include <DataHandler.h>

using namespace std;
 
int main (int argc, char** argv)
{
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS();
}
 
TEST(Protocol,SendData_SendDataMethodCalled){
    //Arrange
    char expectedCommandId = 1;
    SerialConnectorMock* serialConnector = new SerialConnectorMock();
    DataHandler* dataHandlerSender = new DataHandler();

    MessageDataProtocol* sender = new MessageDataProtocol(new DataPackets(serialConnector->GetSerialCom1()), dataHandlerSender);
    HandlerMock* dataHandlerReceiver = new HandlerMock();
    SerialCom* receiver = serialConnector->GetSerialCom2();
    MessageDataProtocol* sut = new MessageDataProtocol(new DataPackets(receiver), dataHandlerReceiver);
    
    short expectedData[] = {242,345};
    char length = 2;
    sender->SendData(expectedCommandId, length, expectedData);
    
    //Act
    sut->Update();

    //Assert
    EXPECT_EQ(0,receiver->DataAvailable());
    EXPECT_EQ(dataHandlerReceiver->LastCommandReceived, expectedCommandId);
    EXPECT_EQ(dataHandlerReceiver->LastLengthReceived, length);    
    for(int i=0; i<length; i++)
    {
        EXPECT_EQ(dataHandlerReceiver->LastShortDataReceived[i], expectedData[i]);
    }
}

TEST(Protocol,Remove_Non_Starting_Char_In_Serial){
    //Arrange
    char expectedCommandId = 123;    
    SerialConnectorMock* serialConnector = new SerialConnectorMock();
    DataHandler* dataHandlerSender = new DataHandler();
    SerialCom* transmitter = serialConnector->GetSerialCom1();
    transmitter->WriteChar(12);
    transmitter->WriteChar(23);
    MessageDataProtocol* sender = new MessageDataProtocol(new DataPackets(transmitter), dataHandlerSender);
    HandlerMock* dataHandlerReceiver = new HandlerMock();
    SerialCom* receiver = serialConnector->GetSerialCom2();
    MessageDataProtocol* sut = new MessageDataProtocol(new DataPackets(receiver), dataHandlerReceiver);
    
    short expectedData[] = {242,345};
    char length = 2;
    sender->SendData(expectedCommandId, length, expectedData);

    //Act
    sut->Update();
    
    //Assert
    EXPECT_EQ(0,receiver->DataAvailable());
    EXPECT_EQ(dataHandlerReceiver->LastCommandReceived, expectedCommandId);
    EXPECT_EQ(dataHandlerReceiver->LastLengthReceived, length);    
    for(int i=0; i<length; i++)
    {
        EXPECT_EQ(dataHandlerReceiver->LastShortDataReceived[i], expectedData[i]);
    }
}

TEST(Protocol,RequestData_RequestData_Returned){
    //Arrange
    char expectedCommandId = 1;
    SerialConnectorMock* serialConnector = new SerialConnectorMock();
    HandlerMock* dataHandlerSender = new HandlerMock();
    DataPackets* dataPacketSender = new DataPackets(serialConnector->GetSerialCom1());
    MessageDataProtocol* sender = new MessageDataProtocol(dataPacketSender, dataHandlerSender);
    HandlerMock* dataHandlerReceiver = new HandlerMock();
    SerialCom* receiverCom = serialConnector->GetSerialCom2();
    MessageDataProtocol* receiver = new MessageDataProtocol(new DataPackets(receiverCom), dataHandlerReceiver);
    
    char requestedData[2];
    char length = 1;
    
    receiverCom->WriteChar(expectedCommandId + 0x80); //1CCCCCCC
    receiverCom->WriteChar(0x42); //0DDTLLLL  -  0100
    receiverCom->WriteChar(0x07); //0SSSHHHH    
        
    //Act
    sender->RequestData(expectedCommandId, length, requestedData);

    //Assert
    EXPECT_EQ(length, dataPacketSender->GetLength());
    EXPECT_EQ(expectedCommandId, dataPacketSender->GetCommandId());
    EXPECT_EQ(PacketType::Char, dataPacketSender->GetType());
    EXPECT_EQ(0x72, dataPacketSender->GetCharDataBuffer()[0]);
    EXPECT_EQ(PacketDirection::ReplyData, dataPacketSender->GetDirection());
    EXPECT_EQ(0x72, requestedData[0]);
}

TEST(CreateDataPacket, SetRequest_With_Char){
    //Arrange
    SerialBufferMock* serialBufferMock = new SerialBufferMock();
    DataPackets* dataPacket = new DataPackets(serialBufferMock);
    char commandId = 125;
    char length = 1;    
    char data[] = {0x7D};
    dataPacket->SetRequest(commandId, length, data);
    
    //Act
    dataPacket->SendData();
    char* serialData = serialBufferMock->serialData;
    
    //Assert
    char direction = serialData[1] >> 5 & 0x03;
    char type = serialData[1] >> 4 & 0x01;
    
    EXPECT_TRUE(serialData[0] >> 7 == 1);
    EXPECT_EQ(commandId+128, serialData[0]);

    EXPECT_TRUE(serialData[1] >> 7 == 0);    
    EXPECT_EQ(direction, (char)(PacketDirection::SendData));
    EXPECT_EQ(type, (char)(PacketType::Char));
    
    EXPECT_EQ(serialData[1] & 0x0F, 0x0D);
    
    EXPECT_TRUE(serialData[2] >> 7 == 0);    
    EXPECT_EQ(length-1, serialData[2] >> 4 & 0x7);
    EXPECT_EQ(serialData[2] & 0x0F, 0x07);
    EXPECT_EQ(serialBufferMock->DataAvailable(), 3);
}

TEST(CreateDataPacket, SetRequest_With_Char_Array){
    //Arrange
    SerialBufferMock* serialBufferMock = new SerialBufferMock();
    DataPackets* dataPacket = new DataPackets(serialBufferMock);
    char commandId = 125;
    char length = 3;    
    char data[] = {0xD7, 0x42, 0x94};
    dataPacket->SetRequest(commandId, length, data);
    
    //Act
    dataPacket->SendData();
    
    //Assert
    char* serialData = serialBufferMock->serialData;

    char direction = serialData[1] >> 5 & 0x03;
    char type = serialData[1] >> 4 & 0x01;
    
    EXPECT_TRUE(serialData[0] >> 7 == 1);
    EXPECT_EQ(commandId+128, serialData[0]);

    EXPECT_EQ(direction, (char)(PacketDirection::SendData));
    EXPECT_EQ(type, (char)(PacketType::Char));

    EXPECT_EQ(length-1, serialData[2] >> 4 & 0x7);    

    
    EXPECT_TRUE(serialData[1] >> 7 == 0);
    EXPECT_EQ(serialData[1] & 0x0F, 0x07);
    
    EXPECT_TRUE(serialData[2] >> 7 == 0);    
    EXPECT_EQ(serialData[2] & 0x0F, 0x0D);
    
    EXPECT_TRUE(serialData[3] >> 7 == 0);
    EXPECT_EQ(serialData[3] & 0x0F, 0x02);
    
    EXPECT_TRUE(serialData[4] >> 7 == 0);    
    EXPECT_EQ(serialData[4] & 0x0F, 0x04);

    EXPECT_TRUE(serialData[5] >> 7 == 0);
    EXPECT_EQ(serialData[5] & 0x0F, 0x04);
    
    EXPECT_TRUE(serialData[6] >> 7 == 0);    
    EXPECT_EQ(serialData[6] & 0x0F, 0x09);

    EXPECT_EQ(serialBufferMock->DataAvailable(), 7);
}

TEST(CreateDataPacket, SetRequest_With_Short_Array){
    //Arrange
    SerialBufferMock* serialBufferMock = new SerialBufferMock();
    DataPackets* dataPacket = new DataPackets(serialBufferMock);
    char commandId = 125;
    char length = 3;    
    short data[] = {0x1D5A, 0x3FA2, 0x489C};
    dataPacket->SetRequest(commandId, length, data);    
    
    //Act
    dataPacket->SendData();
    
    //Assert
    char* serialData = serialBufferMock->serialData;
    char direction = serialData[1] >> 5 & 0x03;
    char type = serialData[1] >> 4 & 0x01;
    
    EXPECT_TRUE(serialData[0] >> 7 == 1);
    EXPECT_EQ(commandId+128, serialData[0]);

    EXPECT_TRUE(serialData[1] >> 7 == 0);    
    EXPECT_EQ(direction, (char)(PacketDirection::SendData));
    EXPECT_EQ(type, (char)(PacketType::Short));    
    EXPECT_EQ(serialData[1] & 0x0F, 0x0A);
    
    EXPECT_TRUE(serialData[2] >> 7 == 0);    
    EXPECT_EQ(length-1, serialData[2] >> 4 & 0x7);
    EXPECT_EQ(serialData[2] & 0x0F, 0x05);
    
    EXPECT_TRUE(serialData[3] >> 7 == 0);    
    EXPECT_EQ(serialData[3] & 0x0F, 0x0D);
    
    EXPECT_TRUE(serialData[4] >> 7 == 0);    
    EXPECT_EQ(serialData[4] & 0x0F, 0x01);

    EXPECT_TRUE(serialData[5] >> 7 == 0);    
    EXPECT_EQ(serialData[5] & 0x0F, 0x02);
    
    EXPECT_TRUE(serialData[6] >> 7 == 0);    
    EXPECT_EQ(serialData[6] & 0x0F, 0x0A);

    EXPECT_TRUE(serialData[7] >> 7 == 0);    
    EXPECT_EQ(serialData[7] & 0x0F, 0x0F);
    
    EXPECT_TRUE(serialData[8] >> 7 == 0);    
    EXPECT_EQ(serialData[8] & 0x0F, 0x03);
    
    EXPECT_TRUE(serialData[9] >> 7 == 0);    
    EXPECT_EQ(serialData[9] & 0x0F, 0x0C);
    
    EXPECT_TRUE(serialData[10] >> 7 == 0);    
    EXPECT_EQ(serialData[10] & 0x0F, 0x09);

    EXPECT_TRUE(serialData[11] >> 7 == 0);    
    EXPECT_EQ(serialData[11] & 0x0F, 0x08);
    
    EXPECT_TRUE(serialData[12] >> 7 == 0);    
    EXPECT_EQ(serialData[12] & 0x0F, 0x04);
    
    EXPECT_EQ(serialBufferMock->DataAvailable(), 13);    
}

/*
TEST(CreateDataPacket, GetRequest_With_Short_Array){
    //Arrange
    DataPackets* dataPacket = new DataPackets();
    char commandId = 125;
    char length = 2;    
    short data[] = {0x1D5A, 0x3FA2, 0x0000};
    dataPacket->SetRequest(commandId, length, data);

    SerialBufferMock* serialBufferMock = new SerialBufferMock();
    dataPacket->SendData(serialBufferMock);

    DataPackets* dataPacketReceive = new DataPackets();
    
    //Act
    dataPacketReceive->GetSerialData(serialData);
    
    //Assert
    EXPECT_EQ(dataPacketReceive->GetCommandId(), commandId);
    EXPECT_EQ(dataPacketReceive->GetLength(), length);
    EXPECT_EQ(dataPacketReceive->GetType(), PacketType::Short);
    EXPECT_EQ(dataPacketReceive->GetDirection(), PacketDirection::Request);
    short resultData[10];
    dataPacketReceive->FillData(resultData);
    for(int i=0; i<3; i++) {
      EXPECT_EQ(resultData[i], data[i]);      
    }
}

TEST(CreateDataPacket, GetRequest_With_Char_Array){
    //Arrange
    DataPackets* dataPacket = new DataPackets();
    char commandId = 125;
    char length = 2;    
    char data[] = {0xD7, 0x42, 0x94};
    dataPacket->SetRequest(commandId, length, data);

    char serialData[50];
    dataPacket->FillSerialData(serialData);
    
    DataPackets* dataPacketReceive = new DataPackets();
    
    //Act
    dataPacketReceive->GetSerialData(serialData);
    
    //Assert
    EXPECT_EQ(dataPacketReceive->GetCommandId(), commandId);
    EXPECT_EQ(dataPacketReceive->GetLength(), length);
    EXPECT_EQ(dataPacketReceive->GetType(), PacketType::Char);
    EXPECT_EQ(dataPacketReceive->GetDirection(), PacketDirection::Request);
    char resultData[10];
    dataPacketReceive->FillData(resultData);
    for(int i=0; i<3; i++) {
      EXPECT_EQ(resultData[i], data[i]);      
    }    
}
 */ 