#include "FaceDetectionPresentation.h"

FaceDetectionPresentation::FaceDetectionPresentation(CameraSensor* cameraSensor, Position* position) {
    _CameraSensor = cameraSensor;
    _Position = position;
}

std::string FaceDetectionPresentation::Presentation() {
    bool detected = _CameraSensor->GetFacePosition(_Position);
    if(detected)
    {
        std::ostringstream stringStream;
        stringStream << "Face detected Position( " << _Position->GetX() << " , " << _Position->GetY() << " )";
        return stringStream.str();
    }
    else
        return std::string("No face detected");
}

FaceDetectionPresentation::~FaceDetectionPresentation() {
}

