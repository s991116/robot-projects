#ifndef NAVIGATETOBOOK_H
#define	NAVIGATETOBOOK_H

#include <RobotCamera.h>
#include <DetectSurfObject.h>
#include <Position.h>
#include <Direction.h>
#include <ComController.h>
#include <Command.h>
#include <Setting.h>
#include <LoggingSetting.h>

enum class BookSearchResult {NoBook, Book1, Book2 }; 

class NavigateToBook : public Command , public Setting {
public:
  NavigateToBook(RobotCamera* robotCamera, ComController* comController, LoggingSetting* loggingSetting);
  std::string Execute(std::vector<int> input);
    
private:
  void SetNavigation(Position* pos);
  DetectSurfObject* CreateDetectObject(std::string templateName);
  DetectSurfObject* CreateDetectObject(cv::Mat templateImage);
  BookSearchResult FindBook();
  void ShowResult(BookSearchResult result);
  void LogResult(BookSearchResult result);
  void LEDResult(BookSearchResult result);
  void SetSearchArea();
  cv::Rect SetSearchArea(std::vector< cv::Point2f > corners);
  void MoveToNextPosition(int distance);
  void CenterBook(); 
  void UpdateBookPosition();
  cv::Mat CreateBookTemplate(Position* position1_ROI, Position* position2_ROI, cv::Mat image);
  
  RobotCamera* _RobotCamera;
  DetectSurfObject* _DetectBook1;
  DetectSurfObject* _DetectBook2;
  DetectSurfObject* _NavigateBook1;
  DetectSurfObject* _NavigateBook2;
  
  cv::Mat _image;
  std::vector< cv::Point2f > _Scene_corners;
  Position* _Position;
  Position* _Position1_ROI;
  Position* _Position2_ROI;
  
  Direction* _Direction;
  int _NoBookDistance;
  float _MinDetectPosition;
  int _MoveBookDistanceFactor;
  float _MoveBookDistanceOffset;
  float _MoveBookDistanceMinError;
  int _MoveAfterBook;
  
  bool _Book1Finished, _Book2Finished;
  ComController* _ComController;
  LoggingSetting* _LoggingSetting;
};

#endif	/* NAVIGATETOBOOK_H */