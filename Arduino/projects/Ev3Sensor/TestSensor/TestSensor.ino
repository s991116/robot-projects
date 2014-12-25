#include <SoftwareSerial.h>
//#include "EV3UARTEmulation.h"
#include "EV3UARTEmulationHard.h"
#include <Serial.h>

#define UART_TYPE (99)
#define UART_BITRATE (38400)
//(115200)
#define UART_RX (7)
#define UART_TX (6)

//EV3UARTEmulation sensor(UART_RX, UART_TX, UART_TYPE, UART_BITRATE);
EV3UARTEmulation sensor(&Serial, UART_TYPE, UART_BITRATE);

unsigned long last_reading = 0;
  
void setup() {
  Serial.begin(2400);
  sensor.create_mode("TEST", true, DATA16, 2, 3, 0);
  sensor.reset(); 
}

short data[2];
  
void loop() {
  sensor.heart_beat();
  if (millis() - last_reading > 100) {
    data[0] = 123;
    data[1] = 222;
    sensor.send_data16(data, 2);
    last_reading = millis();
  }
}
