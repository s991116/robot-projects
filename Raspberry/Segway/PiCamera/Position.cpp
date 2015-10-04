#include "Position.h"

Position::Position(float x, float y) {
    _X = x;
    _Y = y;
}

void Position::SetPosition(float x, float y) {
    _X = x;
    _Y = y;
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

