#include <Direction.h>
#include <Convert.h>

#define MAX_DIRECITON (100)
#define MIN_DIRECITON (-100)

Direction::Direction(int direction, int rotation, int speed)
{
    this->_Direction = direction;
    LimitDirection();
	this->_Rotation = rotation;
    this->_Speed = speed;
}

void Direction::SetDirectionNorm(float direction) {
  this->_Direction = direction*100;
  LimitDirection();
}

void Direction::SetDirection(int direction)
{
    this->_Direction = direction;
	LimitDirection();
}

void Direction::LimitDirection()
{
  if(this->_Direction > MAX_DIRECITON)
	  this->_Direction = MAX_DIRECITON;
  else if(this->_Direction < MIN_DIRECITON)
	  this->_Direction = MIN_DIRECITON;
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

std::string Direction::Print()
{
  return "Dir: " + Convert::IntToString(_Direction) + " - Rot: " + Convert::IntToString(_Rotation) + " - Speed: " + Convert::IntToString(_Speed);	
}
