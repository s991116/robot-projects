#ifndef LINEPOSITION_H
#define	LINEPOSITION_H

class LinePosition {
public:
    enum SearchStatusEnum{
        NoLine,
        Cros,
        Middle,
        CrosLeft,
        CrosRight        
    };
    
    SearchStatusEnum LineDetected;
    float Left;
    float Right;
    float Top;

    
private:

};

#endif	/* LINEPOSITION_H */

