#include "Money.h"
Money::Money()
{
	m_value = 7;
}
bool Money::add(const uint8_t& value)
{
	if (m_bank->getValue() < value)
	{
		m_value += m_bank->getValue();
		m_bank->subtract(value);
		return 0;
	}
	else
	{
		m_value += value;
		m_bank->subtract(value);
		return 0;
	}
}
uint8_t Money::getValue() const
{
	return m_value;
}
bool Money::subtract(const uint8_t& value)
{
	if(value>m_value)
	{
		m_value = 0;
		m_bank->add(m_value);
	}
	else
	{
		m_value -= value;
		m_bank->add(value);
	}
}
Bank* Money::m_bank = new Bank();