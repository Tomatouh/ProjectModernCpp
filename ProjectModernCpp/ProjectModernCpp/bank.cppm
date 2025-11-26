export module bank;
import <cstdint>;
import <unordered_map>;
import Player;
export class Bank {
private:
	std::uint8_t const static k_coinsAmount1 = 14;
	std::uint8_t const static k_coinsAmount3 = 10;
	std::uint8_t const static k_coinsAmount6 = 7;
	std::uint8_t const static k_coinsValue1 = 1;
	std::uint8_t const static k_coinsValue3 = 3;
	std::uint8_t const static k_coinsValue6 = 6;
	std::unordered_map<uint8_t, uint8_t> m_coins = { {k_coinsValue1,k_coinsAmount1},{k_coinsValue3,k_coinsAmount3},{k_coinsValue6,k_coinsAmount6} };
	
	//total value for coins at the start of the game
	Bank();
public:
	std::uint8_t k_total = m_coins[k_coinsValue1] + m_coins[k_coinsValue3] * k_coinsValue3 + m_coins[k_coinsValue6] * k_coinsValue6;
	static Bank* theBank;
	void bankTotal();
	void pay1();
	void pay3();
	void pay6();
	void take(uint8_t value, Player & player);
	void give(uint8_t value, Player & player);
	void trade(bool player, Player & p1, Player & p2);


};