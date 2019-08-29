import ArduinoCommunication 
import Arduino

arduinoCom = ArduinoCommunication.ArduinoCommunication()

arduino = Arduino.Arduino(arduinoCom)

arduino.SetPID(15,1.5,10)
