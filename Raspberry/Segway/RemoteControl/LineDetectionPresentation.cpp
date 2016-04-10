#include "LineDetectionPresentation.h"
#include <boost/lexical_cast.hpp>

LineDetectionPresentation::LineDetectionPresentation(CameraSensor* cameraSensor, Position* position) {
    _CameraSensor = cameraSensor;
    _Position = position;
}

std::string LineDetectionPresentation::Presentation() {    
    std::string lineInfo = _CameraSensor->GetLine()->ToString();
    std::string cameraInfo = _CameraSensor->_LineDetect->ToString();
    
    return lineInfo + "\n" + cameraInfo;
}

LineDetectionPresentation::~LineDetectionPresentation() {
}

