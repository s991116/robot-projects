#include <Position.h>
#include <Convert.h>

void Position::SetImagePosition(int imageX, int imageY, int width, int height) {
  	_Width = width;
	_Height = height;
	this->_X = ((2.0 * imageX) / _Width) - 1.0;
	this->_Y = 1.0 - ((2.0 * imageY) / _Height);
}

void Position::SetNormalizedPosition(float x, float y, int width, int height) {
  	_Width = width;
	_Height = height;

  	this->_X = x;
	this->_Y = y;
}

int Position::GetImageX() {
  return _Width * ((_X+1.0)/2.0);
}

int Position::GetImageY() {
  return _Height * ((-_Y+1.0)/2.0);
}

int Position::GetLimitedImageX() {
  int x = GetImageX();
  return LimitPoint(x, _Width);
}

int Position::GetLimitedImageY() {
	int y = GetImageY();
	return LimitPoint(y,_Height);
}

int Position::LimitPoint(int value, int maxValue) {
  if(value < 0)
  {
    return 0;
  }
  else if(value > maxValue)
  {  
    return maxValue-1;
  }
  return value;
}

float Position::GetNormalizedX() {
  return _X;
}

float Position::GetNormalizedY() {
  return _Y;
}

int Position::GetHeight() {
  return _Height;
}

void Position::SetHeight(int height) {
  _Height = height;
}

int Position::GetWidth() {
  return _Width;
}

void Position::SetWidth(int width) {
  _Width = width;
}

bool Position::WithinImage() {
  return (_X >= -1.0 && _X <= 1.0 && _Y >= -1.0 && _Y <= 1.0);
}

std::string Position::Print() {
  return "(" + Convert::FloatToString(_X) + " ; " + Convert::FloatToString(_Y) + ")";
}