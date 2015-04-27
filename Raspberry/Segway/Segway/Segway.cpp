#include <iostream>
#include "PiCamera.h"
using namespace std;

int main(int argc, char *argv[])
{
	PiCamera* pc = new PiCamera();
	cv::Mat image = pc->GetNextFrame();
	cv::imwrite("snapshot.jpg", image);
}