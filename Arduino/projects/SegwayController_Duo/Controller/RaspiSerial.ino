void InitializeRaspiSerial()
{
  Serial2.begin(115200); 
}

void SendCommandToSerial(int data)
{
  Serial2.println(data);
}

