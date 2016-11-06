import serial
from arduinoCom.serialProtocol import serialProtocol
from components.servo import servo
from components.distance import distance
from components.gyro import gyro
from components.sound import sound
from components.segway import segway
from components.motor import motor

import time

port = serial.Serial("/dev/ttyAMA0", baudrate=115200, timeout=3.0)
dataProtocol = serialProtocol(port)

#servo = servo(dataProtocol)
#servo.setVerticalPosition(90)
#servo.setHorizontalPosition(90)

gyro = gyro(dataProtocol);
#gyro.enableGyro()
#print str(gyro.measure());
#gyro.disableGyro()

#distance = distance(dataProtocol)
#distance.enable(1)
#print str(distance.measure())

segway = segway(dataProtocol)
gyro.setPidGyroSpeed(100, 0, 0)
gyro.setPidGyroAccelration(100, 0, 0)

motor = motor(dataProtocol)
motor.setPidMotorA(3000, 1000, 0)
motor.setPidMotorB(3000, 1000, 0)

segway.enable()
time.sleep(5)
segway.disable()

#sound.play("test.wav")

port.close()
