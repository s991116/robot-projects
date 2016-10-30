import serial
from arduinoCom.serialProtocol import serialProtocol
from components.servo import servo
from components.distance import distance
from components.gyro import gyro
from components.sound import sound

port = serial.Serial("/dev/ttyAMA0", baudrate=115200, timeout=3.0)
dataProtocol = serialProtocol(port)

#servo = servo(dataProtocol)
#servo.setVerticalPosition(90)
#servo.setHorizontalPosition(90)

#gyro = gyro(dataProtocol);
#gyro.enableGyro()
#print str(gyro.measure());
#gyro.disableGyro()

#distance = distance(dataProtocol)
#distance.enable(1)
#print str(distance.measure())

sound.play("test.wav")

port.close()
