// MyClass.h

#ifndef _MyClass_h
#define _MyClass_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class MyClass
{
 protected:


 public:
	void init();
};

extern MyClass ;

#endif

