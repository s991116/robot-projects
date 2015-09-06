#ifndef POSITION_H
#define	POSITION_H

class Position {
public:
    Position(float x, float y);
    void SetPosition(float x, float y);
    
    float GetX();
    float GetY();

    virtual ~Position();

private:
    float _X;
    float _Y;
};

#endif	/* POSITION_H */

