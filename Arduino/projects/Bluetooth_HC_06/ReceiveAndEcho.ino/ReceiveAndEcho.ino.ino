//Receive char and returns it back over bluetooth (Written for Arduino DUE).
//Bluetooth (HC_06) is 3.3V and Baud is 9600
//Receive char on Serial1 and echo it back to Serial and Serial1

#define LED_PIN (13)
#define HC_06_BAUD (9600)
void setup()
{
  Serial.begin(HC_06_BAUD);
  Serial1.begin(HC_06_BAUD); // Default Baud rate of HC-05

  pinMode(LED_PIN, OUTPUT); //Pin Led
  Serial.println("Test Bluetooth receiver.....");
}

bool ledMode;

void swithLED() {
  ledMode = !ledMode;
  if(ledMode)
    digitalWrite(LED_PIN, HIGH);
  else
    digitalWrite(LED_PIN, LOW); 
}

void loop()
{
  short c;
  if (Serial1.available()) 
  {
     c = Serial1.read();
     Serial1.write(c);
     Serial.write(c);
     swithLED();
  }
}
