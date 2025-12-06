module Player;
import <iostream>;
import <memory>;
//import <stdexcept>;
import card;
import Building;
import <functional>;

Player::Player() : m_name("player"),
m_coins(7),
m_victoryPoints(0),
m_wood(0),
m_stone(0),
m_clay(0),
m_glass(0),
m_papyrus(0)
{
    for (uint16_t i = 0; i < 7; i++)
        m_scientificPoints.push_back(0);
}

Player::Player(std::string name,  uint16_t startCoin1Amount,
    uint16_t startCoin3Amount, uint16_t startCoin6Amount): m_name(std::move(name)),
    m_coins(7),
    m_victoryPoints(0),
    m_wood(0),
    m_stone(0),
    m_clay(0),
    m_glass(0),
    m_papyrus(0)
{
    for (uint16_t i = 0; i < 7; i++)
        m_scientificPoints.push_back(0);
}

Player::Player(const Player& other) : m_name(other.m_name),
m_coins(other.m_coins),
m_victoryPoints(other.m_victoryPoints),
m_wood(other.m_wood),
m_stone(other.m_stone),
m_clay(other.m_clay),
m_glass(other.m_glass),
m_papyrus(other.m_papyrus),
m_brownBuildings(other.m_brownBuildings),
m_greyBuildings(other.m_greyBuildings),
m_blueBuildings(other.m_blueBuildings),
m_greenBuildings(other.m_greenBuildings),
m_redBuildings(other.m_redBuildings),
m_purpleBuildings(other.m_purpleBuildings),
m_scientificPoints(other.m_scientificPoints),
m_scientificPointTypeNumber(other.m_scientificPointTypeNumber),
m_progressTokens(other.m_progressTokens)
{
}

const std::string& Player::name() const noexcept {
    return m_name;
}

void Player::setPlayerName(const std::string_view name)
{
    m_name = name;
}

void Player::addCoin(std::uint16_t amount) noexcept
{
	m_coins = amount;
}

bool Player::payCoin(uint16_t amount) noexcept {
	m_coins -= amount;
}
uint16_t Player::coins() const noexcept {
    return m_coins;
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

Building Player::discardBuilding(Building::Color color, std::uint8_t id)
{
    Building found;
    std::vector<Building>::iterator it;
    switch(color)
    {
    case Building::Color::GREY:
        it = std::find_if(m_greyBuildings.begin(), m_greyBuildings.end(), [id](const Building& b) { return b.getId() == id; });
        if ( it == m_greyBuildings.end()) {
            std::cout << "building not found\n";
            return Building();
        }
        found = std::move(*it);
        m_greyBuildings.erase(it);
        return found;
    case Building::Color::BROWN:
        it = std::find_if(m_brownBuildings.begin(), m_brownBuildings.end(), [id](const Building& b) { return b.getId() == id; });
        if ( it == m_brownBuildings.end()) {
            std::cout << "building not found\n";
            return Building();
        }
        found = std::move(*it);
        m_brownBuildings.erase(it);
        return found;
    }
    
}

const std::vector<Building>& Player::getBrownBuildings() const noexcept { return m_brownBuildings; }
const std::vector<Building>& Player::getGreyBuildings() const noexcept { return m_greyBuildings; }
const std::vector<Building>& Player::getBlueBuildings() const noexcept { return m_blueBuildings; }
const std::vector<Building>& Player::getGreenBuildings() const noexcept { return m_greenBuildings; }
const std::vector<Building>& Player::getYellowBuildings() const noexcept { return m_yellowBuildings; }
const std::vector<Building>& Player::getRedBuildings() const noexcept { return m_redBuildings; }
const std::vector<Building>& Player::getPurpleBuildings() const noexcept { return m_purpleBuildings; }

const std::array<std::pair<std::shared_ptr<Card>, std::shared_ptr<Building>>, Player::k_numberOfWonders> Player::getWonders() const noexcept { return m_wonders; }


uint16_t Player::getVictoryPoints() const noexcept { return m_victoryPoints; }
void Player::addVictoryPoints(uint16_t points) noexcept { m_victoryPoints += points; }

uint16_t Player::getWood() const noexcept { return m_wood; }
void Player::addWood(uint16_t amount) noexcept { m_wood += amount; }
uint16_t Player::getStone() const noexcept { return m_stone; }
void Player::addStone(uint16_t amount) noexcept { m_stone += amount; }
uint16_t Player::getClay() const noexcept { return m_clay; }
void Player::addClay(uint16_t amount) noexcept { m_clay += amount; }
uint16_t Player::getGlass() const noexcept { return m_glass; }
void Player::addGlass(uint16_t amount) noexcept { m_glass += amount; }
uint16_t Player::getPapyrus() const noexcept { return m_papyrus; }
void Player::addPapyrus(uint16_t amount) noexcept { m_papyrus += amount; }

void Player::showStatus(std::ostream& os) const {
    os << "Player " << m_name << " | coins=" << coins() <<"\n";
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

void Player::addScientificPoint(Building::ScientificSymbol point) noexcept
{
    uint16_t auxIndex = static_cast<uint16_t>(point);
    m_scientificPoints[auxIndex]++;
    if (m_scientificPoints[auxIndex] == 2)
    {
        //Add new progress token
        std::cout << "Placeholder";
    }
    else
    {
        m_scientificPointTypeNumber++;
    }
    if (m_scientificPointTypeNumber == 6)
    {
        std::cout << "Scientific victory for player " << this->name();
        exit(0);
    }
}
std::vector<uint16_t> Player::getScientificPoints() noexcept
{
    return m_scientificPoints;
}
std::vector<Player::ProgressToken> Player::getProgressTokens()
{
    return m_progressTokens;
}
void Player::applyEffects()
{
    std::unique_ptr<Player> aux(this);
    for (auto progresToken : m_progressTokens)
        progresToken.applyEffect(std::move(aux));
}
void Player::ProgressToken::applyEffect(std::unique_ptr<Player> player)
{
    m_effect(std::move(player));
}

Player::ProgressToken Player::ProgressToken::agricultureToken([](std::unique_ptr<Player> player) {
    player->addCoin(6);
    player->addVictoryPoints(4);
    }, true);

Player::ProgressToken Player::ProgressToken::lawToken([](std::unique_ptr<Player> player) {
    std::vector<uint16_t> vect = player->getScientificPoints();
    for(uint16_t i=0;i<vect.size();i++)
        if (vect[i] != 2)
        {
            player->addScientificPoint((Building::ScientificSymbol)i);
            break;
        }
    }, true);

Player::ProgressToken Player::ProgressToken::philosphyToken([](std::unique_ptr<Player> player) {
    player->addVictoryPoints(6);
    }, true);

Player::ProgressToken Player::ProgressToken::mathematicsToken([](std::unique_ptr<Player> player) {
    player->addVictoryPoints(player->getProgressTokens().size()*3);
    }, true);

Player::ProgressToken Player::ProgressToken::economyToken([](std::unique_ptr<Player> player) {
    player->m_hasEconomyProgressToken = 1;
    }, false);

Player::ProgressToken Player::ProgressToken::masonryToken([](std::unique_ptr<Player> player) {
    player->m_hasMasonryProgressToken = 1;
    }, false);

Player::ProgressToken Player::ProgressToken::strategyToken([](std::unique_ptr<Player> player) {
    player->m_hasStrategyProgressToken = 1;
    }, false);

Player::ProgressToken Player::ProgressToken::theologyToken([](std::unique_ptr<Player> player) {
    player->m_hasTheologyProgressToken = 1;
    }, false);

Player::ProgressToken Player::ProgressToken::urbanismToken([](std::unique_ptr<Player> player) {
    player->m_hasUrbanismProgressToken = 1;
    }, false);

Player::ProgressToken Player::ProgressToken::architectureToken([](std::unique_ptr<Player> player) {
    player->m_hasArchitectureProgressToken = 1;
    }, false);

Player::ProgressToken::ProgressToken(std::function<void(std::unique_ptr<Player> player)> effect, bool isOneTime)
{
    this->m_effect = effect;
    this->m_isOneTime = isOneTime;
}
