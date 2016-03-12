void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

int data = 111;

void loop() {
  while(!Serial.available());
  int j = Serial.read();
  Serial.write(j);
}
