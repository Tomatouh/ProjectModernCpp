#pragma once
#include <stdint.h>
#include <iostream>
class Bank
{
private:
	uint8_t m_value;
public:
	Bank();
	uint8_t getValue() const;
	void add(const uint8_t& value);
	void subtract(const uint8_t& value);
};

