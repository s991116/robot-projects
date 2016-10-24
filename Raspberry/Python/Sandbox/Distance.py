from ArduinoCommands import ArduinoCommands
import time

class Distance(object):

    def __init__(self, protocol):
        self.protocol = protocol
        self.enabled = False
        return
        
    def enable(self, enabled):
        if enabled == True:
            self.protocol.sendCharData(ArduinoCommands.DISTANCE_SENSOR_ENABLE_BYTE(), [1])
            time.sleep(1)
        else:
            self.protocol.sendCharData(ArduinoCommands.DISTANCE_SENSOR_ENABLE_BYTE(), [0])
            
    def measure(self):
        return self.protocol.RequestShort(ArduinoCommands.DISTANCE_MEASURE_SHORT(), 1)