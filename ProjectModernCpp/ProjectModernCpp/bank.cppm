export module bank;
import <cstdint>;
import <unordered_map>;
export class Bank {
private:
	std::unordered_map<uint8_t, uint8_t> m_coins;
public:
	Bank();
	void pay1();
	void pay3();
	void pay6();
	bool take(uint8_t value);
};