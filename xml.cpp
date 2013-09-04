#include "xml.h"

char* XmlParser::source = nullptr;
char* XmlParser::sourceEnd = nullptr;
unsigned int XmlParser::columnNumber = 0;
unsigned int XmlParser::stringNumber = 0;
unsigned int XmlParser::prevColumnNumber = 0;
unsigned int XmlParser::prevStringNumber = 0;
XmlElement* XmlParser::element = nullptr;
vector<XmlElement*> XmlParser::elements;
stack<XmlElement*> XmlParser::elementsStack;
void (*XmlParser::stateFunc)();