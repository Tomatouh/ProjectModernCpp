module money;
Money::Money()
{
	m_value = 7;
}
bool Money::add(const uint8_t& value)
{
		m_value += value;
		return 0;
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
		return true;
	}
	else
	{
		m_value -= value;
		return true;
	}
	return false;
}