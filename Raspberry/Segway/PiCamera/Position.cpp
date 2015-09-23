#include "Position.h"

Position::Position(float x, float y) {
    _X = x;
    _Y = y;
}

void Position::SetNormailzePosition(float x, float y) {
    _X = x;
    _Y = y;
}

void Position::SetPosition(float x, float y, short width, short height) {
    _X = ((x))/(float)(width) * 2 - 1;
    _Y = ((y))/(float)(height) * 2 - 1;
}

void Position::SetCenterPosition(){
    _X = 0;
    _Y = 0;
}

float Position::GetX()
{
    return _X;
}

float Position::GetY()
{
    return _Y;
}

Position::~Position() {
}

