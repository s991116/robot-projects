#include <DetectSurfObject.h>
using namespace cv;

DetectSurfObject::DetectSurfObject(int hessianValue, int minGoodMatches, Logging* logging) {
  this->nndrRatio = 0.7f;
  _minGoodMatches = minGoodMatches;
  obj_corners = std::vector< Point2f >(4);

  this->surf = SurfFeatureDetector(hessianValue);
  _Logging = logging;
}

void DetectSurfObject::SetTemplate(cv::Mat object) {
  this->objectMat = object;

  surf.detect(objectMat,keypointsO);
  extractor.compute( objectMat, keypointsO, descriptors_object );
}

void DetectSurfObject::GetPosition(cv::Mat sceneMat, Position* position, std::vector< Point2f >* scene_corners) {
    keypointsS.clear();
	surf.detect(sceneMat,keypointsS);

	if((int)keypointsS.size() < _minGoodMatches ||   (int)keypointsO.size() < _minGoodMatches) //Not enough keypoints, object not found 
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

	_Logging->Log("Good matches: ", (int)(good_matches.size()));
    if((int)good_matches.size() < _minGoodMatches)
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

	std::vector<Point2f> obj_transformed_corners(4);
    perspectiveTransform( obj_corners, obj_transformed_corners, H);

	for(int i = 0; i< 4; i++)
	{
      (scene_corners->at(i)).x = obj_transformed_corners[i].x;
	  (scene_corners->at(i)).y = obj_transformed_corners[i].y;
	}

	float center_x,center_y;
	for(unsigned int i = 0; i< 4; ++i)
	{
	  center_x += (scene_corners->at(i)).x;
	  center_y += (scene_corners->at(i)).y;
	}
	center_x = center_x / 4.0;
    center_y = center_y / 4.0;
	
    position->SetImagePosition(center_x, center_y, sceneMat.cols, sceneMat.rows);	

	_Logging->Log("Detected position X: ", position->GetNormalizedX());
	_Logging->Log("Detected position Y: ", position->GetNormalizedY());

    position->Detected = true;
}
