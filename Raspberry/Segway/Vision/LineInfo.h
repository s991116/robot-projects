#ifndef LINEINFO_H
#define	LINEINFO_H
#include <string>

class LineInfo {
public:
    
    LineInfo(bool detected, int position, int imageWidth);
	LineInfo(bool detected, int position, int imageWidth, int lineWidth);
	
    void SetPosition(int position);
    int GetPosition();
    float GetNormalizePosition();
    bool LineDetected();
    std::string ToString();
    
	int GetLineWidth();
	
private:
    int Position;
    bool Detected;
    int ImageWidth;
	int LineWidth;

};

#endif	/* LINEINFO_H */

