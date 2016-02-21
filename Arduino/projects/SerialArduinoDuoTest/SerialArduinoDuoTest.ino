#include <CommandTypes.h>
#include <SerialProtocol.h>



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  serialFlush();
  Serial3.begin(115200);
  Serial.println("Ready.");
}

short Angle;
short AngleAcc;

void loop() {
    HandleCommands();
    return;
    Serial.print("Angle:");
    Serial.println(Angle);
    Serial.print("Acc.:");
    Serial.println(AngleAcc);
}

void serialFlush(){
  while(Serial3.available() > 0) {
    char t = Serial3.read();
  }
}   
