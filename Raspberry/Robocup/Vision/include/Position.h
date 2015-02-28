#ifndef POSITION_H
#define	POSITION_H

class Position {
public:
    float X;
    float Y;
    bool Detected;
    
	void SetNormalizedPosition(int imageX, int imageY, int width, int height);
	
	int GetImagePositionX(int width);
	int GetImagePositionY(int height);
	
private:

};

#endif	/* POSITION_H */

