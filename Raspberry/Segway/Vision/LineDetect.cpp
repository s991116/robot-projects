#include "LineDetect.h"
#include "Convert.h"
#include <cmath>
#include "Logging.h"

LineDetect::LineDetect(LineDetectSetting* lineDetectSetting, Logging* logging) {
    this->_LineDetectSetting = lineDetectSetting;
    if (_LineDetectSetting->ROI.width > _LineDetectSetting->ROI.height) {
        _SearchWidth = _LineDetectSetting->ROI.width;
    }
    else {
        _SearchWidth = _LineDetectSetting->ROI.height;
    }
    this->IntensityLine = new int[_SearchWidth];
    this->FilterResult = new int[_SearchWidth];
    this->_logging = logging;
}

LineInfo* LineDetect::DetectLine(cv::Mat imageMat) {
    cv::Mat detectImage = imageMat(_LineDetectSetting->ROI);
    CalculateIntensityLine(detectImage, this->IntensityLine); 
    LineInfo* lineInfo;
    if (_LineDetectSetting->MinLineWidth < 0)
        lineInfo = EdgeFilter(this->IntensityLine);
    else
        lineInfo = EdgeFilterOnly(this->IntensityLine);

    OffsetLine(lineInfo, _LineDetectSetting->PositionOffset);
    return lineInfo;
}

void LineDetect::CalculateIntensityLine(cv::Mat detectImage, int* intensityLine) { 
    int intensityPosition = 0;
    if (_LineDetectSetting->GetPosition() == LineDetectSetting::RIGHT) {
        for (int position = _SearchWidth - 1; position >= 0; position--) {
            CalculateIntensity(detectImage, intensityLine, &intensityPosition, position);            
        }
    } else {
        for (int position = 0; position < _SearchWidth; position++) {
            CalculateIntensity(detectImage, intensityLine, &intensityPosition, position);
        }
    }
}

void LineDetect::CalculateIntensity(cv::Mat detectImage, int* intensityLine, int* intensityPosition, int position) {
    intensityLine[*intensityPosition] = CalculateIntensityAtPosition(detectImage, position);    
    (*intensityPosition)++;
}

int LineDetect::CalculateIntensityAtPosition(cv::Mat detectImage, int position) {
    int intensity = 0;
    if (_LineDetectSetting->GetLineDirection() == LineDetectSetting::VERTICAL) {
        if (_LineDetectSetting->BlackLine) {
            for (int y = 0; y < _LineDetectSetting->ROI.height; y++) {
                cv::Scalar intensityScalar = detectImage.at<uchar>(y, position);
                intensity += 255 - intensityScalar.val[0];
            }
        } else {
            for (int y = 0; y < _LineDetectSetting->ROI.height; y++) {
                cv::Scalar intensityScalar = detectImage.at<uchar>(y, position);
                intensity += intensityScalar.val[0];
            }
        }
    } else {
        if (_LineDetectSetting->BlackLine) {
            for (int x = 0; x < _LineDetectSetting->ROI.width; x++) {
                cv::Scalar intensityScalar = detectImage.at<uchar>(position, x);
                intensity += 255 - intensityScalar.val[0];
            }
        } else {
            for (int x = 0; x < _LineDetectSetting->ROI.width; x++) {
                cv::Scalar intensityScalar = detectImage.at<uchar>(position, x);
                intensity += intensityScalar.val[0];
            }
        }
    }
    return intensity;
}

LineInfo* LineDetect::EdgeFilter(int* intensityLine) {
    int sumFirstHalf = LineDetect::FilterFirstHalf(intensityLine);
    int sumSecondHalf = LineDetect::FilterSecondHalf(intensityLine);

    int middle = _LineDetectSetting->FilterHalf;
    int end = 2 * _LineDetectSetting->FilterHalf;

    MaxFilterValue = sumFirstHalf - sumSecondHalf;
    MaxFilterIndex = middle;
    MinFilterValue = MaxFilterValue;
    MinFilterIndex = MaxFilterIndex;
    int FilterIndexValue = 0;
    for (int start = 0; start < _SearchWidth - 2 * _LineDetectSetting->FilterHalf; start++) {
        sumFirstHalf = sumFirstHalf - intensityLine[start] + intensityLine[middle];
        sumSecondHalf = sumSecondHalf - intensityLine[middle] + intensityLine[end];
        middle++;
        end++;

        int FilterValue = sumFirstHalf - sumSecondHalf;
        FilterResult[start] = FilterValue;

        if (_LineDetectSetting->GetPosition() == LineDetectSetting::CENTER) {
            if (FilterValue > MaxFilterValue) {
                MaxFilterIndex = middle;
                MaxFilterValue = FilterValue;
                FilterIndexValue = FilterValue;
            } else if (FilterValue < MinFilterValue) {
                MinFilterIndex = middle;
                MinFilterValue = FilterValue;
                FilterIndexValue = FilterValue;
            }
        } else {
            if (std::abs(FilterValue) > _LineDetectSetting->FilterThresshold) {
                if (_LineDetectSetting->GetPosition() == LineDetectSetting::RIGHT) {
                    //LogFilterResult(0, FilterValue, _SearchWidth - middle);
                    return new LineInfo(true, _SearchWidth - middle, _SearchWidth);
                } else {
                    //LogFilterResult(0, FilterValue, middle);
                    return new LineInfo(true, middle, _SearchWidth);
                }
            }
        }
    }

    if (_LineDetectSetting->GetPosition() == LineDetectSetting::CENTER) {
        int minLineWidth = 1;
        if (MaxFilterValue > _LineDetectSetting->FilterThresshold || MinFilterValue < -_LineDetectSetting->FilterThresshold) {
            if (MaxFilterIndex > MinFilterIndex) {
                int lineWidth = MaxFilterIndex - MinFilterIndex;
                int centerIndex = MinFilterIndex + (lineWidth) / 2;
                //LogFilterResult(MinFilterValue, MaxFilterValue, centerIndex);
                return new LineInfo(true, centerIndex, _SearchWidth, lineWidth);
            }
            if (MaxFilterValue < -MinFilterValue) {
                return new LineInfo(true, _LineDetectSetting->ROI.width, _SearchWidth, minLineWidth);
            } else {
                return new LineInfo(true, 0, _SearchWidth, minLineWidth);
            }
        }
    }
    //LogFilterResult(MinFilterValue, MaxFilterValue, 0);
    return new LineInfo(false, 0, _SearchWidth);
}

LineInfo* LineDetect::EdgeFilterOnly(int* intensityLine) {
    int sumFirstHalf = LineDetect::FilterFirstHalf(intensityLine);
    int sumSecondHalf = LineDetect::FilterSecondHalf(intensityLine);

    int middle = _LineDetectSetting->FilterHalf;
    int end = 2 * _LineDetectSetting->FilterHalf;

    MaxFilterValue = _LineDetectSetting->FilterThresshold;
    MaxFilterIndex = 0;
    MinFilterValue = -_LineDetectSetting->FilterThresshold;
    MinFilterIndex = 0;

    bool MaxFilterValueFound = false;
    bool MinFilterValueFound = false;
    int index;
    int FilterIndexValue = 0;
    for (index = 0; index < _SearchWidth - 2 * _LineDetectSetting->FilterHalf; index++) {
        sumFirstHalf = sumFirstHalf - intensityLine[index] + intensityLine[middle];
        sumSecondHalf = sumSecondHalf - intensityLine[middle] + intensityLine[end];
        middle++;
        end++;

        int FilterValue = sumFirstHalf - sumSecondHalf;
        FilterResult[index] = FilterValue;

        if (FilterValue > MaxFilterValue) {
            if (MinFilterValueFound) {
                if (index > MinFilterIndex + _LineDetectSetting->MinLineWidth) {
                    MaxFilterValueFound = true;
                    MaxFilterValue = FilterValue;
                    MaxFilterIndex = middle;
                    //				_logging->Log("MaxFilter and MinFilter found. MaxFilterIndex is: ", MaxFilterIndex);
                } else {
                    MaxFilterValue = _LineDetectSetting->FilterThresshold;
                    MinFilterValue = -_LineDetectSetting->FilterThresshold;
                    MaxFilterIndex = middle;
                    MinFilterIndex = 0;
                    MinFilterValueFound = false;
                    MaxFilterValueFound = false;
                    //				_logging->Log("MaxFilter found but to close to MinFilter. MaxFilterIndex is: ", MaxFilterIndex);
                }
            } else {
                MaxFilterValueFound = true;
                MaxFilterValue = FilterValue;
                MaxFilterIndex = middle;
                //			_logging->Log("MaxFilter found and no MinFilter found. MaxFilterIndex is: ", MaxFilterIndex);
            }
        } else {
            if (FilterValue < MinFilterValue) {
                if (MaxFilterValueFound) {
                    if (index > MaxFilterIndex + _LineDetectSetting->MinLineWidth) {
                        MinFilterValue = FilterValue;
                        MinFilterIndex = middle;
                        MinFilterValueFound = true;
                        //    				_logging->Log("MaxFilter and MinFilter found. MinFilterIndex is: ", MinFilterIndex);
                    } else {
                        MaxFilterValue = _LineDetectSetting->FilterThresshold;
                        MinFilterValue = -_LineDetectSetting->FilterThresshold;
                        MaxFilterIndex = 0;
                        MinFilterIndex = middle;
                        MinFilterValueFound = false;
                        MaxFilterValueFound = false;
                        //				    _logging->Log("MinFilter found, but to close to MaxFilter. MinFilterIndex is: ", MinFilterIndex);
                    }
                } else {
                    MinFilterValueFound = true;
                    MinFilterValue = FilterValue;
                    MinFilterIndex = middle;
                    //    			_logging->Log("MinFilter found and no MaxFilter found. MinFilterIndex is: ", MinFilterIndex);
                }
            } else {
                if (MinFilterValueFound && MaxFilterValueFound) {
                    int lineWidth = MaxFilterIndex - MinFilterIndex;
                    if (lineWidth < 0)
                        lineWidth = -lineWidth;

                    int centerindex = (MinFilterIndex + MaxFilterIndex) / 2;
                    if (_LineDetectSetting->GetPosition() == LineDetectSetting::RIGHT) {
                        centerindex = _SearchWidth - centerindex;
                    }
                    //            	_logging->Log("Centerindex:" , centerindex);
                    return new LineInfo(true, centerindex, _SearchWidth, lineWidth);
                }
            }
        }
    }
    if (MinFilterValueFound && MaxFilterValueFound) {
        int lineWidth = MaxFilterIndex - MinFilterIndex;
        if (lineWidth < 0)
            lineWidth = -lineWidth;

        int centerindex = (MinFilterIndex + MaxFilterIndex) / 2;
        //_logging->Log("Centerindex:" , centerindex);
        return new LineInfo(true, centerindex, _SearchWidth, lineWidth);
    }
    return new LineInfo(false, 0, _SearchWidth);
}

int LineDetect::FilterFirstHalf(int* intensityLine) {
    int sumFirstHalf = 0;
    for (int x = 0; x < _LineDetectSetting->FilterHalf; x++) {
        sumFirstHalf += intensityLine[x];
    }
    return sumFirstHalf;
}

int LineDetect::FilterSecondHalf(int* intensityLine) {
    int sumSecondHalf = 0;
    for (int x = _LineDetectSetting->FilterHalf; x < 2 * _LineDetectSetting->FilterHalf; x++) {
        sumSecondHalf += intensityLine[x];
    }
    return sumSecondHalf;
}

void LineDetect::OffsetLine(LineInfo* lineInfo, int positionOffset) {
    int position = lineInfo->GetPosition() - positionOffset;
    lineInfo->SetPosition(position);
}

void LineDetect::LogFilterResult(int MinFilterValue, int MaxFilterValue, int centerIndex) {
    _logging->Log("MinFilterValue", MinFilterValue);
    _logging->Log("MinFilterIndex", MinFilterIndex);
    _logging->Log("MaxFilterValue", MaxFilterValue);
    _logging->Log("MaxFilterIndex", MaxFilterIndex);
    _logging->Log("CenterIndex", centerIndex);
    _logging->Log("_SearchWidth", _SearchWidth);
}

std::string LineDetect::ToString() {
    std::string result = "";
    result += "MinFilterValue: " + Convert::IntToString(MinFilterValue) + "\n";
    result += "MinFilterIndex: " + Convert::IntToString(MinFilterIndex) + "\n";
    result += "MaxFilterValue: " + Convert::IntToString(MaxFilterValue) + "\n";
    result += "MaxFilterIndex: " + Convert::IntToString(MaxFilterIndex) + "\n";
    result += "FilterThresshold: " + Convert::IntToString(this->_LineDetectSetting->FilterThresshold) + "\n";

    return result;
}
