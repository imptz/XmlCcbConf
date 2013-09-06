#include "stdafx.h"

#include <windows.h>
#include <stdio.h>
#include <iostream>

#include "cmd.h"
#include "config.h"
#include "xmlExceptions.h"
#include "serial.h"

using namespace std;

int main(int argc, char* argv[])
{
	try{
		Cmd::init(argc, argv);

		if (Cmd::isParameterExists(Cmd::CMD_CONFIG_FILE))
			Config::init(Cmd::getParameterValue(Cmd::CMD_CONFIG_FILE).c_str());
		else{
			std::cout << "ERROR: Not specified the name of the configuration file. Exit." << std::endl;
			return 0;
		}
	}
	catch(ExceptionXml& e){
		cout << "ExceptionConfig what = " << e.what() << " stingNumber = " << e.getStringNumber() << " columnNumber = " << e.getColumnNumber() << endl;
		return 0;
	}
	
	XmlElement* configElement = Config::getElement("config");
	if (configElement == nullptr){
		std::cout << "kornevoy element 'config' ne nayden" << std::endl;
		return 0;
	}

	if (Cmd::isParameterExists(Cmd::CMD_PRINT_CONFIG)){
		configElement->print();
		return 1;
	}

	XmlElement* comPortElement = Config::getElement("com_port");
	if (comPortElement == nullptr){
		std::cout << "imya com porta ne ukazano" << std::endl;
		return 0;
	}

	std::string comPortName;
	if (comPortElement->isAttributeExists("name"))
		comPortName = comPortElement->getAttributeValue("name");
	else{
		std::cout << "imya com porta ne ukazano" << std::endl;
		return 0;
	}
	
	if (!Serial::serialConnect(comPortName.c_str(), atoi(configElement->getAttributeValue("year").c_str()), atoi(configElement->getAttributeValue("version").c_str()))){
		std::cout << "Error: soedinenie ne ustanovleno" << std::endl;
		return 0;
	}



	return 1;
}
