#ifndef CONFIG_H
#define CONFIG_H

#include <fstream>
#include "xml.h"

using namespace std;

class Config{
private:
	static ifstream configFile;
	static char* configData;
	static char* configDataEnd;
	static vector<XmlElement*>* elements;

public:
	static void init(const char* fileName){
		clear();
		readConfigFile(fileName);
		XmlParser::parseXml(configData, configDataEnd);
		elements = XmlParser::getElements();
	}

	static void clear(){
		if (configData != nullptr){
			delete[] configData;
		}
	}

	static XmlElement* getElement(unsigned int index){
		if (index >= elements->size())
			return nullptr;

		return (*elements)[index];
	}

	static XmlElement* getElement(const string& _name){
		int index = getElementIndex(_name);
		if ((index >= elements->size()) || index == -1)
			return nullptr;

		return (*elements)[index];
	}

	static int getElementIndex(const string& _name){
		int index = 0;
		for (;index < elements->size(); ++index)
			if ((*elements)[index]->getName() == _name)
				return index;

		return -1;
	}

private:
	static unsigned int getConfigFileSize(){
		configFile.seekg(0, ios::beg);
		long begin = configFile.tellg();
		configFile.seekg(0, ios::end);
		return (static_cast<long>(configFile.tellg()) - begin);
	}

	static void readConfigFile(const char* fileName){
		configFile.open(fileName, ifstream::in);
		if (configFile.is_open()){
			if (configData != nullptr)
				delete[] configData;

			const unsigned int CONFIG_DATA_SIZE = getConfigFileSize();
			configData = new char[CONFIG_DATA_SIZE];
			configDataEnd = configData + CONFIG_DATA_SIZE;

			configFile.seekg(0, ios::beg);

			configFile.read(configData, CONFIG_DATA_SIZE);

			configFile.close();
		}
	}
};

#endif

