#include "LineDetectionPresentation.h"

LineDetectionPresentation::LineDetectionPresentation(CameraSensor* cameraSensor, Position* position) {
    _CameraSensor = cameraSensor;
    _Position = position;
}

std::string LineDetectionPresentation::Presentation() {
    return "test";
}

LineDetectionPresentation::~LineDetectionPresentation() {
}

