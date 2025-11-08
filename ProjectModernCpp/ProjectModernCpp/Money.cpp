module money;
Money::Money()
{
	for (int i = 0; i < 33; i++)
	{
		if (i == 14 || i == 25)
			m_coins[i] = 255;
		else
			m_coins[i] = 6;
	}
}
std::array<uint8_t, 33> Money::getCoins()
{
	return m_coins;
}
void Money::add1()
{
	for(int i=0;i<14;i++)
		if (m_coins[i] == 0)
		{
			m_coins[i] = 1;
			return;
		}
}
void Money::add3()
{
	for (int i = 15; i < 25; i++)
		if (m_coins[i] == 0)
		{
			m_coins[i] = 3;
			return;
		}
}
void Money::add6()
{
	for (int i = 26; i < 34; i++)
		if (m_coins[i] == 0)
		{
			m_coins[i] = 6;
			return;
		}
}
bool Money::remove(uint8_t value)
{
	int8_t iAux=32;
	while (value && iAux>-1)
	{
		if (iAux > 25)
		{
			if (m_coins[iAux])
			{
				value = value - 6;
				m_coins[iAux] = 0;
			}
		}
		if (iAux < 25)
		{
			if (m_coins[iAux])
			{
				value = value - 3;
				m_coins[iAux] = 0;
			}
		}
		if (iAux < 14)
		{
			if (m_coins[iAux])
			{
				value = value - 1;
				m_coins[iAux] = 0;
			}
		}
		iAux--;
	}
	return !value;
}