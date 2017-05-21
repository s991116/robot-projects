# import the necessary packages
from logging import FileHandler
from vlogging import VisualRecord
import logging
import cv2
 
# open the logging file
logger = logging.getLogger("visual_logging_example")
fh = FileHandler("demo.html", mode = "w")
 
# set the logger attributes
logger.setLevel(logging.DEBUG)
logger.addHandler(fh)
 
# load our example image and convert it to grayscale
image = cv2.imread("superman.jpg")
image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
 
# loop over some varying sigma sizes
for s in xrange(3, 11, 2):
	# blur the image and detect edges
	blurred = cv2.GaussianBlur(image, (s, s), 0)
	edged = cv2.Canny(blurred, 75, 200)
	logger.debug(VisualRecord(("Detected edges using sigma = %d" % (s)),
		[blurred, edged], fmt = "png"))