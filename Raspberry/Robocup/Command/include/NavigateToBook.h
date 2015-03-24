#ifndef NAVIGATETOBOOK_H
#define	NAVIGATETOBOOK_H

#include <RobotCamera.h>
#include <DetectObject.h>
#include <ObjectPosition.h>
#include <Position.h>
#include <Direction.h>
#include <ComController.h>
#include <Command.h>
#include <Setting.h>
#include <Logging.h>
#include <ObjectDetect.h>
#include <FollowLineDistance.h>

enum class BookSearchResult {NoBook, Book1, Book2 }; 

class NavigateToBook : public Command , public Setting {
public:
  NavigateToBook(RobotCamera* robotCamera, ComController* comController, FollowLineDistance* followLineDistance, Logging* logging);

  std::string Execute(std::vector<int> input);
    
private:
  void SetNavigation(Position* pos);
  ObjectPosition* FindBook();
  void SetSearchArea();
  cv::Rect SetSearchArea(std::vector< cv::Point2f > corners);
  void MoveToNextPosition(int distance);
  void CenterBook(int pointX1, int pointX2); 
  void UpdateBookPosition(int pointX1, int pointX2);
  cv::Mat CreateBookTemplate(ObjectPosition* position, cv::Mat image);
  
  RobotCamera* _RobotCamera;
  ObjectDetect* _DetectBook1;
  ObjectDetect* _DetectBook2;
  ObjectDetect* _NavigateBook;
  ObjectPosition* _ObjectPosition;
  
  cv::Mat _image;
  
  Direction* _Direction;
  int _NoBookDistance;
  float _MinDetectPosition;
  int _MoveBookDistanceFactor;
  float _MoveBookDistanceOffset;
  float _MoveBookDistanceMinError;
  int _MoveAfterBook;
  FollowLineDistance* _FollowLineDistance;
  
  bool _Book1Finished, _Book2Finished;
  ComController* _ComController;
  Logging* _Logging;
};

#endif	/* NAVIGATETOBOOK_H */