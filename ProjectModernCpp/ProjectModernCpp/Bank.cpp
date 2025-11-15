module bank;
Bank::Bank()
{
	m_coins[0] = 12;
	m_coins[1] = 6;
	m_coins[3] = 7;
}
void Bank::pay1()
{
	m_coins[0]++;
}
void Bank::pay3()
{
	m_coins[1]++;
}
void Bank::pay6()
{
	m_coins[2]++;
}
int Bank::take(uint8_t value)
{
	while (value)
	{
		if (m_coins[2])
		{
			m_coins[2]--;
			value -= 6;
			//Player.add6();
		}
		else
		{
			if (m_coins[1])
			{
				m_coins[1]--;
				value -= 3;
				//Player.add3();
			}
			else
			{
				if (m_coins[0])
				{
					m_coins[0]--;
					value -= 1;
					//Player.add1();
				}
				else
				{
					return value;
				}
			}

		}
	}
	return 0;
}
Bank* Bank::theBank=new Bank();