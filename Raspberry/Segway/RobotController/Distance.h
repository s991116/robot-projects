#ifndef DISTANCE_H
#define	DISTANCE_H

#include "SerialProtocol.h"

class Distance {
public:
    Distance(SerialCommandProtocol* serialProtocol);
    
    int GetDistance();
    
    void ResetDistance();
    
    virtual ~Distance();
private:
    SerialCommandProtocol* _SerialProtocol;

};

#endif	/* DISTANCE_H */

