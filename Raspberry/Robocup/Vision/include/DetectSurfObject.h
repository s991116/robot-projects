#ifndef DETECTSURFOBJECT_H
#define	DETECTSURFOBJECT_H

#include <CameraDetector.h>
#include <Position.h>
#include <DetectObject.h>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class DetectSurfObject : public DetectObject {
  
  public:
    DetectSurfObject(int hessianValue);    
    void GetPosition(cv::Mat image, Position* position);
    void SetTemplate(cv::Mat object);
	
  private:
    cv::Mat _template, objectMat;
    float nndrRatio;
	std::vector< cv::Point2f > obj_corners;
    std::vector< cv::KeyPoint > keypointsO;
    std::vector< cv::KeyPoint > keypointsS;
    cv::Mat descriptors_object, descriptors_scene;
	cv::SurfFeatureDetector surf; 
	cv::SurfDescriptorExtractor extractor;
	cv::FlannBasedMatcher matcher;
    std::vector< std::vector< cv::DMatch >  > matches;
	std::vector< cv::DMatch > good_matches;
	std::vector< cv::Point2f > obj;
    std::vector< cv::Point2f > scene;
 
};

#endif	/* DETECTSURFOBJECT_H */