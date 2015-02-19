#ifndef SNAPSHOTCOMMAND_H
#define	SNAPSHOTCOMMAND_H

#include "CameraDetector.h"
#include "Command.h"
#include "LineDetectSetting.h"
#include "Setting.h"

class SnapshotCommand : public Command , public Setting {
public:
    SnapshotCommand(CameraDetector* cameraDetector, LineDetectSetting* bottomDetectSetting, LineDetectSetting* topDetectSetting, LineDetectSetting* leftDetectSetting, LineDetectSetting* rightDetectSetting);
    std::string Execute(vector<int> data);

private:
    CameraDetector* _CameraDetector;
    LineDetectSetting* _BottomDetectSetting;
    LineDetectSetting* _TopDetectSetting;
    LineDetectSetting* _LeftDetectSetting;
    LineDetectSetting* _RightDetectSetting;
    bool _GrayMode;
	bool _DisplayLineSearch;
};

#endif	/* SNAPSHOTCOMMAND_H */

