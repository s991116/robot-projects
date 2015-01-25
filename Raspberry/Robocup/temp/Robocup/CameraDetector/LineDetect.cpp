#include "LineDetect.h"
#include <cmath>
#include "EmptyLogger.h"

LineDetect::LineDetect(LineDetectSetting* lineDetectSetting) {
  this->_LineDetectSetting = lineDetectSetting;
  if(_LineDetectSetting->ROI.width > _LineDetectSetting->ROI.height)
  {  
    _SearchWidth = _LineDetectSetting->ROI.width;
  }
  else  
  {  
    _SearchWidth = _LineDetectSetting->ROI.height;
  }
  this->IntensityLine = new int[_SearchWidth];
  this->_logging = new EmptyLogger();  
}

LineInfo* LineDetect::DetectLine(cv::Mat imageMat, Logging* logging)
{    
  cv::Mat detectImage = imageMat(_LineDetectSetting->ROI);
    logging->Log("IntensityLine\n");
    CalculateIntensityLine(detectImage, this->IntensityLine, logging);
    logging->Log("EdgeFilter\n");
    LineInfo* lineInfo = EdgeFilter(this->IntensityLine, logging);
    return lineInfo;
}

LineInfo* LineDetect::DetectLine(cv::Mat imageMat)
{
   return this->DetectLine(imageMat, this->_logging); 
}

void LineDetect::CalculateIntensityLine(cv::Mat detectImage, int* intensityLine, Logging* logging) {
    int intensityPosition = 0;
    if(_LineDetectSetting->Position == LineDetectSetting::RIGHT)
    {
      for(int position=_SearchWidth-1; position>=0; position--)
      {
        CalculateIntensity(detectImage, intensityLine, &intensityPosition, position, logging);
      }
    }
    else
    {
      for(int position=0; position<_SearchWidth; position++)
      {
        CalculateIntensity(detectImage, intensityLine, &intensityPosition, position, logging);  
      }
    }
}

void LineDetect::CalculateIntensity(cv::Mat detectImage, int* intensityLine, int* intensityPosition, int position, Logging* logging)
{
        intensityLine[*intensityPosition] = CalculateIntensityAtPosition(detectImage, position);
        logging->Log(intensityLine[*intensityPosition]);
        (*intensityPosition)++;
}

int LineDetect::CalculateIntensityAtPosition(cv::Mat detectImage, int position)    
{
  int intensity = 0;
  if(_LineDetectSetting->LineDirection == LineDetectSetting::VERTICAL)
  {
    if(_LineDetectSetting->BlackLine)
    {
      for(int y=0; y<_LineDetectSetting->ROI.height; y++)
    {
        cv::Scalar intensityScalar = detectImage.at<uchar>(y, position);
        intensity += 255-intensityScalar.val[0];
      }  
    }
    else
    {
      for(int y=0; y<_LineDetectSetting->ROI.height; y++)
      {
        cv::Scalar intensityScalar = detectImage.at<uchar>(y, position);
        intensity += intensityScalar.val[0];
      }         
    }
  }
  else
  {
    if(_LineDetectSetting->BlackLine)
    {
      for(int x=0; x<_LineDetectSetting->ROI.width; x++)
      {
        cv::Scalar intensityScalar = detectImage.at<uchar>(position, x);
        intensity += 255-intensityScalar.val[0];
      }  
    }
    else
    {
      for(int x=0; x<_LineDetectSetting->ROI.width; x++)
      {
        cv::Scalar intensityScalar = detectImage.at<uchar>(position, x);
        intensity += intensityScalar.val[0];
      }         
    }
  }
  return intensity;
}
    
LineInfo* LineDetect::EdgeFilter(int* intensityLine, Logging* logging)
{
    int sumFirstHalf = LineDetect::FilterFirstHalf(intensityLine);
    int sumSecondHalf = LineDetect::FilterSecondHalf(intensityLine);
    
    int middle = _LineDetectSetting->FilterHalf;
    int end = 2*_LineDetectSetting->FilterHalf;

    int MaxFilterValue = sumFirstHalf-sumSecondHalf;
    int MaxFilterIndex = middle;
    int MinFilterValue = MaxFilterValue;
    int MinFilterIndex = MaxFilterIndex;

    for(int start=0; start<_SearchWidth-2*_LineDetectSetting->FilterHalf; start++)
    {
        sumFirstHalf = sumFirstHalf - intensityLine[start] + intensityLine[middle];
        sumSecondHalf = sumSecondHalf - intensityLine[middle] + intensityLine[end];
        middle++;
        end++;        
        
        int FilterValue = sumFirstHalf-sumSecondHalf;
        logging->Log(FilterValue);
        if(_LineDetectSetting->Position == LineDetectSetting::CENTER)
        {
          if(FilterValue > MaxFilterValue)
          {
            MaxFilterIndex = middle;
            MaxFilterValue = FilterValue;
          }
          else if(FilterValue < MinFilterValue)
          {
            MinFilterIndex = middle;
            MinFilterValue = FilterValue;
          }
        }
        else
        {
          if(std::abs(FilterValue) > _LineDetectSetting->FilterThresshold)
          {
            if(_LineDetectSetting->Position == LineDetectSetting::RIGHT) {
              LogFilterResult(0, FilterValue, _SearchWidth-middle, logging);
              return new LineInfo(true, _SearchWidth-middle, _SearchWidth);
            }
            else
            {
              LogFilterResult(0, FilterValue, middle, logging);
              return new LineInfo(true, middle, _SearchWidth);
            }
          }            
        }
    }
    
    if(_LineDetectSetting->Position == LineDetectSetting::CENTER)
    {
      if(MaxFilterValue > _LineDetectSetting->FilterThresshold || MinFilterValue < -_LineDetectSetting->FilterThresshold)
      {
        if(MaxFilterIndex > MinFilterIndex)
        {
          int centerIndex = MinFilterIndex + (MaxFilterIndex - MinFilterIndex)/2;
          LogFilterResult(MinFilterValue, MaxFilterValue, centerIndex, logging);
          return new LineInfo(true, centerIndex, _LineDetectSetting->ROI.width);
        }
      
        if(MaxFilterValue < -MinFilterValue)
        {
          return new LineInfo(true, _LineDetectSetting->ROI.width, _SearchWidth);
        }
        else
        {
          return new LineInfo(true, 0, _SearchWidth);
        }
      }
    }
    LogFilterResult(MinFilterValue, MaxFilterValue, 0, logging);
    return new LineInfo(false, 0, _SearchWidth);
}

int LineDetect::FilterFirstHalf(int* intensityLine)
{
    int sumFirstHalf = 0;
    for(int x=0; x<_LineDetectSetting->FilterHalf; x++)
    {
      sumFirstHalf += intensityLine[x];
    }
    return sumFirstHalf;
}

int LineDetect::FilterSecondHalf(int* intensityLine)
{
    int sumSecondHalf = 0;
    for(int x=_LineDetectSetting->FilterHalf; x<2*_LineDetectSetting->FilterHalf; x++)
    {
      sumSecondHalf += intensityLine[x];
    }
    return sumSecondHalf;
}

void LineDetect::LogFilterResult(int MinFilterValue, int MaxFilterValue, int centerIndex, Logging* logging)
{
  logging->Log("MinFilterValue", MinFilterValue);
  logging->Log("MaxFilterValue", MaxFilterValue);
  logging->Log("CenterIndex", centerIndex);
  logging->Log("_SearchWidth", _SearchWidth);
}
