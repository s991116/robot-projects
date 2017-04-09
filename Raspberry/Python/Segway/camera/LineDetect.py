from picamera.array import PiRGBArray
import SplitLineDirection
import numpy
from LineDetectInfo import LineDetectInfo

class LineDetect():
    
    def __init__(self):        
        self.detectMaxValue = 20
        self.detectMinValue = -20

        self.SetDetectHeight(101, 105)
        self.imageWidth = 320
        self.SetFilter(31, 5, True)
        self.SetImageWidth(self.imageWidth)
        self.SetFilterThresshold(100)
    
    def SetImageWidth(self, imageWidth):
        self.imageWidth = imageWidth
        self.__UpdateFilter__()
    
    def SetDetectHeight(self, start, end):
        self.sensorHeightStart = start
        self.sensorHeightEnd = end
    
    def SetFilter(self, lineLength, nonLineLength, blackLine):
    
        self.filterLineLength = lineLength
        self.filterNonLineLength = nonLineLength
        self.blackLine = blackLine        
        self.__UpdateFilter__()
    
    def SetFilterThresshold(self, thresshold):
        self.FilterThresshold = thresshold
    
    def __UpdateFilter__(self):
        if(self.blackLine):
            lineFilterColor = -1
            nonLineFilterColor = 1
        else:
            lineFilterColor = 1
            lineFilterColor = -1

        self.filter = numpy.append(numpy.full(self.filterNonLineLength,nonLineFilterColor), numpy.full(self.filterLineLength,lineFilterColor))
        self.filter = numpy.append(self.filter, numpy.full(self.filterNonLineLength,nonLineFilterColor))
        self.filterLength = len(self.filter)
        self.filterHalfLength = len(self.filter)/float(2)
        
        self.imageFilterWidth = self.imageWidth-self.filterLength
            
    def GetLinePosition(self, image, direction):        

        scanArea =  image[[self.sensorHeightStart, self.sensorHeightEnd],:]
        intensityLine = numpy.sum(scanArea, axis=0)
        
        lineDetect = numpy.convolve(intensityLine, self.filter,'valid')

        linePositionAbs = self.__GetLinePosition__(direction, lineDetect)
        
        if(lineDetect[int(linePositionAbs)] > self.FilterThresshold):
            linePositionAbs = linePositionAbs + self.filterHalfLength - 0.5                        
            linePosition = ((linePositionAbs)/float(self.imageWidth))*2.0-1.0
            return LineDetectInfo(True, linePosition)
        else:
            return LineDetectInfo(False, 0)        
        
    def __GetLinePosition__(self, direction, lineDetect):
        if(direction == SplitLineDirection.SplitRight()):
            lineDetect = lineDetect[::-1]
            linePositionAbs = len(lineDetect) - numpy.argmax(lineDetect>self.FilterThresshold) - 1
        elif(direction == SplitLineDirection.SplitLeft()):
            linePositionAbs = numpy.argmax(lineDetect>self.FilterThresshold)
        else:
            linePositionAbs = numpy.argmax(lineDetect)
        return linePositionAbs