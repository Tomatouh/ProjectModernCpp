export module bank;
import <cstdint>;
import <unordered_map>;
import Player;
import buildingResource;

export class Bank {
private:
    std::uint16_t const static k_coinsAmount1 = 14;
    std::uint16_t const static k_coinsAmount3 = 10;
    std::uint16_t const static k_coinsAmount6 = 7;
    std::uint16_t const static k_coinsValue1 = 1;
    std::uint16_t const static k_coinsValue3 = 3;
    std::uint16_t const static k_coinsValue6 = 6;
    std::unordered_map<uint16_t, uint16_t> m_coins = { {k_coinsValue1,k_coinsAmount1},{k_coinsValue3,k_coinsAmount3},{k_coinsValue6,k_coinsAmount6} };
public:
    Bank();
    Bank(const Bank& other);
    Bank& operator=(const Bank& other);
    ~Bank();

    std::uint16_t k_total = m_coins[k_coinsValue1] + m_coins[k_coinsValue3] * k_coinsValue3 + m_coins[k_coinsValue6] * k_coinsValue6;
    static Bank* theBank;
    void bankTotal();
    void deposit1();
    void deposit3();
    void deposit6();
    void take(uint16_t value, Player & player);
    void give(uint16_t value, Player & player);
    void trade(bool player, Player & p1, Player & p2, ResourceType type);
};