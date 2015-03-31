#ifndef DIRECTION_H
#define	DIRECTION_H

#include <string>

class Direction {
public:
    Direction(int direction, int rotation, int speed);
    void SetDirection(int);
    void SetDirectionNorm(float);
    int GetDirection(void);
    void SetRotation(int);
    int GetRotation(void);
    void SetSpeed(int);
    int GetSpeed(void);
	std::string Print(void);

private:
    int _Direction;
    int _Rotation;
    int _Speed;
};

#endif	/* DIRECTION_H */