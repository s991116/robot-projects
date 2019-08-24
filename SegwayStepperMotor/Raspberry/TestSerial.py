import serial

port = serial.Serial(port='/dev/serial0')

while True:
    #Send Byte 0x10 Send TestData CMD
    port.write([0x10])
    #Send Byte with TestData
    port.write([0xFF])
    #Send Byte 0x20 Receive TestData CMD
    port.write([0x20])
    #Wait for byte from Arduino
    while(port.in_waiting<1):
        pass
    receive = port.read(1)
    
    print("\r\nArduino Sent back:" + repr(ord(receive)))