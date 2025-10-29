#pragma once
#include "Resource.h"
class Money: public Resource
{
private:
	uint8_t value;
public:
	Money();
	void add1();
	void add3();
	void add6();
	uint8_t getValue() const;

};

