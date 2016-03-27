#ifndef COMSTREAM_H
#define	COMSTREAM_H

#include "ComPort.h"

class ComStream {
public:
    ComStream(ComPort* comPort);
    virtual ~ComStream();
    
    bool available();
    int read();
    void write(int data);
private:
    ComPort* _ComPort;
    int _DataRead;
    bool _DataAvailable;

};

#endif	/* COMSTREAM_H */

