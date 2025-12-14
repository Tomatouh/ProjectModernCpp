module Player;
import <iostream>;
import <memory>;
//import <stdexcept>;
import card;
import Building;
import <functional>;
import buildingResource;

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
	m_coins += amount;
}

void Player::payCoin(uint16_t amount) noexcept {
	m_coins -= amount;
    
}
uint16_t Player::getCoins() const noexcept {
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

	//Add appropriate resources
   /* m_coins = m_coins - building.getCost().getCostCoins();
	std::vector<ResourceType> buildingResource = building.getResources();
    for (auto resource : buildingResource)
    {
        switch (resource)
        {
        case ResourceType::WOOD:
        {
            m_wood++;
            break;
        }
        case ResourceType::STONE:
        {
            m_stone++;
            break;
        }
        case ResourceType::CLAY:
        {
            m_clay++;
            break;
        }
        case ResourceType::GLASS:
        {
            m_glass++;
            break;
        }
        case ResourceType::PAPYRUS:
        {
            m_papyrus++;
            break;
        }
        }
	}
	m_victoryPoints = m_victoryPoints + building.getVictoryPoints();*/
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

void Player::addWonder(const std::shared_ptr<Card>& wonder)
{
    std::pair<std::shared_ptr<Card>, std::optional<std::shared_ptr<Building>>> card{ wonder, std::make_optional(nullptr) };
    m_wonders.push_back(card);
}

const std::vector<Building>& Player::getBrownBuildings() const noexcept { return m_brownBuildings; }
const std::vector<Building>& Player::getGreyBuildings() const noexcept { return m_greyBuildings; }
const std::vector<Building>& Player::getBlueBuildings() const noexcept { return m_blueBuildings; }
const std::vector<Building>& Player::getGreenBuildings() const noexcept { return m_greenBuildings; }
const std::vector<Building>& Player::getYellowBuildings() const noexcept { return m_yellowBuildings; }
const std::vector<Building>& Player::getRedBuildings() const noexcept { return m_redBuildings; }
const std::vector<Building>& Player::getPurpleBuildings() const noexcept { return m_purpleBuildings; }

const std::vector<std::pair<std::shared_ptr<Card>, std::optional<std::shared_ptr<Building>>>> Player::getWonders() const noexcept { return m_wonders; }


uint16_t Player::getVictoryPoints() const noexcept { return m_victoryPoints; }
void Player::addVictoryPoints(uint16_t points) noexcept { m_victoryPoints += points; }

void Player::addResources(const std::vector<ResourceType>& resources)
{
    for (const auto& resource : resources) {
        switch (resource)
        {
        case ResourceType::WOOD:
        {
            m_wood++;
            break;
        }
        case ResourceType::STONE:
        {
            m_stone++;
            break;
        }
        case ResourceType::CLAY:
        {
            m_clay++;
            break;
        }
        case ResourceType::GLASS:
        {
            m_glass++;
            break;
        }
        case ResourceType::PAPYRUS:
        {
            m_papyrus++;
            break;
        }
        }
    }
}

void Player::addProduction(const std::vector<ResourceType>& resources)
{
    for (const auto& resource : resources) {
        m_productions[resource]++;
    }
}

uint16_t Player::getWood() const noexcept { return m_wood; }
uint16_t Player::getStone() const noexcept { return m_stone; }
uint16_t Player::getClay() const noexcept { return m_clay; }
uint16_t Player::getGlass() const noexcept { return m_glass; }
uint16_t Player::getPapyrus() const noexcept { return m_papyrus; }

void Player::showStatus(std::ostream& os) const {
    os << "Player " << m_name << " | coins=" << getCoins() <<"\n";
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

bool Player::hasDiscountFor(ResourceType type) const
{
    std::uint8_t requiredId = 0;

    switch (type)
    {
    case ResourceType::WOOD: requiredId = 42; break;
    case ResourceType::CLAY: requiredId = 41; break;
    case ResourceType::STONE: requiredId = 40; break;
    case ResourceType::GLASS: requiredId = 43; break;
    case ResourceType::PAPYRUS: requiredId = 43; break;
    }

    for (const auto& building : m_yellowBuildings)
    {
        if (building.getId() == requiredId)
        {
            return true;
        }
    }
    return false;
}

std::uint16_t Player::countOpponentProduction(ResourceType type) const {
    std::uint16_t count = 0;

    auto countInList = [&](const std::vector<Building>& buildings) {
        for (const auto& b : buildings) {
            for (const auto& r : b.getResources()) {
                if (r == type) {
                    count++;
                }
            }
        }
        };

    countInList(m_brownBuildings);
    countInList(m_greyBuildings);

    return count;
}

std::uint16_t Player::getTradeCost(ResourceType type, const Player& opponent) const {
    if (this->hasDiscountFor(type)) {
        return 1;
    }


    std::uint16_t baseCost = 2;
    std::uint16_t opponentTax = opponent.countOpponentProduction(type);

    return baseCost + opponentTax;
}

const std::shared_ptr<Player> Player::getOtherPlayer()
{
    return m_otherPlayer.lock();
}

void Player::setOtherPlayer(const std::shared_ptr<Player>& otherPlayer)
{
    m_otherPlayer = otherPlayer;
}

const std::shared_ptr<std::vector<std::shared_ptr<Card>>> Player::getDiscardPile()
{
    return m_discardPile;
}

void Player::setDiscardPile(const std::shared_ptr<std::vector<std::shared_ptr<Card>>>& discardPile)
{
    m_discardPile = discardPile;
}

bool Player::hasChainId(std::uint16_t linkId) const
{
    if (linkId == 0) return false;

    auto ownsBuildingInList = [&](const std::vector<Building>& buildingList) {
        for (const auto& building : buildingList) {
            if (building.getId() == linkId) return true;
        }
        return false;
    };

    if (ownsBuildingInList(m_brownBuildings)) return true;
    if (ownsBuildingInList(m_greyBuildings)) return true;
    if (ownsBuildingInList(m_blueBuildings)) return true;
    if (ownsBuildingInList(m_greenBuildings)) return true;
    if (ownsBuildingInList(m_yellowBuildings)) return true;
    if (ownsBuildingInList(m_redBuildings)) return true;
    if (ownsBuildingInList(m_purpleBuildings)) return true;

    return false;
}

std::uint16_t Player::getConstructionCost(const Building& building) const {
    if (hasChainId(building.getCost().getLink())) {
        return 0;
    }

    std::uint16_t totalCoinsNeeded = building.getCost().getCostCoins();
    std::vector<ResourceType> resourcesNeeded = building.getCost().getCostResources();

    std::uint16_t availableWood = m_wood;
    std::uint16_t availableStone = m_stone;
    std::uint16_t availableClay = m_clay;
    std::uint16_t availableGlass = m_glass;
    std::uint16_t availablePapyrus = m_papyrus;

    for (const auto& resource : resourcesNeeded) {
        bool playerHasResource = false;

        switch (resource) {
        case ResourceType::WOOD:
            if (availableWood > 0) { availableWood--; playerHasResource = true; }
            break;
        case ResourceType::STONE:
            if (availableStone > 0) { availableStone--; playerHasResource = true; }
            break;
        case ResourceType::CLAY:
            if (availableClay > 0) { availableClay--; playerHasResource = true; }
            break;
        case ResourceType::GLASS:
            if (availableGlass > 0) { availableGlass--; playerHasResource = true; }
            break;
        case ResourceType::PAPYRUS:
            if (availablePapyrus > 0) { availablePapyrus--; playerHasResource = true; }
            break;
        }

        if (!playerHasResource) {
            if (auto opponent = m_otherPlayer.lock()) {
                totalCoinsNeeded += getTradeCost(resource, *opponent);
            }
            else {
                totalCoinsNeeded += 2; 
            }
        }
    }

    return totalCoinsNeeded;
}