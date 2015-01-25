#ifndef LINEDETECT_H
#define	LINEDETECT_H

#include <LineDetectSetting.h>
#include <LineInfo.h>
#include <Logging.h>
#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>


class LineDetect{
public:
    LineDetect(LineDetectSetting* lineDetectSetup, Logging* logging);
    LineInfo* DetectLine(cv::Mat imageMat);
    LineDetectSetting* _LineDetectSetting;
    std::string ToString();

private:
    int* IntensityLine;
    Logging* _logging;
    int _SearchWidth;
    void CalculateIntensityLine(cv::Mat detectImage, int* intensityLine);
    int CalculateIntensityAtPosition(cv::Mat detectImage, int position);
    void CalculateIntensity(cv::Mat detectImage, int* intensityLine, int* intensityPosition, int position);
    int MaxFilterValue;
    int MaxFilterIndex;
    int MinFilterValue;
    int MinFilterIndex;
    int* FilterResult;
    LineInfo* EdgeFilter(int* intensityLine);
    int FilterFirstHalf(int* intensityLine);
    int FilterSecondHalf(int* intensityLine);
    void LogFilterResult(int MinFilterValue, int MaxFilterValue, int centerIndex);
};

#endif	/* LINEDETECT_H */