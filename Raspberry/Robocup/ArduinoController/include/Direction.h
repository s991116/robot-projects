#ifndef DIRECTION_H
#define	DIRECTION_H

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

private:
    int _Direction;
    int _Rotation;
    int _Speed;
};

#endif	/* DIRECTION_H */