module Player;
import <iostream>;
//import <stdexcept>;
import card;
import Building;

Player::Player(std::string name, bool isPlayer1, int startCoin1Amount,
    int startCoin3Amount, int startCoin6Amount)
    : m_name(std::move(name)),
    m_isPlayer1(isPlayer1),
    m_coin1Count(startCoin1Amount),
    m_coin3Count(startCoin3Amount),
    m_coin6Count(startCoin6Amount),
    m_victoryPoints(0),
    m_militaryPoints(0),
    m_wood(0),
    m_stone(0),
    m_clay(0),
    m_glass(0),
    m_papyrus(0)
{
    for (int i = 0; i < 7; i++)
        m_scientificPoints.push_back(0);
}

const std::string& Player::name() const noexcept {
    return m_name;
}

bool Player::isPlayer1() const noexcept {
    return m_isPlayer1;
}

void Player::setIsPlayer1(bool isPlayer1) noexcept {
    m_isPlayer1 = isPlayer1;
}

void Player::addCoin1(int amount) noexcept {
    m_coin1Count += amount;
}

void Player::addCoin3(int amount) noexcept {
    m_coin3Count += amount;
}

void Player::addCoin6(int amount) noexcept {
    m_coin6Count += amount;
}

int Player::coin1Count() const noexcept {
    return m_coin1Count;
}

int Player::coin3Count() const noexcept {
    return m_coin3Count;
}

int Player::coin6Count() const noexcept {
    return m_coin6Count;
}

int Player::totalCoinValue() const noexcept {
    return (m_coin1Count * 1) + (m_coin3Count * 3) + (m_coin6Count * 6);
}

int Player::coins() const noexcept {
    return totalCoinValue();
}


void Player::addBuilding(const Building& building) {
    switch (building.getColor()) {
    case Building::Color::BROWN:
        m_brownBuildings.push_back(building);
        break;
    case Building::Color::GREY:
        m_greyBuildings.push_back(building);
        break;
    case Building::Color::BLUE:
        m_blueBuildings.push_back(building);
        break;
    case Building::Color::GREEN:
        m_greenBuildings.push_back(building);
        break;
    case Building::Color::YELLOW:
        m_yellowBuildings.push_back(building);
        break;
    case Building::Color::RED:
        m_redBuildings.push_back(building);
        break;
    case Building::Color::PURPLE:
        m_purpleBuildings.push_back(building);
        break;
    }
}

const std::vector<Building>& Player::getBrownBuildings() const noexcept { return m_brownBuildings; }
const std::vector<Building>& Player::getGreyBuildings() const noexcept { return m_greyBuildings; }
const std::vector<Building>& Player::getBlueBuildings() const noexcept { return m_blueBuildings; }
const std::vector<Building>& Player::getGreenBuildings() const noexcept { return m_greenBuildings; }
const std::vector<Building>& Player::getYellowBuildings() const noexcept { return m_yellowBuildings; }
const std::vector<Building>& Player::getRedBuildings() const noexcept { return m_redBuildings; }
const std::vector<Building>& Player::getPurpleBuildings() const noexcept { return m_purpleBuildings; }


uint8_t Player::getVictoryPoints() const noexcept { return m_victoryPoints; }
void Player::addVictoryPoints(uint8_t points) noexcept { m_victoryPoints += points; }

int Player::getMilitaryPoints() const noexcept { return m_militaryPoints; }
void Player::addMilitaryPoints(int points) noexcept { m_militaryPoints += points; }

uint8_t Player::getWood() const noexcept { return m_wood; }
void Player::addWood(uint8_t amount) noexcept { m_wood += amount; }
uint8_t Player::getStone() const noexcept { return m_stone; }
void Player::addStone(uint8_t amount) noexcept { m_stone += amount; }
uint8_t Player::getClay() const noexcept { return m_clay; }
void Player::addClay(uint8_t amount) noexcept { m_clay += amount; }
uint8_t Player::getGlass() const noexcept { return m_glass; }
void Player::addGlass(uint8_t amount) noexcept { m_glass += amount; }
uint8_t Player::getPapyrus() const noexcept { return m_papyrus; }
void Player::addPapyrus(uint8_t amount) noexcept { m_papyrus += amount; }

void Player::showStatus(std::ostream& os) const {
    os << "Player " << m_name << " | coins=" << totalCoinValue()
        << " (1s=" << m_coin1Count << ", 3s=" << m_coin3Count << ", 6s=" << m_coin6Count << ")\n";
}

void Player::showCards(std::ostream& os) const {
    os << m_name << " owns buildings:\n";
    os << " - Brown: " << m_brownBuildings.size() << "\n";
    os << " - Grey: " << m_greyBuildings.size() << "\n";
    os << " - Blue: " << m_blueBuildings.size() << "\n";
    os << " - Green: " << m_greenBuildings.size() << "\n";
    os << " - Yellow: " << m_yellowBuildings.size() << "\n";
    os << " - Red: " << m_redBuildings.size() << "\n";
    os << " - Purple: " << m_purpleBuildings.size() << "\n";
}

void Player::addScientificPoint(Player::scientificPointType point)
{
    switch (point)
    {
        case Player::scientificPointType::Globe: { m_scientificPoints[0]; break; }
        case Player::scientificPointType::Law: { m_scientificPoints[1]; break; }
        case Player::scientificPointType::Time: { m_scientificPoints[2]; break; }
        case Player::scientificPointType::Medicine: { m_scientificPoints[3]; break; }
        case Player::scientificPointType::Architecture: { m_scientificPoints[4]; break; }
        case Player::scientificPointType::Writing: { m_scientificPoints[5]; break; }
        case Player::scientificPointType::Wheel: { m_scientificPoints[6]; break; }
    }
}