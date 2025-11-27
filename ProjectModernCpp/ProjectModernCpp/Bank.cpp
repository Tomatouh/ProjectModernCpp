module bank;
import Player;
import game;
import buildingResource;
import Building;

void Bank::deposit1()
{
    m_coins[Bank::k_coinsValue1]++;
    bankTotal();
}
void Bank::deposit3()
{
    m_coins[Bank::k_coinsValue3]++;
    bankTotal();
}
void Bank::deposit6()
{
    m_coins[Bank::k_coinsValue6]++;
    bankTotal();
}

void Bank::bankTotal()
{
    this->k_total = this->m_coins[Bank::k_coinsValue1] * Bank::k_coinsValue1 +
                    this->m_coins[Bank::k_coinsValue3] * Bank::k_coinsValue3 +
                    this->m_coins[Bank::k_coinsValue6] * Bank::k_coinsValue6;
}

void Bank::give(uint8_t value, Player& player)
{
    if (player.coins() == 0)
        return;

    int needed = static_cast<int>(value);
    int paid = 0;

    while (paid < needed) {
        if (player.coin1Count() > 0) {
            player.payCoin1(1);
            m_coins[Bank::k_coinsValue1]++;
            paid += Bank::k_coinsValue1;
            bankTotal();
        }
        else if (player.coin3Count() > 0) {
            player.payCoin3(1);
            m_coins[Bank::k_coinsValue3]++;
            paid += Bank::k_coinsValue3;
            bankTotal();
        }
        else if (player.coin6Count() > 0) {
            player.payCoin6(1);
            m_coins[Bank::k_coinsValue6]++;
            paid += Bank::k_coinsValue6;
            bankTotal();
        }
        else {
            break;
        }
    }

    if (paid > needed) {
        uint8_t change = static_cast<uint8_t>(paid - needed);
        take(change, player);
    }
}

void Bank::take(uint8_t value, Player &player)
{
    int remaining = static_cast<int>(value);

    while (remaining > 0) {
        if (remaining >= static_cast<int>(Bank::k_coinsValue6) && m_coins[Bank::k_coinsValue6] > 0) {
            m_coins[Bank::k_coinsValue6]--;
            player.addCoin6(1);
            remaining -= Bank::k_coinsValue6;
            bankTotal();
        }
        else if (remaining >= static_cast<int>(Bank::k_coinsValue3) && m_coins[Bank::k_coinsValue3] > 0) {
            m_coins[Bank::k_coinsValue3]--;
            player.addCoin3(1);
            remaining -= Bank::k_coinsValue3;
            bankTotal();
        }
        else if (remaining >= static_cast<int>(Bank::k_coinsValue1) && m_coins[Bank::k_coinsValue1] > 0) {
            m_coins[Bank::k_coinsValue1]--;
            player.addCoin1(1);
            remaining -= Bank::k_coinsValue1;
            bankTotal();
        }
        else {
            if (m_coins[Bank::k_coinsValue3] > 0) {
                m_coins[Bank::k_coinsValue3]--;
                player.addCoin3(1);
                remaining -= Bank::k_coinsValue3;
                bankTotal();
            }
            else if (m_coins[Bank::k_coinsValue6] > 0) {
                m_coins[Bank::k_coinsValue6]--;
                player.addCoin6(1);
                remaining -= Bank::k_coinsValue6;
                bankTotal();
            }
            else if (m_coins[Bank::k_coinsValue1] > 0) {
                m_coins[Bank::k_coinsValue1]--;
                player.addCoin1(1);
                remaining -= Bank::k_coinsValue1;
                bankTotal();
            }
            else {
                break;
            }
        }
    }
}
static std::size_t countBuildingsProducing(const Player& player, ResourceType type)
{
    if (!(type == ResourceType::WOOD || type == ResourceType::CLAY || type == ResourceType::STONE ||
          type == ResourceType::GLASS || type == ResourceType::PAPYRUS)) {
        return 0;
    }

    std::size_t count = 0;
    auto check_vec = [&](const std::vector<Building>& vec) {
        for (const auto& b : vec) {
            const auto res = b.getResources();
            if (res.empty()) continue; 
            for (const auto& r : res) {
                if (r == type) { ++count; break; }
            }
        }
    };

    check_vec(player.getBrownBuildings());
    check_vec(player.getGreyBuildings());
    check_vec(player.getYellowBuildings());

    return count;
}

void Bank::trade(bool player, Player& p1, Player& p2, ResourceType type)
{
    Player* buyer = player ? &p2 : &p1;   
    Player* enemy = player ? &p1 : &p2;  

    if (!(type == ResourceType::WOOD || type == ResourceType::CLAY || type == ResourceType::STONE ||
          type == ResourceType::GLASS || type == ResourceType::PAPYRUS)) {
        return;
    }

    bool buyerHasDiscount = false;
    for (const auto& y : buyer->getYellowBuildings()) {
        uint8_t id = y.getId();
        if (id < 40 || id > 43) continue;

        if (id == 40 && type == ResourceType::STONE) { buyerHasDiscount = true; break; }
        if (id == 41 && type == ResourceType::CLAY)  { buyerHasDiscount = true; break; }
        if (id == 42 && type == ResourceType::WOOD)  { buyerHasDiscount = true; break; }
        if (id == 43 && (type == ResourceType::GLASS || type == ResourceType::PAPYRUS)) { buyerHasDiscount = true; break; }

        for (const auto& r : y.getResources()) {
            if (r == type) { buyerHasDiscount = true; break; }
        }
        if (buyerHasDiscount) break;
    }

    std::uint8_t cost = 0;
    if (buyerHasDiscount) {
        cost = 1;
    } else {
        std::size_t enemyCount = countBuildingsProducing(*enemy, type);
        std::size_t total = 2 + enemyCount;
        cost = static_cast<std::uint8_t>((total > 255) ? 255 : total);
    }

    if (cost > 0) {
        give(cost, *buyer);
    }
}

Bank::Bank(const Bank& other)
    : m_coins(other.m_coins), k_total(other.k_total) {}

Bank& Bank::operator=(const Bank& other) {
    if (this != &other) {
        m_coins = other.m_coins;
        k_total = other.k_total;
    }
    return *this;
}

Bank::~Bank() = default;