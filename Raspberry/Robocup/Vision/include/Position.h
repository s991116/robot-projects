#ifndef POSITION_H
#define	POSITION_H

#include <string>

class Position {
public:
  bool Detected;
  
void SetImagePosition(int imageX, int imageY, int width, int height);
void SetNormalizedPosition(float x, float y, int width, int height);

int GetImageX();
int GetImageY();

int GetLimitedImageX();
int GetLimitedImageY();

float GetNormalizedX();
float GetNormalizedY();

int GetHeight();
void SetHeight(int height);
int GetWidth();
void SetWidth(int width);
bool WithinImage();

std::string Print(void);

private:
  int LimitPoint(int value, int maxValue);
  float _X;
  float _Y;  
  int _Width;
  int _Height;
};

#endif	/* POSITION_H */

