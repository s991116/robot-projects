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
  BookSearchResult FindBook();
  void ShowResult(BookSearchResult result);
  void LogResult(BookSearchResult result);
  void LEDResult(BookSearchResult result);
  void SetSearchArea();
  cv::Rect SetSearchArea(std::vector< cv::Point2f > corners);
  void Turn(int angle);
  void MoveToNextPosition(int distance);
  void CenterBook();  
  
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
  int _angleToDistance;
  bool _Book1Finished, _Book2Finished;
  ComController* _ComController;
  LoggingSetting* _LoggingSetting;
};

#endif	/* NAVIGATETOBOOK_H */