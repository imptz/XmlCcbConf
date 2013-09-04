#include "config.h"

ifstream Config::configFile;
char* Config::configData = nullptr;
char* Config::configDataEnd = nullptr;
vector<XmlElement*>* Config::elements;
