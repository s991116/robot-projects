#include "CameraSensor.h"

CameraSensor::CameraSensor(PiCamera* piCamera, LineDetect* lineDetect, LineDetect* sensorLineDetect, Servo* servo) {
    _PiCamera = piCamera;
    _LineDetect = lineDetect;
    _SensorLineDetect = sensorLineDetect;
    _Servo = servo;
    _MoveFactor = 8;
    _Width = 0;
    _Height = 0;
    UpdateFrameSize(320,240);
}

void CameraSensor::UpdateFrameSize(int width, int height)
{
    if(_Width != width || _Height != height)
    {
      _PiCamera->SetFrameSize(width, height);
      _Width = width;
      _Height = height;
    }
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
        _Servo->StepDown(-yOffset * _MoveFactor);       
    }
}

LineInfo* CameraSensor::GetLine() {
    UpdateFrameSize(320,240);
    UpdateCameraPosition(88,130);
    cv::Mat image = _PiCamera->GetNextFrame();
    LineInfo* lineinfo = _LineDetect->DetectLine(image);
    return lineinfo;
}

double CameraSensor::GetLinePosition() {
    UpdateFrameSize(320,240);
    UpdateCameraPosition(88,125);
    cv::Mat image = _PiCamera->GetNextFrame();
    LineInfo* lineinfo = _LineDetect->DetectLine(image);
    return lineinfo->GetNormalizePosition();
}

LineInfo* CameraSensor::GetSensorLine() {
    UpdateFrameSize(320,240);
    UpdateCameraPosition(88,130);
    cv::Mat image = _PiCamera->GetNextFrame();
    LineInfo* lineinfo = _SensorLineDetect->DetectLine(image);
    return lineinfo;
}

LineInfo* CameraSensor::GetSensorLine(std::string filename) {
    UpdateFrameSize(320,240);
    UpdateCameraPosition(88,130);
    cv::Mat image = _PiCamera->GetNextFrame();
    LineInfo* lineinfo = _SensorLineDetect->DetectLine(image);
    return lineinfo;
}


void CameraSensor::UpdateCameraPosition(int horizontal,int vertical)
{    
    _Servo->SetHorizontalPosition(horizontal);
    _Servo->SetVerticalPosition(vertical);
}

void CameraSensor::MoveToCenter() {
    _Servo->ToCenter();
}

void CameraSensor::TakePicture(std::string filename) {
    UpdateFrameSize(320,240);
    cv::Mat image = _PiCamera->GetNextFrame();
    cv::imwrite( filename, image );
}

LineInfo* CameraSensor::GetLine(std::string filename) {
    cv::Mat image = cv::imread(filename);
    return _LineDetect->DetectLine(image);
}

CameraSensor::~CameraSensor() {
}