#ifndef POSITION_H
#define	POSITION_H

class Position {
public:
  bool Detected;
  
void SetImagePosition(int imageX, int imageY, int width, int height);
void SetNormalizedPosition(float x, float y, int width, int height);

int GetImageX();
int GetImageY();

float GetNormalizedX();
float GetNormalizedY();

int GetHeight();
void SetHeight(int height);
int GetWidth();
void SetWidth(int width);

private:
  float _X;
  float _Y;  
  int _Width;
  int _Height;
};

#endif	/* POSITION_H */

