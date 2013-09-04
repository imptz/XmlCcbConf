#include "stdafx.h"

#include <windows.h>
#include <stdio.h>
#include <iostream>

#include "cmd.h"
#include "config.h"
#include "xmlExceptions.h"

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
	
	XmlElement* xmlElement = Config::getElement("conf");
	if (xmlElement == nullptr){
		std::cout << "imya com porta ne ukazano" << std::endl;
		return 0;
	}

	xmlElement->print();


	std::string comPortName;
	if (xmlElement->isAttributeExists("name"))
		comPortName = xmlElement->getAttributeValue("name");
	else{
		std::cout << "imya com porta ne ukazano" << std::endl;
		return 0;
	}
	
	return true;
}
