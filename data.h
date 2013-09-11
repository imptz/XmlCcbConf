#ifndef DATA_H
#define DATA_H

#include "config.h"
#include "xmlExceptions.h"
#include "serial.h"
#include "crc32.h"
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
				if (elem->isAttributeExists("sizeInBytes"))
					dataSize += atoi(elem->getAttributeValue("sizeInBytes").c_str());
				else{
					std::cout << "ne zadan atribute 'sizeInBytes' u elementa " << elem->getName() << std::endl;
					return false;
				}
			}
		}

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

		pBuffer = new unsigned char[dataSize + 8];
		memset(pBuffer, 0, dataSize + 8);

		unsigned char* _pBuffer = pBuffer;
		*(reinterpret_cast<unsigned int*>(_pBuffer)) = dataSize;
		_pBuffer += sizeof(unsigned int);

		for (unsigned int i = 0; i < blockCount; ++i){
			XmlElement* blockElem = configElement->getElement(i);
			*(reinterpret_cast<unsigned short*>(_pBuffer)) = atoi(blockElem->getAttributeValue("id").c_str());
			_pBuffer += sizeof(unsigned short);
			unsigned char* pBlockSize = _pBuffer;
			_pBuffer += sizeof(unsigned int);
			unsigned int blockSize = 0;

			for (unsigned int j = 0; j < blockElem->getElementCount(); ++j){
				XmlElement* elem = blockElem->getElement(j);
				unsigned int itemSize = atoi(elem->getAttributeValue("sizeInBytes").c_str());
				blockSize += itemSize;

				for (unsigned int k = 0; k < elem->getElementCount(); ++k){
					XmlElement* itemElem = elem->getElement(k);
					unsigned int itemSize = atoi(itemElem->getAttributeValue("sizeInBytes").c_str());
					unsigned int value = atoi(itemElem->getAttributeValue("value").c_str());

					switch (itemSize){
						case 1:
							*reinterpret_cast<unsigned char*>(_pBuffer) = value;
							_pBuffer += 1;
							break;
						case 2:
							*reinterpret_cast<unsigned char*>(_pBuffer) = value;
							_pBuffer += 1;
							*reinterpret_cast<unsigned char*>(_pBuffer) = value >> 8;
							_pBuffer += 1;
							break;
						default:
							std::cout << __FUNCTION__ << " itemSize unknown = " << itemSize << " block = " << blockElem->getName() << " itemIndex = " << k << std::endl;
							return false;
							break;
					}
				}
			}
			*reinterpret_cast<unsigned int*>(pBlockSize) = blockSize;
		}

		unsigned int crc = calcCRC32(pBuffer + 4, dataSize);
		*reinterpret_cast<unsigned int*>((pBuffer + sizeof(unsigned int) + dataSize)) = crc;
		return true;
	}

	static void send(){
		Serial::send(pBuffer, dataSize + 8);
	}
};

unsigned char* Data::pBuffer = nullptr;
XmlElement* Data::configElement = nullptr;
unsigned int Data::dataSize = 0;
unsigned int Data::blockCount = 0;

#endif