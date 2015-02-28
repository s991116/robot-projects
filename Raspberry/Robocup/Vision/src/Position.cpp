#include <Position.h>

void Position::SetNormalizedPosition(int imageX, int imageY, int width, int height) {
  	this->X = ((2.0 * imageX) / width) - 1.0;
	this->Y = 1.0 - ((2.0 * imageY) / height);
}

int Position::GetImagePositionX(int width) {
  return width * ((this->X+1.0)/2.0);
}

int Position::GetImagePositionY(int height) {
  return height * ((-this->Y+1.0)/2.0);
}