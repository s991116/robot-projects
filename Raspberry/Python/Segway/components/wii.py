import cwiid
import time

class wii(object):

    def __init__(self):
        self.wm = None
        self.connected = False
        self.ledEnabled = 0
        self.nextSoundTime = time.time()
        return
        
    def tryConnect(self, attempts):
        connectionTry = 1
        while not self.wm:
            try:
                self.wm=cwiid.Wiimote()
            except:
                if(connectionTry>attempts):
                    self.connected = False
                    return False
                connectionTry += 1
        self.connected = True
        self.wm.rpt_mode = cwiid.RPT_BTN
        self.led(1,1)
        return self.connected

    def getAccelration(self):
        return self.wm.state['acc']
    
    def getCommand(self, servo, sound):
        buttons = self.wm.state['buttons']
        button_delay = 0.1
        # If Plus and Minus buttons pressed
        # then quit
        if (buttons - cwiid.BTN_PLUS - cwiid.BTN_MINUS == 0):  
            self.ledOff()
            self.connected = False
            return
            
        if (buttons & cwiid.BTN_UP):
            servo.moveLeft()
            time.sleep(button_delay)

        if (buttons & cwiid.BTN_DOWN):
            servo.moveRight()
            time.sleep(button_delay)

        if (buttons & cwiid.BTN_RIGHT):
            servo.moveUp()
            time.sleep(button_delay)

        if (buttons & cwiid.BTN_LEFT):
            servo.moveDown()
            time.sleep(button_delay)

        if (buttons & cwiid.BTN_1):
            if(self.nextSoundTime < time.time()):
                sound.hello()
                self.nextSoundTime = time.time()+15
                time.sleep(button_delay)

        if (buttons & cwiid.BTN_2):
            if(self.nextSoundTime < time.time()):
                servo.setHorizontalPosition(100)
                time.sleep(0.500)
                self.nextSoundTime = time.time()+15
                sound.ridin()
                time.sleep(0.625)
                for x in range(0, 8):
                    servo.setHorizontalPosition(150)
                    time.sleep(0.83916)
                    servo.setHorizontalPosition(50)
                    time.sleep(0.83916)                
                servo.setHorizontalPosition(100)
        return
        
    def ledOff(self):
        self.led(1,0)
        self.led(2,0)
        self.led(3,0)
        self.led(4,0)                
        return
        
    def led(self, number, state):
        self.ledEnabled = self.set_bit(self.ledEnabled, number-1, state)
        self.wm.led = self.ledEnabled
        return
        
    def set_bit(self, v, index, x):
      """Set the index:th bit of v to x, and return the new value."""
      mask = 1 << index
      v &= ~mask
      if x:
        v |= mask
      return v