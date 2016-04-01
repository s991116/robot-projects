#include "CameraSensor.h"

CameraSensor::CameraSensor(PiCamera* piCamera, FaceDetection* faceDetection, Servo* servo) {
    _PiCamera = piCamera;
    _FaceDetection = faceDetection;

    _Servo = servo;
    _MoveFactor = 20;
}

void CameraSensor::GetFacePosition(Position* position) {
    _PiCamera->SetFrameSize(320, 240);
    cv::Mat image = _PiCamera->GetNextFrame();
    _FaceDetection->GetFacePosition(image, position);
    MoveCamera(position);
}

void CameraSensor::MoveCamera(Position* position) {
    if(position->Detected())
    {
        float xOffset = position->GetNormalizedX();
        _Servo->StepRight(xOffset * _MoveFactor);
        float yOffset = position->GetNormalizedY();
        _Servo->StepDown(yOffset * _MoveFactor);       
    }
}

void CameraSensor::MoveToCenter() {
    _Servo->ToCenter();
}

void CameraSensor::TakePicture(std::string filename) {
    cv::Mat image = _PiCamera->GetNextFrame();
    cv::imwrite( filename, image );
}

CameraSensor::~CameraSensor() {
}