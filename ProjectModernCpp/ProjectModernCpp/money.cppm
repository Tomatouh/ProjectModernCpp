export module money;
import <cstdint>;
import <unordered_map>;
export class Money
{
private:
	std::unordered_map<uint8_t, uint8_t> m_coins;
public:
	Money();
	std::unordered_map<uint8_t, uint8_t> getCoins();
	void add1();
	void add3();
	void add6();
	bool pay(uint8_t value);
};
