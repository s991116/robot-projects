#include "FaceDetectionPresentation.h"

FaceDetectionPresentation::FaceDetectionPresentation(CameraSensor* cameraSensor, Position* position) {
    _CameraSensor = cameraSensor;
    _Position = position;
}

std::string FaceDetectionPresentation::Presentation() {
    _CameraSensor->GetFacePosition(_Position);
    if(_Position->Detected())
    {
        std::ostringstream stringStream;
        stringStream << "Face detected Position( " << _Position->GetNormalizedX() << " , " << _Position->GetNormalizedY() << " )";
        return stringStream.str();
    }
    else
        return std::string("No face detected");
}

FaceDetectionPresentation::~FaceDetectionPresentation() {
}

