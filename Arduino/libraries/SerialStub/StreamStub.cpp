#ifndef StreamStub_CPP
#define StreamStub_CPP

#include "StreamStub.h"

StreamStub::StreamStub()
{
	reset();
}

size_t StreamStub::write(uint8_t data)
{
	_memory[_nextWrite] = data;
	_available++;
	_nextWrite++;
	_count++;
}

                    
int StreamStub::available(void)
{
	return _available;
}
						                 
int StreamStub::read(void)
{
	int data = -1;
	if(_available > 0)
	{
		data = _memory[_nextRead];
		_nextRead++;
		_available--;
	}
	return data;
}
                 
int StreamStub::peek(void)
{
	int data = -1;
	if(_available > 0)
	{
		data = _memory[_nextRead];
	}
	return data;
}

int StreamStub::bytesWritten(void)
{
	return _count;	
}   
	              
void StreamStub::flush(void)
{
	return;
}

void StreamStub::reset(void)
{
	_available = 0;
	_nextRead = 0;
	_nextWrite = 0;
	_count = 0;
}

int StreamStub::peek(int i)
{
	if(i <= _available && i > 0)
	{
		return _memory[_nextRead + i - 1];
	}
	return -1;
}

#endif