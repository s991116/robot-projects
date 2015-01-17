#ifndef COMPORT_H
#define	COMPORT_H

class ComPort {
public:
    ComPort();
    virtual ~ComPort();
    
    int Send(char* command);
    int ReceiveChar(unsigned char* rx_buffer_ptr);
private:
        int uart0_filestream;
};

#endif	/* COMPORT_H */

