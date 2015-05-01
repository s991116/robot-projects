#include <iostream>
#include "PiCamera.h"
#include "ComPort.h"
#include "Controller.h"

using namespace std;

int main(int argc, char *argv[])
{
	PiCamera* pc = new PiCamera();
	cv::Mat image = pc->GetNextFrame();
	cv::imwrite("snapshot.jpg", image);

	ComPort* comPort = new ComPort();
	Controller* controller = new Controller(comPort);

	short resultat = controller->SendCommand(CommandType::TestEcho, 1222);

}