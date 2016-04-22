#include "DetectFace.h"

DetectFace::DetectFace() {
   std::string face_cascade_name = "lbpcascade_frontalface.xml";//haarcascade_frontalface_alt2.xml";
    if(!face_cascade.load( face_cascade_name ))
    {
        std::string error = "FaceDetection initilazation error";
        throw error;
    }
}

DetectFace::~DetectFace() {
}

void DetectFace::GetFacePosition(cv::Mat frame_gray, Position* position) {
 std::vector<cv::Rect> faces;
  //cv::equalizeHist( frame_gray, frame_gray );

  //-- Detect faces
//  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(30, 30) );
//  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 3, CV_HAAR_SCALE_IMAGE, cv::Size(80,80));

  cv::equalizeHist(frame_gray, frame_gray);

  // Detect faces
  face_cascade.detectMultiScale(frame_gray, faces, 1.4, 3, 0|CV_HAAR_SCALE_IMAGE, cv::Size(50, 50));

  if(faces.size()>0)
  {
      cv::Point center( faces[0].x + faces[0].width*0.5, faces[0].y + faces[0].height*0.5 );
      position->SetImagePosition(center.x, center.y, frame_gray.cols, frame_gray.rows);
  }
  else
  {
      position->NotDetected();
  }
}