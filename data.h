#ifndef DATA_H
#define DATA_H

#include "config.h"
#include "xmlExceptions.h"
#include "serial.h"
#include <string>

class Data{
private:
	static unsigned char* pBuffer;
	static XmlElement* configElement;
	static unsigned int dataSize;
	static unsigned int blockCount;

	static bool getDataSize(){
		for (unsigned int i = 0; i < blockCount; ++i){
			XmlElement* blockElem = configElement->getElement(i);
			dataSize += 6;
			for (unsigned int j = 0; j < blockElem->getElementCount(); ++j){
				XmlElement* elem = blockElem->getElement(j);
				if (elem->isAttributeExists("sizeOfByte"))
					dataSize += atoi(elem->getAttributeValue("sizeOfByte").c_str());
				else{
					std::cout << "ne zadan atribute 'sizeOfByte' u elementa " << elem->getName() << std::endl;
					return false;
				}
			}
		}

		dataSize += 8;
		std::cout << "dataSize = " << dataSize << std::endl;
		return true;
	}

public:
	static bool init(){
		configElement = Config::getElement("config");
		if (configElement == nullptr){
			std::cout << "element 'config' ne nayden" << std::endl;
			return false;
		}

		blockCount = configElement->getElementCount();
		std::cout << "elementCount = " << blockCount << std::endl;

		if (!getDataSize())
			return false;

		pBuffer = new unsigned char[dataSize];
		memset(pBuffer, 0, dataSize);

		unsigned char* _pBuffer = pBuffer;
		*(reinterpret_cast<unsigned int*>(pBuffer)) = dataSize;
		pBuffer += sizeof(unsigned int);

		for (unsigned int i = 0; i < blockCount; ++i){
			XmlElement* blockElem = configElement->getElement(i);
			*(reinterpret_cast<unsigned short*>(pBuffer)) = atoi(blockElem->getAttributeValue("id").c_str());
			pBuffer += sizeof(unsigned short);

			продолжить


			for (unsigned int j = 0; j < blockElem->getElementCount(); ++j){
				XmlElement* elem = blockElem->getElement(j);
				dataSize += atoi(elem->getAttributeValue("sizeOfByte").c_str());
			}
		}

	}

	static bool send(){

	}
};

unsigned char* Data::pBuffer = nullptr;
XmlElement* Data::configElement = nullptr;
unsigned int Data::dataSize = 0;
unsigned int Data::blockCount = 0;

#endif