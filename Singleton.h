#ifndef SINGLETON_H
#define SINGLETON_H

template<class T>
class Singleton{
protected:
	Singleton(){}
	Singleton(const Singleton&);
	Singleton& operator=(Singleton&);
	~Singleton(){}

public:
	static T& getInstance(){
		static T instance;
		return instance;
	}
};

#endif