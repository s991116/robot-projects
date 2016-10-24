#ifndef DISTANCE_H
#define	DISTANCE_H

#include "MessageDataProtocol.h"

class Distance {
public:
    Distance(MessageDataProtocol* serialProtocol);
    
    int GetDistance();
    
    void ResetDistance();
    
    virtual ~Distance();
private:
    MessageDataProtocol* _SerialProtocol;

};

#endif	/* DISTANCE_H */

