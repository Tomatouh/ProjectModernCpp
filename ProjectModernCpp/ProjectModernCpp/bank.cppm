export module bank;
import <cstdint>;
import <unordered_map>;
export class Bank {
private:
	std::uint8_t const k_coinsAmount1 = 14;
	std::uint8_t const k_coinsAmount3 = 10;
	std::uint8_t const k_coinsAmount6 = 7;
	std::uint8_t const k_coinsValue1 = 1;
	std::uint8_t const k_coinsValue3 = 3;
	std::uint8_t const k_coinsValue6 = 6;
	std::unordered_map<uint8_t, uint8_t> m_coins = { {k_coinsValue1,k_coinsAmount1},{k_coinsValue3,k_coinsAmount3},{k_coinsValue6,k_coinsAmount6} };
	std::uint8_t total=m_coins[k_coinsValue1]+ m_coins[k_coinsValue3] * k_coinsValue3 +m_coins[k_coinsValue6] * k_coinsValue6; 
	//total value for coins at the start of the game
	Bank();
public:
	static Bank* theBank;
	void pay1();
	void pay3();
	void pay6();
	int take(uint8_t value);
	bool trade();


};