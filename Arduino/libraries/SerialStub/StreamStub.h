#ifndef StreamStub_H
#define StreamStub_H
#include <Stream.h>

class StreamStub : public Stream
{
	public:
		StreamStub();
		
		size_t write(uint8_t);
		                    
		int available(void);
		                 
		int read(void);
		                 
		int peek(void);
		                 
		void flush(void);
		
		void reset();
		
		int peek(int i);
		
		int bytesWritten();
		                 
		operator bool(){
		  return true;
		}
			
		void begin(unsigned long) {
		}
			
		void end() {
		}
			
	private:
		uint8_t _memory[100];
		int _count;
		int _nextRead;
		int _nextWrite;
		int _available;
};

#endif