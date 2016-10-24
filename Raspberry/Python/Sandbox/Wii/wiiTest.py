import cwiid
import time

wm = None
connectionTry = 1
while not wm:
    try:
        print "Connection attempt " + str(connectionTry)
        wm=cwiid.Wiimote()
    except:
        if(connectionTry>5):
            print "cannot create connection"
            quit()
        print "Error connecting to WiiMote"
        connectionTry += 1

wm.led = 1
wm.rpt_mode = cwiid.RPT_BTN | cwiid.RPT_ACC

while True:
    print "Acc 0:" + str(wm.state['acc'][0])
    print "Acc 1:" + str(wm.state['acc'][1])
    print "Acc 2:" + str(wm.state['acc'][2])
    time.sleep(.5)
