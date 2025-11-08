export module money;
import <cstdint>;
import <array>;
export class Money
{
private:
	std::array<uint8_t, 33> m_coins;
public:
	Money();
	std::array<uint8_t, 33> getCoins();
	void add1();
	void add3();
	void add6();
	bool remove(uint8_t value);
};
