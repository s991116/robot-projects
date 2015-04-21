#ifndef FINDLINESETTING_H
#define	FINDLINESETTING_H

#include "LinePosition.h"
#include "LineDetect.h"
#include <opencv/cv.h>

class FindLineSetting {
public:
    
    FindLineSetting(LineDetect* leftDetect, LineDetect* rightDetect, LineDetect* topDetect);
    void GetLinePosition(cv::Mat image, LinePosition* linePosition);
    void GetLeftLinePosition(cv::Mat image, LinePosition* linePosition);
    void GetRightLinePosition(cv::Mat image, LinePosition* linePosition);
    
    LineDetect* _LeftDetect;
    LineDetect* _RightDetect;
    LineDetect* _TopDetect;
private:
    LinePosition::SearchStatusEnum GetSearchStatus(LineInfo* leftLineInfo, LineInfo* rightLineInfo, LineInfo* topLineInfo);
};

#endif	/* FINDLINESETTING_H */

