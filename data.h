#ifndef DATA_H
#define DATA_H

#include "config.h"
#include "xmlExceptions.h"
#include "serial.h"

struct ConfigDataStructConst
{
	unsigned char maxPR;
	unsigned char timeOutBeforeStart;
	unsigned char timeOutBeforeFinish;
	unsigned char numberFireToAnalize;
	unsigned char minimumDistanceForCompactJet;
	unsigned char permissionTesting;
	unsigned char testingHour;
	unsigned char testingMinute;
	unsigned char permissionTestingInfo;
	unsigned char timeControlUserAction;
	unsigned short zoneX;
	unsigned short zoneY;
	unsigned short zoneZ;
	unsigned short tvAdapter;
	unsigned short pcAdapter;
	unsigned char topField;
	unsigned char bottomField;
	unsigned char leftField;
	unsigned char rightField;
	unsigned char timeReturnFromRemoteMode;
	unsigned char permissionRemoteWithSearch;
}

class Data{
private:


public:
	bool init();
	bool send();
};

#endif