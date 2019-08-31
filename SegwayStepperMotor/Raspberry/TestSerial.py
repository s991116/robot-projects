import ArduinoCommunication 
import Arduino
import time

arduinoCom = ArduinoCommunication.ArduinoCommunication()

arduino = Arduino.Arduino(arduinoCom)

arduino.SetPID(10,1.5,10)

for x in range(0, 20):
    arduino.Direction(1,1)
    time.sleep(0.1)

arduino.Direction(0,0)
