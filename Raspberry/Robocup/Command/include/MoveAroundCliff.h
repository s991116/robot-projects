#include <Command.h>
#include <Setting.h>
#include <CameraNavigation.h>
#include <ComController.h>
#include <Logging.h>
#include <Direction.h>

class MoveAroundCliff : public Command , public Setting
{
public:
    MoveAroundCliff(ComController* comController, CameraNavigation* cameraNavigation, Logging* logging);
	std::string Execute(vector<int> data);
	
private:
    int MeasureDistance();
	void UpdateDirection(bool toClose);
    void SetDirection(int dir, int speed);
	
	CameraNavigation* _CameraNavigation;
	ComController* _ComController;
	Logging* _Logging;
	Direction* _Direction;
    bool _CurrentState;
	int _CircleDistance;
	int _CliffDetect;
	int _NormalDirection;
	int _NormalSpeed;
	int _CliffDirection;
	int _CliffSpeed;
    int _MaxErrorDistance;
};