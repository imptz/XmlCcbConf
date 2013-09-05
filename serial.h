#ifndef SERIAL_H
#define SERIAL_H

#include <windows.h>

class Serial{
private:
	static HANDLE hCom;
	static const unsigned int BUFFER_SIZE = 1024 * 1024 * 64;
	static unsigned char* buffer;

public:
	static bool serialConnect(const char* serialName, unsigned int year, unsigned int version);
	static void serialDisconnect();
	static unsigned int recv();
	static void send(unsigned int size);
};

#endif


