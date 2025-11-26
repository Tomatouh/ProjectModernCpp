module bank;
import Player;
import game;
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
void Player::payCoin1(int amount) noexcept {
    m_coin1Count -= amount;
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
			pay6();
			bankTotal();
			value -= Bank::k_coinsValue6;
			player.payCoin6();
		}
		else
		{
			if (player.coin3Count())
			{
				pay3();
				bankTotal();
				value -= Bank::k_coinsValue3;
				player.addCoin3();
			}
			else
			{
				if (m_coins[Bank::k_coinsAmount1])
				{
					pay1();
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