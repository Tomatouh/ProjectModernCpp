#pragma once
#include "Resource.h"
#include "Bank.h"
class Money: public Resource
{
private:
	uint8_t m_value;
	static Bank* m_bank;
public:
	Money();
	bool add(const uint8_t& value);
	bool subtract(const uint8_t& value);
	uint8_t getValue() const;

};

