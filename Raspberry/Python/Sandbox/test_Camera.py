#Picamera test
import unittest
from imutils.video.pivideostream import PiVideoStream
import imutils
import time
import numpy

class Test(unittest.TestCase):

    def setUp(self):
        pass
        
    def test_Grab_frame_from_PiCamera(self):
        #Arrange
        vs = PiVideoStream().start()
        time.sleep(2.0)
        
        #Act
        frame = vs.read()
        frame = imutils.resize(frame, width=400)
        vs.stop()
        
        #Assert
        self.assertTrue(isinstance(frame, numpy.ndarray))
        
#if __name__ == '__main__':
#    unittest.main()
