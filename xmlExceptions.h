#ifndef XML_EXCEPTIONS_H
#define XML_EXCEPTIONS_H

class ExceptionXml : public std::exception{
protected:
	unsigned int stringNumber;
	unsigned int columnNumber;

public:
	ExceptionXml(unsigned int _stringNumber = 0, unsigned int _columnNumber = 0)	:
		stringNumber(_stringNumber), columnNumber(_columnNumber)
	{}

	virtual const char* what() const throw() = 0;

	unsigned int getStringNumber(){
		return stringNumber;
	}

	unsigned int getColumnNumber(){
		return columnNumber;
	}
};

class ExceptionXml_UnexpectedEndOfInputData : public ExceptionXml{
public:
	ExceptionXml_UnexpectedEndOfInputData(unsigned int _stringNumber = 0, unsigned int _columnNumber = 0)	:
		ExceptionXml(_stringNumber, _columnNumber)
	{}

	virtual const char* what() const throw(){
		return "Unexpected end of input data";
	}
};

class ExceptionXml_ExtraCharactersOutsideElement : public ExceptionXml{
public:
	ExceptionXml_ExtraCharactersOutsideElement(unsigned int _stringNumber = 0, unsigned int _columnNumber = 0)	:
		ExceptionXml(_stringNumber, _columnNumber)
	{}

	virtual const char* what() const throw(){
		return "Extra characters outside element";
	}
};

class ExceptionXml_SpaceBetweenTagStartSymbolAndElementName : public ExceptionXml{
public:
	ExceptionXml_SpaceBetweenTagStartSymbolAndElementName(unsigned int _stringNumber = 0, unsigned int _columnNumber = 0)	:
		ExceptionXml(_stringNumber, _columnNumber)
	{}

	virtual const char* what() const throw(){
		return "Space between tag start symbol and element name";
	}
};

class ExceptionXml_NoElementName : public ExceptionXml{
public:
	ExceptionXml_NoElementName(unsigned int _stringNumber = 0, unsigned int _columnNumber = 0)	:
		ExceptionXml(_stringNumber, _columnNumber)
	{}

	virtual const char* what() const throw(){
		return "No element name";
	}
};

class ExceptionXml_NoAttributeName : public ExceptionXml{
public:
	ExceptionXml_NoAttributeName(unsigned int _stringNumber = 0, unsigned int _columnNumber = 0)	:
		ExceptionXml(_stringNumber, _columnNumber)
	{}

	virtual const char* what() const throw(){
		return "No attribute name";
	}
};

class ExceptionXml_ExtraCharactersInElementAttributeNames : public ExceptionXml{
public:
	ExceptionXml_ExtraCharactersInElementAttributeNames(unsigned int _stringNumber = 0, unsigned int _columnNumber = 0)	:
		ExceptionXml(_stringNumber, _columnNumber)
	{}

	virtual const char* what() const throw(){
		return "Extra characters in the name of the element or attribute";
	}
};

class ExceptionXml_NotElementWithinElement : public ExceptionXml{
public:
	ExceptionXml_NotElementWithinElement(unsigned int _stringNumber = 0, unsigned int _columnNumber = 0)	:
		ExceptionXml(_stringNumber, _columnNumber)
	{}

	virtual const char* what() const throw(){
		return "Not an element within the element";
	}
};

class ExceptionXml_AttributeValueNotEnclosedInDoubleQuotes : public ExceptionXml{
public:
	ExceptionXml_AttributeValueNotEnclosedInDoubleQuotes(unsigned int _stringNumber = 0, unsigned int _columnNumber = 0)	:
		ExceptionXml(_stringNumber, _columnNumber)
	{}

	virtual const char* what() const throw(){
		return "Attribute value is not enclosed in double quotes";
	}
};

class ExceptionXml_InvalidComment : public ExceptionXml{
public:
	ExceptionXml_InvalidComment(unsigned int _stringNumber = 0, unsigned int _columnNumber = 0)	:
		ExceptionXml(_stringNumber, _columnNumber)
	{}

	virtual const char* what() const throw(){
		return "Invalid comment";
	}
};

class ExceptionXml_WrongEndOfElement : public ExceptionXml{
public:
	ExceptionXml_WrongEndOfElement(unsigned int _stringNumber = 0, unsigned int _columnNumber = 0)	:
		ExceptionXml(_stringNumber, _columnNumber)
	{}

	virtual const char* what() const throw(){
		return "Wrong end of element";
	}
};

class ExceptionXml_UnexpectedShutdownElement : public ExceptionXml{
public:
	ExceptionXml_UnexpectedShutdownElement(unsigned int _stringNumber = 0, unsigned int _columnNumber = 0)	:
		ExceptionXml(_stringNumber, _columnNumber)
	{}

	virtual const char* what() const throw(){
		return "Unexpected shutdown element";
	}
};

#endif

