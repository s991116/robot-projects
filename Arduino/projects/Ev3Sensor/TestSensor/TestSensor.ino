#define DEBUG
#include <SoftwareSerial.h>
#include <EV3UARTEmulation.h>
#include <Serial.h>

#define UART_RX (10)
#define UART_TX (11)
#define UART_TYPE (99)
#define UART_BITRATE (38400)

 
EV3UARTEmulation sensor(UART_RX, UART_TX, UART_TYPE, UART_BITRATE);

// Reference the I2C Library
#include <Wire.h>

int error = 0;
short heading[4];
unsigned long last_reading = 0;
  
void setup() {
  Serial.begin(9600);
  Serial.println("Create RAW mode");
  sensor.create_mode("RAW", true, DATA16, 3, 5, 0);
  Serial.println("Create Degree mode");
  sensor.create_mode("DEGREES", true, DATA16, 1, 3, 0);
  Serial.println("Reset sensor");
  sensor.reset();
 
  Serial.println("Starting the I2C interface.");
  Wire.begin(); // Start the I2C interface.
 
  Serial.println("Setting MPU6050 sensor.");
  error = 0; //TODO Setup 6050 sensor
  if(error != 0) // If there is an error, print it out.
    Serial.println("Error code: " + error);
}
  
void loop() {
  sensor.heart_beat();
  if (millis() - last_reading > 100) {
    switch (sensor.get_current_mode()) {
      case 0: // Retrieve the raw values from the compass (not scaled).
        heading[0] = 1;
        heading[1] = 2;
        heading[2] = 3;
        heading[3] = 4;
        Serial.print("Raw X: ");
        Serial.print(heading[0]);
        Serial.print(" Y: ");
        Serial.print(heading[1]);
        Serial.print(" Z: ");
        Serial.println(heading[2]);
        sensor.send_data16(heading, 4);
        break;
      
      case 1: // Retrieve the scaled values from the compass (scaled to the configured scale).
        // Calculate heading when the magnetometer is level, then correct for signs of axis.
        short degrees = 90;
 
        if (degrees < 0) 
          degrees += 360;
        Serial.print("Heading: ");
        Serial.println(degrees);
        sensor.send_data16(degrees);
        break;
    }
    last_reading = millis();
  }
}
