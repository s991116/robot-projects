#ifndef SNAPSHOTCOMMAND_H
#define	SNAPSHOTCOMMAND_H

#include <PiCamera.h>
#include <Command.h>
#include <LineDetectSetting.h>
#include <Setting.h>

class SnapshotCommand : public Command , public Setting {
public:
    SnapshotCommand(PiCamera* piCamera, LineDetectSetting* bottomDetectSetting, LineDetectSetting* topDetectSetting, LineDetectSetting* leftDetectSetting, LineDetectSetting* rightDetectSetting);
    std::string Execute(vector<int> data);

private:
    PiCamera* _PiCamera;
    LineDetectSetting* _BottomDetectSetting;
    LineDetectSetting* _TopDetectSetting;
    LineDetectSetting* _LeftDetectSetting;
    LineDetectSetting* _RightDetectSetting;
    bool _GrayMode;
	bool _DisplayLineSearch;
};

#endif	/* SNAPSHOTCOMMAND_H */