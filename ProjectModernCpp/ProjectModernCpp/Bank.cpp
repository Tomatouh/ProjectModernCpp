#include "Bank.h"
Bank::Bank()
{
	m_value = 17;
}
uint8_t Bank::getValue() const
{
	return m_value;
}
void Bank::add(const uint8_t& value)
{
	if (value + m_value > 31)
	{
		m_value = 31;
		std::cout << "This is very bad. Something is causing more coins to appear";
	}
	else
	{
		m_value+=value;
	}
}
void Bank::subtract(const uint8_t& value)
{
	m_value -= value;
}