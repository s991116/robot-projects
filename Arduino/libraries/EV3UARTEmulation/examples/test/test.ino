#include <SoftwareSerial.h>
#include <EV3UARTEmulation.h>
 
EV3UARTEmulation sensor(10, 11, 99, 38400); // rx pin, tx pin, type, bit rate
 
void setup() {
  // Single short value with 3 decimal digits
  sensor.create_mode("NOSE", true, DATA16, 1, 3, 0); 
  sensor.reset();
}
 
unsigned long last_reading = 0;
 
void loop() {
  sensor.heart_beat();
  if (millis() - last_reading > 100) {
    sensor.send_data16(0, analogRead(0)); // Read MQ-2 every 100 milliseconds
    last_reading = millis();
  }
}
