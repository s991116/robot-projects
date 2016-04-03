#include "CameraSensor.h"

CameraSensor::CameraSensor(PiCamera* piCamera, FaceDetection* faceDetection, LineDetect* lineDetect, Servo* servo) {
    _PiCamera = piCamera;
    _FaceDetection = faceDetection;
    _LineDetect = lineDetect;
    _Servo = servo;
    _MoveFactor = 20;
}

void CameraSensor::GetFacePosition(Position* position) {
    _PiCamera->SetFrameSize(320, 240);
    cv::Mat image = _PiCamera->GetNextFrame();
    _FaceDetection->GetFacePosition(image, position);
    MoveCamera(position);
}

std::string CameraSensor::GetStatus() {
    std::string info;
    double linePos = GetLinePosition();
    return GetLine()->ToString();
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

LineInfo* CameraSensor::GetLine() {
    cv::Mat image = _PiCamera->GetNextFrame();
    LineInfo* lineinfo = _LineDetect->DetectLine(image);
    return lineinfo;
}

double CameraSensor::GetLinePosition() {
    _PiCamera->SetFrameSize(320, 240);
    cv::Mat image = _PiCamera->GetNextFrame();
    LineInfo* lineinfo = _LineDetect->DetectLine(image);
    return lineinfo->GetNormalizePosition();
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