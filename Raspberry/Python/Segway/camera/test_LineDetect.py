import unittest
import cv2
from LineDetect import LineDetect
import SplitLineDirection
from LineDetectInfo import LineDetectInfo
import timeit
import os
from logging import FileHandler
import logging

def setUpModule():
    #-- Enable to show images with debug information on --
    #EnableVisualDebug('LineDetectTest.html')
        
class Test(unittest.TestCase):
    def setUp(self):
        logger = logging.getLogger('Segway')
        logger.debug("Testname: '" + self._testMethodName + "' ")
        
    def test_LineAtCenter_PositionReturnIsCenter(self):
        
        #Arrange
        sut = LineDetectFixture().CreateTarget()
        img = self.__TestImageLoader__('VerticalLineCenter.jpg')

        #Act
        lineInfo = sut.GetLinePosition(img, SplitLineDirection.SplitCenter())

        #Assert
        self.assertEqual(0, lineInfo.Position)

    def test_LineAtCenter_DetectionTimeIsSmall(self):

        #Arrange
        sut = LineDetectFixture().CreateTarget()
        img = self.__TestImageLoader__('VerticalLineCenter.jpg')

        def wrapper(func, *args, **kwargs):
            def wrapped():
                return func(*args, **kwargs)
            return wrapped
        direction = SplitLineDirection.SplitCenter()
        wrapped = wrapper(sut.GetLinePosition, img, direction, False)
        
        #Act        
        executionTime = timeit.timeit(wrapped, number=1000)

        #Assert
        self.assertLess(executionTime, 0.5)
    
    
    def test_LineAtLeft_PositionReturnIsNegative(self):

        #Arrange
        sut = LineDetectFixture().CreateTarget()
        img = self.__TestImageLoader__('VerticalLineLeft.jpg')

        #Act
        lineInfo = sut.GetLinePosition(img, SplitLineDirection.SplitCenter())

        #Assert
        self.assertTrue(lineInfo.Position < 0)

    def test_LineAtRight_PositionReturnIsPositive(self):

        #Arrange
        sut = LineDetectFixture().CreateTarget()
        img = self.__TestImageLoader__('VerticalLineRight.jpg')

        #Act
        lineInfo = sut.GetLinePosition(img, SplitLineDirection.SplitCenter())

        #Assert
        self.assertTrue(lineInfo.Position > 0)

    def test_DetectLeft_LineAtLeftAndRight_LeftPositionFound(self):

        #Arrange
        sut = LineDetectFixture().CreateTarget()
        img = self.__TestImageLoader__('VerticalLinesLeftRight.jpg')

        #Act
        lineInfo = sut.GetLinePosition(img, SplitLineDirection.SplitLeft())

        #Assert
        self.assertTrue(lineInfo.Position < 0)

    def test_DetectRight_LineAtLeftAndRight_RightPositionFound(self):

        #Arrange
        sut = LineDetectFixture().CreateTarget()
        img = self.__TestImageLoader__('VerticalLinesLeftRight.jpg')

        #Act
        lineInfo = sut.GetLinePosition(img, SplitLineDirection.SplitRight())

        #Assert
        self.assertTrue(lineInfo.Position > 0)

    def test_Detect_NoLine_LineFoundIsFalse(self):

        #Arrange
        sut = LineDetectFixture().CreateTarget()
        img = self.__TestImageLoader__('NoLines.jpg')

        #Act
        lineInfo = sut.GetLinePosition(img, SplitLineDirection.SplitRight())

        #Assert
        self.assertFalse(lineInfo.Found)

        
    def __TestImageLoader__(self, filename):
        CurrentDir = os.path.dirname(os.path.abspath(__file__))
        fullFilename = os.path.join(CurrentDir, 'TestData', filename)
        
        img = cv2.imread(fullFilename)
        img = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)
        return img
                    
def TestSuite():
    return unittest.TestLoader().loadTestsFromTestCase(Test)

def EnableVisualDebug(filename):
    logger = logging.getLogger('Segway')
    logger.setLevel(logging.DEBUG)
    handler = FileHandler(filename, mode = "w")
    handler.setLevel(logging.DEBUG)
    logger.addHandler(handler)
    
class LineDetectFixture():
    def CreateTarget(self):
        ld = LineDetect()
        ld.SetFilter(31, 5, True)
        return ld
