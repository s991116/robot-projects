import unittest
import cv2
from LineDetect import LineDetect
import SplitLineDirection
from LineDetectInfo import LineDetectInfo
import timeit

class Test(unittest.TestCase):
        
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
        wrapped = wrapper(sut.GetLinePosition, img, direction)
        
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
        img = cv2.imread(filename)
        img = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)
        return img
        
def TestSuite():
    return unittest.TestLoader().loadTestsFromTestCase(Test)

        
class LineDetectFixture():
    def CreateTarget(self):
        ld = LineDetect()
        ld.SetFilter(31, 5, True)
        return ld
