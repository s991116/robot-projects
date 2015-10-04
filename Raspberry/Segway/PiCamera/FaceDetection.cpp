#include "FaceDetection.h"
#include <stdio.h>

FaceDetection::FaceDetection() {
    std::string face_cascade_name = "haarcascade_frontalface_alt2.xml";
    if(!face_cascade.load( face_cascade_name ))
    {
        std::cout << "FaceDetection initilazation error" << std::endl;
    }
}

bool FaceDetection::GetFacePosition(cv::Mat frame_gray, Position* position) {
  std::vector<cv::Rect> faces;
  
  cv::equalizeHist( frame_gray, frame_gray );

  //-- Detect faces
  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(30, 30) );


  if(faces.size()>0)
  {
      cv::Point center( faces[0].x + faces[0].width*0.5, faces[0].y + faces[0].height*0.5 );
      float x = ((float)(center.x))/(float)(frame_gray.cols) * 2 - 1;
      float y = ((float)(center.y))/(float)(frame_gray.rows) * 2 - 1;
      position->SetPosition(x, y);
      return true;
  }
  else
  {
      position->SetPosition(0,0);
      return false;
  }
}


FaceDetection::~FaceDetection() {
}

