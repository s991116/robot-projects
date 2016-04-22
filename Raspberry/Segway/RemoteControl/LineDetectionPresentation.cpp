#include "LineDetectionPresentation.h"
#include <boost/lexical_cast.hpp>

LineDetectionPresentation::LineDetectionPresentation(CameraSensor* cameraSensor, Position* position) {
    _CameraSensor = cameraSensor;
    _Position = position;
}

std::string LineDetectionPresentation::Presentation() {    
    std::string lineInfo = _CameraSensor->GetLine()->ToString();
    std::string cameraInfo = _CameraSensor->_LineDetect->ToString();

    std::string sensorLineInfo = _CameraSensor->GetSensorLine()->ToString();
    std::string sensorCameraInfo = _CameraSensor->_SensorLineDetect->ToString();
    
    return "Line:\n" + lineInfo + "\n" + cameraInfo + "\n \n" + "Sensor:\n" + sensorLineInfo + "\n" + sensorCameraInfo;
}

LineDetectionPresentation::~LineDetectionPresentation() {
}

