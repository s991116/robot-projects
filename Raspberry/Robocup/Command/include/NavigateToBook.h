#ifndef NAVIGATETOBOOK_H
#define	NAVIGATETOBOOK_H

#include <RobotCamera.h>
#include <DetectObject.h>
#include <ObjectPosition.h>
#include <Position.h>
#include <Direction.h>
#include <Command.h>
#include <Setting.h>
#include <Logging.h>
#include <ObjectDetect.h>
#include <FollowLineDistance.h>
#include <MoveDistance.h>
#include <NavigateToObject.h>

enum class BookSearchResult {NoBook, Book1, Book2 }; 

class NavigateToBook : public Command, public NavigateToObject {
public:
  NavigateToBook(RobotCamera* robotCamera, FollowLineDistance* followLineDistance, MoveDistance* moveDistance, ObjectDetect* detectBook1, ObjectDetect* detectBook2, Logging* logging);

  std::string Execute(std::vector<int> input);
    
private:
  void SetNavigation(Position* pos);
  void SetSearchArea();
  cv::Rect SetSearchArea(std::vector< cv::Point2f > corners);
  void MoveToNextPosition(int distance);

  RobotCamera* _RobotCamera;
  ObjectDetect* _DetectBook1;
  ObjectDetect* _DetectBook2;
  ObjectDetect* _NavigateBook;
  ObjectPosition* _ObjectPosition;

  cv::Mat _image;

  Direction* _Direction;
  int _NoBookDistance;
  int _MoveAfterBook;
  FollowLineDistance* _FollowLineDistance;

  bool _Book1Finished, _Book2Finished;
  MoveDistance* _MoveDistance;
  Logging* _Logging;
};

#endif	/* NAVIGATETOBOOK_H */