#include "serial.h"
#include "config.h"
#include <iostream>

using namespace std;

HANDLE Serial::hCom = nullptr;
unsigned char* Serial::buffer = nullptr;

bool Serial::serialConnect(const char* serialName, unsigned int year, unsigned int version){
	if (buffer != nullptr)
		delete[] buffer;

	buffer = new unsigned char[BUFFER_SIZE];

	hCom = CreateFileA(serialName, 
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	if (hCom == INVALID_HANDLE_VALUE)  
	{
		cout << "ERROR: opening com port: " << GetLastError() << endl;
		return false;
	}

	DCB dcb;
	BOOL fSuccess = GetCommState(hCom, &dcb);

	if (!fSuccess) 
	{
		cout << "ERROR: GetCommState: " << GetLastError() << endl;
		CloseHandle(hCom);
		return false;
	}

	dcb.BaudRate = CBR_57600;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;

	fSuccess = SetCommState(hCom, &dcb);

	COMMTIMEOUTS ct;

	ct.ReadIntervalTimeout = 1;
	ct.ReadTotalTimeoutConstant = 0;
	ct.ReadTotalTimeoutMultiplier = 0;
	ct.WriteTotalTimeoutConstant = 0;
	ct.WriteTotalTimeoutMultiplier = 0;

	SetCommTimeouts(hCom,&ct);
	if (!fSuccess) 
	{
		cout << "ERROR: SetCommState: " << GetLastError() << endl;
		CloseHandle(hCom);
		return false;
	}

	DWORD nWrite = 0;
	buffer[0] = version;
	buffer[1] = version >> 8;
	buffer[2] = year;
	buffer[3] = year >> 8;
	if (WriteFile(hCom, buffer, 4, &nWrite, NULL)){
		if (ReadFile(hCom, &buffer[0], 8, &nWrite, NULL)){
			if (*reinterpret_cast<unsigned int*>(&buffer[0]) == 0x45dc69a3)
				return true;

			//cout << "Connection: recv bytes - " << nWrite << " : ";
			//for (unsigned int i = 0; i < nWrite; ++i)
			//	cout << static_cast<unsigned int>(buffer[i]) << " ";

			//cout << endl;
		}
	}

	CloseHandle(hCom);
	return false;
}

void Serial::serialDisconnect(){
	CloseHandle(hCom);
}


unsigned int Serial::recv(){
	unsigned int pos = 0;
	DWORD nWrite = 0;

	while (pos < 5)
	{
		if (ReadFile(hCom, &buffer[pos], 1, &nWrite, NULL))
			pos += nWrite;
	}
		
	unsigned int length = buffer[4] * 256 + buffer[3];
		
	while (pos < length + 7)
	{
		if (ReadFile(hCom, &buffer[pos], 1, &nWrite, NULL))
			pos += nWrite;
	}

	//if (Debug::BUS_IN_DEBUG_OUT){
	//	if ((Debug::BUS_DEVICE_NUMBER == -1) || (buffer[0] == pUsoDeviceManager->devices[Debug::BUS_DEVICE_NUMBER]->getAddress())){
	//		char str[800];
	//		std::cout << "recv: ";
	//		for (int i = 0; i < length + 7; i++)
	//			std::cout << _itoa(buffer[i], str, 16) << " ";
	//		std::cout << std::endl;
	//	}
	//}

	return 0;
}

void Serial::send(unsigned char* pBuffer, unsigned int size){
	DWORD nWrite = 0;
	WriteFile(hCom, pBuffer, size, &nWrite, NULL);
}