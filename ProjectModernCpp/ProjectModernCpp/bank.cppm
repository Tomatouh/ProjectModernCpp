export module bank;
import <cstdint>;
import <unordered_map>;
export class Bank {
private:
	std::unordered_map<uint8_t, uint8_t> m_coins;
	Bank();
public:
	static Bank* theBank;
	void pay1();
	void pay3();
	void pay6();
	int take(uint8_t value);
	bool trade();


};