#include "ComPort.h"
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#include <termios.h>
#include <iostream>		        //Used for UART

ComPort::ComPort() {
        //-------------------------
    //----- SETUP USART 0 -----
    //-------------------------
    //At bootup, pins 8 and 10 are already set to UART0_TXD, UART0_RXD (ie the alt0 function) respectively
    ComPort::uart0_filestream = -1;
    
    uart0_filestream = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY); //Open in non blocking read/write mode
    
    if (uart0_filestream == -1) {
        std::cout << "Error: Cannot open Serial port";
        return;
    }

    //CONFIGURE THE UART
    //The flags (defined in /usr/include/termios.h - see http://pubs.opengroup.org/onlinepubs/007908799/xsh/termios.h.html):
    //	Baud rate:- B1200, B2400, B4800, B9600, B19200, B38400, B57600, B115200, B230400, B460800, B500000, B576000, B921600, B1000000, B1152000, B1500000, B2000000, B2500000, B3000000, B3500000, B4000000
    //	CSIZE:- CS5, CS6, CS7, CS8
    //	CLOCAL - Ignore modem status lines
    //	CREAD - Enable receiver
    //	IGNPAR = Ignore characters with parity errors
    //	ICRNL - Map CR to NL on input
    //	PARENB - Parity enable
    //	PARODD - Odd parity (else even)
    struct termios options;
    tcgetattr(uart0_filestream, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD; //<Set baud rate
    options.c_iflag = IGNPAR | ICRNL;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart0_filestream, TCIFLUSH);
    tcsetattr(uart0_filestream, TCSANOW, &options);
}


ComPort::~ComPort() {
    close(uart0_filestream);
}

int ComPort::ReceiveChar(unsigned char* rx_buffer_ptr) {
   //----- CHECK FOR ANY RX BYTES -----
    if (ComPort::uart0_filestream != -1) {
        // Read up to 255 characters from the port if they are there

        int rx_length = read(uart0_filestream, (void*) rx_buffer_ptr, 1); //Filestream, buffer to store in, number of bytes to read (max)
        if (rx_length < 0) {
            return -1; //An error occured (will occur if there are no bytes)
        } else if (rx_length == 0) {
            return 0; //No data waiting
        } else {
            return rx_length; //Bytes received
        }
    }
}

int ComPort::Send(char* command) {
    //Transmitting Bytes
    //----- TX BYTES -----

    if (uart0_filestream != -1) {
        int count = write(uart0_filestream, command, 3); //Filestream, bytes to write, number of bytes to write
        return count;
    }
    return 0;
}