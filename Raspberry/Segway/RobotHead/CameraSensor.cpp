#include "CameraSensor.h"

CameraSensor::CameraSensor(PiCamera* piCamera, FaceDetection* faceDetection, Servo* servo) {
    _PiCamera = piCamera;
    _FaceDetection = faceDetection;
    _Servo = servo;
    _MoveFactor = 20;
}

bool CameraSensor::GetFacePosition(Position* position) {
    _PiCamera->SetFrameSize(320, 240);
    cv::Mat image = _PiCamera->GetNextFrame();
    bool detected = _FaceDetection->GetFacePosition(image, position);
    MoveCamera(position);
    return detected;
}

void CameraSensor::MoveCamera(Position* position) {
    float xOffset = position->GetX();
    if(xOffset > 0)
    {
        _Servo->StepRight(xOffset * _MoveFactor);
    }
    else if(position->GetX() < 0)
    {
        _Servo->StepLeft(-xOffset * _MoveFactor);
    }
    float yOffset = position->GetY();
    if(yOffset > 0)
    {
        _Servo->StepDown(yOffset * _MoveFactor);
    }
    else if(position->GetY() < 0)
    {
        _Servo->StepUp(-yOffset * _MoveFactor);
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