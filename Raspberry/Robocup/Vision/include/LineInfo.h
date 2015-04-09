#ifndef LINEINFO_H
#define	LINEINFO_H
#include <string>

class LineInfo {
public:
    
    LineInfo(bool detected, int position, int imageWidth);
    void SetPosition(int position);
    int GetPosition();
    float GetNormalizePosition();
    bool LineDetected();
    std::string ToString();
    
private:
    int Position;
    bool Detected;
    int ImageWidth;

};

#endif	/* LINEINFO_H */

