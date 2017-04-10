from PiVideoStream import PiVideoStream
import cv2
import time
pvs = PiVideoStream(resolution=(320, 240))

pvs.start()
time.sleep(2.0)
print "Press key to quit."
key = -1
while(key == -1):

  frame = pvs.read()
  cv2.imshow("Frame",frame)
  key = cv2.waitKey(25)

pvs.stop()


  
