module bank;
import Player;
void Bank::pay1()
{
	m_coins[Bank::k_coinsAmount1]++;
}
void Bank::pay3()
{
	m_coins[Bank::k_coinsAmount3]++;
}
void Bank::pay6()
{
	m_coins[Bank::k_coinsAmount6]++;
}
int Bank::take(uint8_t value)
{
	while (value)
	{
		if (m_coins[Bank::k_coinsAmount6])
		{
			m_coins[Bank::k_coinsAmount6]--;
			value -= Bank::k_coinsValue6;
			Player::addCoin6();
		}
		else
		{
			if (m_coins[Bank::k_coinsAmount3])
			{
				m_coins[Bank::k_coinsAmount3]--;
				value -= Bank::k_coinsValue3;
				Player::addCoin3();
			}
			else
			{
				if (m_coins[Bank::k_coinsAmount1])
				{
					m_coins[Bank::k_coinsAmount1]--;
					value -= Bank::k_coinsValue1;
					Player::addCoin1();
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
void Bank::trade(bool player, Player & p1, Player & p2)
{
	//if(player==false)
	//	if(p1.getYellowBuildings()))

}