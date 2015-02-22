#ifndef SNAPSHOTCOMMAND_H
#define	SNAPSHOTCOMMAND_H

#include <RobotCamera.h>
#include <Command.h>
#include <LineDetectSetting.h>
#include <Setting.h>

class SnapshotCommand : public Command , public Setting {
public:
    SnapshotCommand(RobotCamera* robotCamera, LineDetectSetting* bottomDetectSetting, LineDetectSetting* topDetectSetting, LineDetectSetting* leftDetectSetting, LineDetectSetting* rightDetectSetting);
    std::string Execute(vector<int> data);

private:
    RobotCamera* _RobotCamera;
    LineDetectSetting* _BottomDetectSetting;
    LineDetectSetting* _TopDetectSetting;
    LineDetectSetting* _LeftDetectSetting;
    LineDetectSetting* _RightDetectSetting;
	bool _DisplayLineSearch;
	int _RobotCameraMode;
	
	void SavePicture(std::string filename, cv::Mat frame);
    void IndicateSearchArea(cv::Mat frame, cv::Rect region);
};

#endif	/* SNAPSHOTCOMMAND_H */