module money;
Money::Money()
{
	m_coins[0] = 1;
	m_coins[1] = 2;
	m_coins[3] = 0;
}
std::unordered_map<uint8_t, uint8_t> Money::getCoins()
{
	return m_coins;
}
void Money::add1()
{
	m_coins[0]++;
}
void Money::add3()
{
	m_coins[1]++;
}
void Money::add6()
{
	m_coins[2]++;
}
bool Money::pay(uint8_t value)
{
	//Always chooses the coins with the maximum value
	while (value)
	{
		if (m_coins[2])
		{
			m_coins[2]--;
			value -= 6;
			Bank::theBank->pay6();
		}
		else
		{
			if (m_coins[1])
			{
				m_coins[1]--;
				value -= 3;
				Bank::theBank->pay3();
			}
			else
			{
				if (m_coins[0])
				{
					m_coins[0]--;
					value -= 1;
					Bank::theBank->pay1();
				}
				else
				{
					return 0;
				}
			}
			
		}
	}
	return 1;
}