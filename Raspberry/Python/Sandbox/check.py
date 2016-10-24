import serial
import SerialProtocol
import Gyro
import Servo
import Distance

port = serial.Serial("/dev/ttyAMA0", baudrate=115200, timeout=3.0)
dataProtocol = SerialProtocol.SerialProtocol(port)
gyro = Gyro.Gyro(dataProtocol)
servo = Servo.Servo(dataProtocol)
distance = Distance.Distance(dataProtocol)

#servo.setVerticalPosition(100)
#servo.setHorizontalPosition(90)

gyro.enableGyro()
#gyro.disableGyro()

print str(gyro.measure())


#distance.enable(1)
#print str(distance.measure())

port.close()
