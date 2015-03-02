#include <DetectSurfObject.h>
using namespace cv;

DetectSurfObject::DetectSurfObject(int hessianValue) {
  this->nndrRatio = 0.7f;
  obj_corners = std::vector< Point2f >(4);
  
  this->surf = SurfFeatureDetector(hessianValue);
}

void DetectSurfObject::SetTemplate(cv::Mat object) {
  this->objectMat = object;
  
  surf.detect(objectMat,keypointsO);
  extractor.compute( objectMat, keypointsO, descriptors_object );
}

void DetectSurfObject::GetPosition(cv::Mat sceneMat, Position* position) {
    keypointsS.clear();
	surf.detect(sceneMat,keypointsS);
	
	if(keypointsS.size() < 7 ||   keypointsO.size() < 7) //Not enough keypoints, object not found 
	{
		position->Detected = false;
		return; 
	}
	
	extractor.compute( sceneMat, keypointsS, descriptors_scene );
	matches.clear();
	good_matches.clear();
	
	matcher.knnMatch( descriptors_object, descriptors_scene, matches, 2 );
	
	good_matches.reserve(matches.size());  
     
    for (size_t i = 0; i < matches.size(); ++i)
    { 
      if (matches[i].size() < 2)
        continue;
     
      const DMatch &m1 = matches[i][0];
      const DMatch &m2 = matches[i][1];
     
      if(m1.distance <= nndrRatio * m2.distance)        
        good_matches.push_back(m1);     
    }
	
    if( (good_matches.size() <7))
	{
		position->Detected = false;
		return;
	}
  
    obj.clear();
	scene.clear();
    for( unsigned int i = 0; i < good_matches.size(); i++ )
    {
        //-- Get the keypoints from the good matches
        obj.push_back( keypointsO[ good_matches[i].queryIdx ].pt );
        scene.push_back( keypointsS[ good_matches[i].trainIdx ].pt );
    }
	
	Mat H = findHomography( obj, scene, CV_RANSAC );
 
    //-- Get the corners from the image_1 ( the object to be "detected" )
    obj_corners[0] = cvPoint(0,0); 
	obj_corners[1] = cvPoint( objectMat.cols, 0 );
    obj_corners[2] = cvPoint( objectMat.cols, objectMat.rows ); 
	obj_corners[3] = cvPoint( 0, objectMat.rows );
    std::vector< Point2f > scene_corners(4);
    
    perspectiveTransform( obj_corners, scene_corners, H);
	
	float center_x,center_y;
	for(unsigned int i = 0; i< 4; ++i)
	{
	  center_x += scene_corners[i].x;
	  center_y += scene_corners[i].y;
	}
	center_x = center_x / 4.0;
    center_y = center_y / 4.0;

    position->SetImagePosition(center_x, center_y, sceneMat.cols, sceneMat.rows);	
    position->Detected = true;
}