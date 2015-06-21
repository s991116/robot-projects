#include <iostream>
#include "PiCamera.h"
#include "ComPort.h"
#include "HardwareController.h"
#include "SoundPlayer.h"
#include "Sounds.h"
#include "View.h"
#include "Controller.h"

using namespace std;

int main(int argc, char *argv[])
{
	PiCamera* pc = new PiCamera();
	ComPort* comPort = new ComPort();
	HardwareController* hardwareController = new HardwareController(comPort);
	View* view = new View();
	Controller* controller = new Controller(view);
	view->_Controller = controller;

	int cmd, data;

	while (cmd != -1)
	{
		std::cout << "Enter cmd and data ";
		std::cin >> cmd >> data;

		if (cmd == 0)
		{
			SoundPlayer::Play(Sounds::Test);
		}

		if (cmd != -1)
		{
			std::cout << "cmd: " << cmd << " data: " << data << std::endl;
			int result = hardwareController->SendCommand(static_cast<CommandType>(cmd), data);
			std::cout << "return: " << result << std::endl;
		}
	}
}