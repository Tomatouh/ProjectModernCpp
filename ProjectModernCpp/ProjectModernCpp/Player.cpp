module Player;
import <iostream>;
//import <stdexcept>;
import card;
import Building;

Player::Player(std::string name, bool isPlayer1)
    : name_(std::move(name)),
    m_isPlayer1(isPlayer1),
    coin1_count_(7),
    coin3_count_(0),
    coin6_count_(0),
    total_coin_value_(7),
    score_(0)
{
}

const std::string& Player::name() const noexcept {
    return name_;
}

bool Player::isPlayer1() const noexcept {
    return m_isPlayer1;
}

void Player::setIsPlayer1(bool isPlayer1) noexcept {
    m_isPlayer1 = isPlayer1;
}

int Player::coins() const noexcept {
    return total_coin_value_;
}

void Player::addCoins(int n) noexcept {
    total_coin_value_ += n;
}

bool Player::spendCoins(int n) noexcept {
    if (n > total_coin_value_) {
        return false;
    }
    total_coin_value_ -= n;
    return true;
}

int Player::coin1Count() const noexcept {
    return coin1_count_;
}

int Player::coin3Count() const noexcept {
    return coin3_count_;
}

int Player::coin6Count() const noexcept {
    return coin6_count_;
}

int Player::totalCoinValue() const noexcept {
    return total_coin_value_;
}


void Player::addBuilding(const Building& building) {
    switch (building.getColor()) {
    case Building::Color::BROWN:
        brownBuildings_.push_back(building);
        break;
    case Building::Color::GREY:
        greyBuildings_.push_back(building);
        break;
    case Building::Color::BLUE:
        blueBuildings_.push_back(building);
        break;
    case Building::Color::GREEN:
        greenBuildings_.push_back(building);
        break;
    case Building::Color::YELLOW:
        yellowBuildings_.push_back(building);
        break;
    case Building::Color::RED:
        redBuildings_.push_back(building);
        break;
    case Building::Color::PURPLE:
        purpleBuildings_.push_back(building);
        break;
    }
}

const std::vector<Building>& Player::getBrownBuildings() const noexcept { return brownBuildings_; }
const std::vector<Building>& Player::getGreyBuildings() const noexcept { return greyBuildings_; }
const std::vector<Building>& Player::getBlueBuildings() const noexcept { return blueBuildings_; }
const std::vector<Building>& Player::getGreenBuildings() const noexcept { return greenBuildings_; }
const std::vector<Building>& Player::getYellowBuildings() const noexcept { return yellowBuildings_; }
const std::vector<Building>& Player::getRedBuildings() const noexcept { return redBuildings_; }
const std::vector<Building>& Player::getPurpleBuildings() const noexcept { return purpleBuildings_; }

int Player::getScore() const noexcept {
    return score_;
}

uint8_t Player::getVictoryPoints() const noexcept { return victory_points_; }
void Player::addVictoryPoints(uint8_t points) noexcept { victory_points_ += points; }

int Player::getMilitaryPoints() const noexcept { return military_points_; }
void Player::addMilitaryPoints(int points) noexcept { military_points_ += points; }

uint8_t Player::getWood() const noexcept { return wood_; }
void Player::addWood(uint8_t amount) noexcept { wood_ += amount; }
uint8_t Player::getStone() const noexcept { return stone_; }
void Player::addStone(uint8_t amount) noexcept { stone_ += amount; }
uint8_t Player::getClay() const noexcept { return clay_; }
void Player::addClay(uint8_t amount) noexcept { clay_ += amount; }
uint8_t Player::getGlass() const noexcept { return glass_; }
void Player::addGlass(uint8_t amount) noexcept { glass_ += amount; }
uint8_t Player::getPapyrus() const noexcept { return papyrus_; }
void Player::addPapyrus(uint8_t amount) noexcept { papyrus_ += amount; }

void Player::showStatus(std::ostream& os) const {
    os << "Player " << name_ << " | coins=" << total_coin_value_
        << " (1s=" << coin1_count_ << ", 3s=" << coin3_count_ << ", 6s=" << coin6_count_ << ")\n";
    os << "Score: " << getScore() << "\n";
}

void Player::showCards(std::ostream& os) const {
    os << name_ << " owns buildings:\n";
    os << " - Brown: " << brownBuildings_.size() << "\n";
    os << " - Grey: " << greyBuildings_.size() << "\n";
    os << " - Blue: " << blueBuildings_.size() << "\n";
    os << " - Green: " << greenBuildings_.size() << "\n";
    os << " - Yellow: " << yellowBuildings_.size() << "\n";
    os << " - Red: " << redBuildings_.size() << "\n";
    os << " - Purple: " << purpleBuildings_.size() << "\n";
}