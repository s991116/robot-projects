#include <DetectTemplateObject.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

DetectTemplateObject::DetectTemplateObject(cv::Mat imageTemplate) {
	this->_template = imageTemplate;
	//Method: 0: SQDIFF 1: SQDIFF NORMED 2: TM CCORR 3: TM CCORR NORMED 4: TM COEFF 5: TM COEFF NORMED
	this->_match_method = 0;
}

void DetectTemplateObject::GetPosition(cv::Mat image, Position* position) {
  Mat result;
  
  /// Create the result matrix
  int result_cols =  image.cols - _template.cols + 1;
  int result_rows = image.rows - _template.rows + 1;

  result.create( result_cols, result_rows, CV_32FC1 );

  /// Do the Matching and Normalize
  matchTemplate( image, _template, result, _match_method );
  normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

  /// Localizing the best match with minMaxLoc
  double minVal; double maxVal; Point minLoc; Point maxLoc;
  Point matchLoc;

  minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

  /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
  if( _match_method  == CV_TM_SQDIFF || _match_method == CV_TM_SQDIFF_NORMED )
    { matchLoc = minLoc; }
  else
    { matchLoc = maxLoc; }

  Point center = Point(matchLoc.x + _template.cols/2 ,matchLoc.y + _template.rows/2);

  position->Detected = true;
  position->PositionX = (center.x) / (float) result_cols;
  position->PositionY = (center.y) / (float) result_rows;  
  
  return;
}