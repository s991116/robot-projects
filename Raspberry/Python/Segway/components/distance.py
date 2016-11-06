from arduinoCom.commands import arduinoCommands
import time

class distance(object):

    def __init__(self, protocol):
        self.protocol = protocol
        self.enabled = False
        return

    def enable(self):
        self.protocol.sendCharData(arduinoCommands.DISTANCE_SENSOR_ENABLE_BYTE(), [1])
        time.sleep(1)

    def disable(self):
        self.protocol.sendCharData(arduinoCommands.DISTANCE_SENSOR_ENABLE_BYTE(), [0])
            
    def measure(self):
        return self.protocol.RequestShort(arduinoCommands.DISTANCE_MEASURE_SHORT(), 1)