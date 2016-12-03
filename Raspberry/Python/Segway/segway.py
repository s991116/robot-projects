import serial
from arduinoCom.serialProtocol import serialProtocol
from arduinoCom.commands import arduinoCommands
from components.servo import servo
from components.distance import distance
from components.wheelDistance import wheelDistance
from components.gyro import gyro
from components.sound import sound
from components.motor import motor
from components.wii import wii

class segway(object):

    def __init__(self):
        self.port = serial.Serial("/dev/ttyAMA0", baudrate=115200, timeout=3.0)
        self.dataProtocol = serialProtocol(self.port)
        self.servo = servo(self.dataProtocol)
        self.gyro = gyro(self.dataProtocol)
        self.distance = distance(self.dataProtocol)
        self.wheelDistance = wheelDistance(self.dataProtocol)
        self.motor = motor(self.dataProtocol)
        self.wii = wii()

    def enable(self):
        self.dataProtocol.sendCharData(arduinoCommands.SEGWAY_ENABLED_BYTE(), [1])

    def disable(self):
        self.dataProtocol.sendCharData(arduinoCommands.SEGWAY_ENABLED_BYTE(), [0])
    
    def isEnabled(self):
        return self.dataProtocol.RequestChar(arduinoCommands.SEGWAY_ENABLED_BYTE(),1)[0]

    def wiiControl(self):
        if(self.wii.tryConnect(5)):
            while(self.wii.connected):
                self.wii.getCommand(self.servo, sound)                
        return
        
    def pidGyro(self):
        return self.dataProtocol.RequestShort(arduinoCommands.PID_GYRO_SHORT(),3)

    def pidSpeed(self):
        return self.dataProtocol.RequestShort(arduinoCommands.PID_SPEED_SHORT(),3)
        
    def SetGyroPid(self, p, i, d):
        self.dataProtocol.sendShortData(arduinoCommands.PID_GYRO_SHORT(), [p,i,d])
    
    def SetSpeedPid(self, p, i, d):
        self.dataProtocol.sendShortData(arduinoCommands.PID_SPEED_SHORT(), [p,i,d])

    def pidMotorA(self):
        return self.dataProtocol.RequestShort(arduinoCommands.PID_ENCODER_A_SHORT(), 3)
        
    def setMotorAPid(self, p, i, d):
        self.dataProtocol.sendShortData(arduinoCommands.PID_ENCODER_A_SHORT(), [p,i,d])

    def pidMotorB(self):
        return self.dataProtocol.RequestShort(arduinoCommands.PID_ENCODER_B_SHORT(), 3)

    def setMotorBPid(self, p, i, d):
        self.dataProtocol.sendShortData(arduinoCommands.PID_ENCODER_B_SHORT(), [p,i,d])
                
    def __del__(self):
        self.port.close()
