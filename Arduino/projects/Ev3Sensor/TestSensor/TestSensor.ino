#include <SoftwareSerial.h>
//#include <EV3UARTEmulation.h>
#include <EV3UARTEmulationHard.h>
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
  Serial.begin(9600);
  sensor.create_mode("TEST", true, DATA16, 1, 3, 0);
  sensor.reset(); 
}
  
void loop() {
  sensor.heart_beat();
  if (millis() - last_reading > 100) {
    sensor.send_data16(123);
    last_reading = millis();
  }
}
