#include "Direction.h"

Direction::Direction(int direction, int rotation, int speed)
{
    this->_Direction = direction;
    this->_Rotation = rotation;
    this->_Speed = speed;
}

void Direction::SetDirectionNorm(float direction) {
  this->_Direction = direction*100;
}

void Direction::SetDirection(int direction)
{
    this->_Direction = direction;
}

int Direction::GetDirection()
{
    return this->_Direction;
}

void Direction::SetRotation(int rotation)
{
    this->_Rotation = rotation;
}

int Direction::GetRotation()
{
    return this->_Rotation;
}

void Direction::SetSpeed(int speed)
{
    this->_Speed = speed;
}

int Direction::GetSpeed()
{
    return this->_Speed;
}