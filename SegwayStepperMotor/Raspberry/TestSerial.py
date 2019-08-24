import ArduinoCommunication 
import Arduino

arduinoCom = ArduinoCommunication.ArduinoCommunication()

arduino = Arduino.Arduino(arduinoCom)

arduino.SetPID(15,0.5,10)
