#Connect to HC-06. Sends Hello and expect Hello to be sent back.
import bluetooth

target_name = "HC-06"
target_address = None

nearby_devices = bluetooth.discover_devices()

for bdaddr in nearby_devices:
    if target_name == bluetooth.lookup_name( bdaddr ):
        target_address = bdaddr
        break

if target_address is not None:
    print "found target bluetooth device with address ", target_address
else:
    print "could not find target bluetooth device nearby"
    
bd_addr = target_address
port = 1

sock=bluetooth.BluetoothSocket( bluetooth.RFCOMM )
sock.connect((bd_addr, port))

print "Sending 'Hello'"
sock.send("Hello")
for x in range (0, 5):
  data = sock.recv(1); #Receive 1 char at a time (5 char in 'Hello')
  print "Receving '" + data + "'"

sock.close()
