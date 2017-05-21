from picamera.array import PiRGBArray
import SplitLineDirection
import numpy
from LineDetectInfo import LineDetectInfo
import logging
from vlogging import VisualRecord

class LineDetect():
    
    def __init__(self, settingsOverride={}):
        self.logger = logging.getLogger('Segway')
        self.__DefaultSettings__()
        self.settings.update(settingsOverride)
        self.UpdateSettings(settingsOverride)
            
    def __DefaultSettings__(self):
        self.settings = {
            'SensorHeightStart': 101,
            'SensorHeightEnd': 105,
            'ImageWidth': 320,
            'FilterLineLength': 31,
            'FilterNonLineLength': 5,
            'Blackline': True,
            'FilterThresshold': 100            
        }
    def UpdateSettings(self, settingsOverride):
        self.SetDetectHeight(self.settings['SensorHeightStart'], self.settings['SensorHeightEnd'])
        self.imageWidth = self.settings['ImageWidth']
        self.SetFilter(self.settings['FilterLineLength'], self.settings['FilterNonLineLength'], self.settings['Blackline'])
        self.SetImageWidth(self.settings['ImageWidth'])
        self.SetFilterThresshold(self.settings['FilterThresshold'])

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
            
    def GetLinePosition(self, image, direction, enableLog=True):        

        scanArea =  image[[self.sensorHeightStart, self.sensorHeightEnd],:]
        intensityLine = numpy.sum(scanArea, axis=0)
        lineDetect = numpy.convolve(intensityLine, self.filter,'valid')

        linePositionAbs = self.__GetLinePosition__(direction, lineDetect)
        
        if self.logger.isEnabledFor(logging.DEBUG) & enableLog:
            debugImage = self.__CreateDebugImage__(image, lineDetect, linePositionAbs)
            self.logger.debug(VisualRecord(("Max filter value = %d , Thresshold = %d" % (numpy.amax(lineDetect), self.FilterThresshold)), [debugImage], fmt = "png"))
            
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
        
    def __CreateDebugImage__(self, image, lineDetect, linePositionAbs):
        import cv2
        debugImage = cv2.cvtColor(image, cv2.COLOR_GRAY2RGB)
        cv2.rectangle(debugImage, (0, self.sensorHeightStart), (self.imageWidth-1, self.sensorHeightEnd), (255,0,0), 2)
        
        lineDetectMax = max(self.FilterThresshold, numpy.amax(lineDetect))
        lineDetectMin = min(self.FilterThresshold, numpy.amin(lineDetect))
        lineDetectRange = float(lineDetectMax - lineDetectMin)
        lineOffsetX = (self.imageWidth-len(lineDetect))/2
        height, width = image.shape[:2]

        cv2.rectangle(debugImage, (linePositionAbs+lineOffsetX,self.sensorHeightStart), (linePositionAbs+lineOffsetX, self.sensorHeightEnd), (255,0,255), 3)

        for index in range(0, len(lineDetect)-1):
            x = index + lineOffsetX
            y = int(((lineDetect[index] - lineDetectMin)/lineDetectRange) * height)
            cv2.line(debugImage,(x,y),(x,y),(0,0,255),2)
        thressholdCoordinateY = y = int(((self.FilterThresshold - lineDetectMin)/lineDetectRange) * height)
        cv2.line(debugImage, (0,thressholdCoordinateY), (self.imageWidth-1,thressholdCoordinateY), (0,255,255),2)
        return debugImage