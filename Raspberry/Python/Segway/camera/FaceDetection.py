import cv2
import sys
from PiVideoStream import PiVideoStream

import time
pvs = PiVideoStream(resolution=(320, 240))
cascPath = sys.argv[1]

pvs.start()
time.sleep(2.0)

# Get user supplied values

# Create the haar cascade
faceCascade = cv2.CascadeClassifier(cascPath)

# Read the image

print "Press key to quit."
key = -1
while(key == -1):

  image = pvs.read()
  gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
  faces = faceCascade.detectMultiScale(
      gray,
      scaleFactor=1.1,
      minNeighbors=5,
      minSize=(30, 30),
      flags = cv2.cv.CV_HAAR_SCALE_IMAGE
  )
  for (x, y, w, h) in faces:
      cv2.rectangle(image, (x, y), (x+w, y+h), (0, 255, 0), 2)

  cv2.imshow("Frame",image)  
  key = cv2.waitKey(1)

pvs.stop()