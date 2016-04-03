#include "LineDetectionPresentation.h"
#include <boost/lexical_cast.hpp>

LineDetectionPresentation::LineDetectionPresentation(CameraSensor* cameraSensor, Position* position) {
    _CameraSensor = cameraSensor;
    _Position = position;
}

std::string LineDetectionPresentation::Presentation() {
    double position = _CameraSensor->GetLinePosition();
    return boost::lexical_cast<std::string>(position );
}

LineDetectionPresentation::~LineDetectionPresentation() {
}

