module bank;
import Player;
import game;
void Bank::deposit1()
{
	m_coins[Bank::k_coinsAmount1]++;
}
void Bank::deposit3()
{
	m_coins[Bank::k_coinsAmount3]++;
}
void Bank::deposit6()
{
	m_coins[Bank::k_coinsAmount6]++;
}

void Bank::bankTotal()
{
    this->k_total = this->m_coins[Bank::k_coinsAmount1] * Bank::k_coinsValue1 +
                    this->m_coins[Bank::k_coinsAmount3] * Bank::k_coinsValue3 +
                    this->m_coins[Bank::k_coinsAmount6] * Bank::k_coinsValue6;
}
void Bank::give(uint8_t value, Player& player)
{
	while (value)
	{
		if (player.coin6Count())
		{
			deposit6();
			bankTotal();
			value -= Bank::k_coinsValue6;
			player.payCoin6();
		}
		else
		{
			if (player.coin3Count())
			{
				deposit3();
				bankTotal();
				value -= Bank::k_coinsValue3;
				player.addCoin3();
			}
			else
			{
				if (m_coins[Bank::k_coinsAmount1])
				{
					deposit1();
					bankTotal();
					value -= Bank::k_coinsValue1;
					player.addCoin1();
				}

			}

		}
	}
}
void Bank::take(uint8_t value, Player &player)
{
	while (value)
	{
		if (m_coins[Bank::k_coinsAmount6])
		{
			m_coins[Bank::k_coinsAmount6]--;
			bankTotal();
			value -= Bank::k_coinsValue6;
			player.addCoin6();
		}
		else
		{
			if (m_coins[Bank::k_coinsAmount3])
			{
				m_coins[Bank::k_coinsAmount3]--;
				bankTotal();
				value -= Bank::k_coinsValue3;
				player.addCoin3();
			}
			else
			{
				if (m_coins[Bank::k_coinsAmount1])
				{
					m_coins[Bank::k_coinsAmount1]--;
					bankTotal();
					value -= Bank::k_coinsValue1;
					player.addCoin1();
				}

			}

		}
	}
}
void Bank::trade(bool player, Player & p1, Player & p2)
{
	//if(player==false)
	//	if(p1.getYellowBuildings()))

}