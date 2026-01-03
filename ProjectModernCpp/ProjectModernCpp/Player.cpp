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
m_shields(0),
m_wood(0),
m_stone(0),
m_clay(0),
m_glass(0),
m_papyrus(0)
{
    for (uint16_t i = 0; i < 6; i++)
        m_scientificPoints.push_back(0);
    
	m_tradeDiscounts[ResourceType::WOOD] = false;
	m_tradeDiscounts[ResourceType::STONE] = false;
	m_tradeDiscounts[ResourceType::CLAY] = false;
	m_tradeDiscounts[ResourceType::GLASS] = false;
	m_tradeDiscounts[ResourceType::PAPYRUS] = false;
}

//Player::Player(std::string name,  uint16_t startCoin1Amount,
//    uint16_t startCoin3Amount, uint16_t startCoin6Amount): m_name(std::move(name)),
//    m_coins(7),
//    m_victoryPoints(0),
//    m_shields(0),
//    m_wood(0),
//    m_stone(0),
//    m_clay(0),
//    m_glass(0),
//    m_papyrus(0)
//{
//    for (uint16_t i = 0; i < 7; i++)
//        m_scientificPoints.push_back(0);
//}

Player::Player(const Player& other) : m_name(other.m_name),
m_coins(other.m_coins),
m_victoryPoints(other.m_victoryPoints),
m_shields(other.m_shields),
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
m_progressTokens(other.m_progressTokens),
m_tradeDiscounts(other.m_tradeDiscounts)
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

    std::uint16_t totalCost = getConstructionCost(building);
    
    std::uint16_t cardBaseCost = building.getCost().getCostCoins();

    std::uint16_t tradeSpent = 0;
    if (totalCost > cardBaseCost) {
        tradeSpent = totalCost - cardBaseCost;
    }

    if (tradeSpent > 0) {
        if (auto opponent = m_otherPlayer.lock()) {
            if (opponent->m_hasEconomyProgressToken) {
                opponent->addCoin(tradeSpent);
            }
        }
    }

    if (totalCost == 0 && building.getCost().getLink() != 0 && hasChainId(building.getCost().getLink()) && m_hasUrbanismProgressToken) {
        addCoin(4);
    }

    if (totalCost > 0) {
        payCoin(totalCost);
    }

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
        if (m_hasStrategyProgressToken) {
            addShields(1);
        }
        break;
    case Building::Color::PURPLE:
        m_purpleBuildings.push_back(building);
        break;
    }

    std::vector<ResourceType> bResources = building.getResources();
    for (auto resource : bResources)
    {
        switch (resource)
        {
        case ResourceType::WOOD:    m_wood++; break;
        case ResourceType::STONE:   m_stone++; break;
        case ResourceType::CLAY:    m_clay++; break;
        case ResourceType::GLASS:   m_glass++; break;
        case ResourceType::PAPYRUS: m_papyrus++; break;
        }
        m_productions[resource]++;
    }
    addVictoryPoints(building.getVictoryPoints());
}

void Player::discardBuilding(Building::Color color, std::uint16_t id)
{
    Building found;
    std::vector<Building>::iterator it;
    switch(color)
    {
    case Building::Color::GREY:
        it = std::find_if(m_greyBuildings.begin(), m_greyBuildings.end(), [id](const Building& b) { return b.getId() == id; });
        if ( it == m_greyBuildings.end()) {
            std::cout << "building not found\n";
            return;
        }
        found = std::move(*it);
        m_greyBuildings.erase(it);
		m_discardPile->insert({ id, std::make_shared<Building>(found) });
    case Building::Color::BROWN:
        it = std::find_if(m_brownBuildings.begin(), m_brownBuildings.end(), [id](const Building& b) { return b.getId() == id; });
        if ( it == m_brownBuildings.end()) {
            std::cout << "building not found\n";
            return;
        }
        found = std::move(*it);
        m_brownBuildings.erase(it);
        m_discardPile->insert({ id, std::make_shared<Building>(found) });
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

uint16_t Player::getShields() const noexcept { return m_shields; }
void Player::addShields(uint16_t shields) noexcept
{
    m_shields += shields;
}


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

void Player::removeResources(const std::vector<ResourceType>& resources)
{
    for (const auto& resource : resources) {
        switch (resource)
        {
        case ResourceType::WOOD:
        {
            m_wood--;
            break;
        }
        case ResourceType::STONE:
        {
            m_stone--;
            break;
        }
        case ResourceType::CLAY:
        {
            m_clay--;
            break;
        }
        case ResourceType::GLASS:
        {
            m_glass--;
            break;
        }
        case ResourceType::PAPYRUS:
        {
            m_papyrus--;
            break;
        }
        }
	}
}

std::unordered_map<ResourceType, std::uint16_t> Player::getProductions() const noexcept
{
    return m_productions;
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
const std::vector<Player::ProgressToken> Player::getProgressTokens() const
{
    return m_progressTokens;
}
void Player::addProgressToken(const ProgressToken& token)
{
	m_progressTokens.push_back(token);
}
void Player::applyEffects()
{
    std::shared_ptr<Player> aux(this);
    for (auto progresToken : m_progressTokens)
        progresToken.applyEffect(aux);
}
void Player::ProgressToken::applyEffect(std::shared_ptr<Player> player)
{
    m_effect(player);
}

Player::ProgressToken Player::ProgressToken::agricultureToken([](std::shared_ptr<Player> player) {
    player->addCoin(6);
    player->addVictoryPoints(4);
    }, true);

Player::ProgressToken Player::ProgressToken::lawToken([](std::shared_ptr<Player> player) {
    std::vector<uint16_t> vect = player->getScientificPoints();
    for(uint16_t i=0;i<vect.size();i++)
        if (vect[i] != 2)
        {
            player->addScientificPoint((Building::ScientificSymbol)i);
            break;
        }
    }, true);

Player::ProgressToken Player::ProgressToken::philosphyToken([](std::shared_ptr<Player> player) {
    player->addVictoryPoints(7);
    }, true);

Player::ProgressToken Player::ProgressToken::mathematicsToken([](std::shared_ptr<Player> player) {
    player->addVictoryPoints(player->getProgressTokens().size()*3);
    }, true);

Player::ProgressToken Player::ProgressToken::economyToken([](std::shared_ptr<Player> player) {
    player->m_hasEconomyProgressToken = 1;
    }, false);

Player::ProgressToken Player::ProgressToken::masonryToken([](std::shared_ptr<Player> player) {
    player->m_hasMasonryProgressToken = 1;
    }, false);

Player::ProgressToken Player::ProgressToken::strategyToken([](std::shared_ptr<Player> player) {
    player->m_hasStrategyProgressToken = 1;
    }, false);

Player::ProgressToken Player::ProgressToken::theologyToken([](std::shared_ptr<Player> player) {
    player->m_hasTheologyProgressToken = 1;
    }, false);

Player::ProgressToken Player::ProgressToken::urbanismToken([](std::shared_ptr<Player> player) {
    player->m_hasUrbanismProgressToken = 1;
    player->addCoin(6);
    }, false);

Player::ProgressToken Player::ProgressToken::architectureToken([](std::shared_ptr<Player> player) {
    player->m_hasArchitectureProgressToken = 1;
    }, false);

Player::ProgressToken::ProgressToken(std::function<void(std::shared_ptr<Player> player)> effect, bool isOneTime)
{
    this->m_effect = effect;
    this->m_isOneTime = isOneTime;
}

bool Player::hasDiscountFor(ResourceType type) const
{
    /*std::uint8_t requiredId = 0;

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
    }*/
	return m_tradeDiscounts.at(type);
}

std::uint16_t Player::countOpponentProduction(ResourceType type) {
    std::uint16_t count=0;
     Player other= * this->getOtherPlayer();
     switch (type)
     {
     case ResourceType::WOOD:
         return other.getWood();
     case ResourceType::CLAY:
         return other.getClay();
     case ResourceType::GLASS:
         return other.getGlass();
     case ResourceType::PAPYRUS:
         return other.getPapyrus();
     case ResourceType::STONE:
         return other.getStone();
     }
     return count;
}

std::uint16_t Player::getTradeCost(ResourceType type,  Player& opponent) {
    if (this->hasDiscountFor(type)) {
        return 1;
    }


    std::uint16_t baseCost = 2;
    std::uint16_t opponentTax = opponent.countOpponentProduction(type);

    return baseCost + opponentTax;
}

std::shared_ptr<Player> Player::getOtherPlayer()
{
    return m_otherPlayer.lock();
}

void Player::setOtherPlayer(const std::shared_ptr<Player>& otherPlayer)
{
    m_otherPlayer = otherPlayer;
}

const std::shared_ptr<std::unordered_map<uint16_t, std::shared_ptr<Building>>> Player::getDiscardPile() const
{
    return m_discardPile;
}

void Player::setDiscardPile(const std::shared_ptr<std::unordered_map<uint16_t, std::shared_ptr<Building>>>& discardPile)
{
    m_discardPile = discardPile;
}

void Player::removeCardFromDiscardPile(uint16_t cardId)
{
	m_discardPile->erase(cardId);
}

std::unordered_map<ResourceType, bool> Player::getTradeDiscounts() const noexcept
{
    return m_tradeDiscounts;
}

void Player::addTradeDiscount(ResourceType type) noexcept
{
	m_tradeDiscounts[type] = true;
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

std::uint16_t Player::getConstructionCost(const Building& building) {
    if (hasChainId(building.getCost().getLink())) {
        return 0;
    }

    std::uint16_t totalCoinsNeeded = building.getCost().getCostCoins();
    std::vector<ResourceType> resourcesNeeded = building.getCost().getCostResources();

    if (building.getColor() == Building::Color::BLUE && m_hasMasonryProgressToken) {
        applyTokenDiscount(resourcesNeeded, 2);
    }

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

bool Player::canBuild(const Building& building) 
{
    std::uint16_t cost = getConstructionCost(building);

    if (m_coins >= cost) {
        return true;
    }

    return false;
}

bool Player::canBuildWonder(const Card& wonder)
{
    std::uint16_t totalCoinsNeeded = wonder.getCost().getCostCoins();
    std::vector<ResourceType> resourcesNeeded = wonder.getCost().getCostResources();

    if (m_hasArchitectureProgressToken) {
        applyTokenDiscount(resourcesNeeded, 2);
    }

    std::uint16_t availableWood = m_wood;
    std::uint16_t availableStone = m_stone;
    std::uint16_t availableClay = m_clay;
    std::uint16_t availableGlass = m_glass;
    std::uint16_t availablePapyrus = m_papyrus;

    for (const auto& resource : resourcesNeeded) {
        bool playerHasResource = false;
        switch (resource) {
        case ResourceType::WOOD: if (availableWood > 0) { availableWood--; playerHasResource = true; } break;
        case ResourceType::STONE: if (availableStone > 0) { availableStone--; playerHasResource = true; } break;
        case ResourceType::CLAY: if (availableClay > 0) { availableClay--; playerHasResource = true; } break;
        case ResourceType::GLASS: if (availableGlass > 0) { availableGlass--; playerHasResource = true; } break;
        case ResourceType::PAPYRUS: if (availablePapyrus > 0) { availablePapyrus--; playerHasResource = true; } break;
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

    return m_coins >= totalCoinsNeeded;
}

void Player::buildWonder(std::uint16_t wonderId, std::shared_ptr<Building> ageCardUsed)
{
    for (auto& wonderPair : m_wonders) {
        if (wonderPair.first->getId() == wonderId) {
            wonderPair.second = ageCardUsed;
            addVictoryPoints(wonderPair.first->getVictoryPoints());
            addShields(wonderPair.first->getShields());
            return;
        }
    }
}


void Player::applyTokenDiscount(std::vector<ResourceType>& resourcesNeeded, int discountAmount) const {
    auto tmpWood = m_wood;
    auto tmpStone = m_stone;
    auto tmpClay = m_clay;
    auto tmpGlass = m_glass;
    auto tmpPapyrus = m_papyrus;

    std::vector<int> missingIndices;

    for (size_t i = 0; i < resourcesNeeded.size(); ++i) {
        bool has = false;
        switch (resourcesNeeded[i]) {
        case ResourceType::WOOD: if (tmpWood > 0) { tmpWood--; has = true; } break;
        case ResourceType::STONE: if (tmpStone > 0) { tmpStone--; has = true; } break;
        case ResourceType::CLAY: if (tmpClay > 0) { tmpClay--; has = true; } break;
        case ResourceType::GLASS: if (tmpGlass > 0) { tmpGlass--; has = true; } break;
        case ResourceType::PAPYRUS: if (tmpPapyrus > 0) { tmpPapyrus--; has = true; } break;
        }
        if (!has) missingIndices.push_back(i);
    }

    int removedCount = 0;


    for (int i = missingIndices.size() - 1; i >= 0 && removedCount < discountAmount; --i) {
        resourcesNeeded.erase(resourcesNeeded.begin() + missingIndices[i]);
        removedCount++;
    }

    while (removedCount < discountAmount && !resourcesNeeded.empty()) {
        resourcesNeeded.pop_back();
        removedCount++;
    }
}

uint16_t Player::getCoinsPoints() const noexcept {
    return m_coins / 3;
}

uint16_t Player::getBluePoints() const noexcept {
    uint16_t bluePoints = 0;
    for (const auto& building : m_blueBuildings) {
        bluePoints += building.getVictoryPoints();
    }
    return bluePoints;
}

uint16_t Player::getFinalScore(uint16_t militaryPoints) const noexcept {
    //militaryPoints = cate puncte de victorie ofera pozitia pionului pentru Player
    return m_victoryPoints + getCoinsPoints() + militaryPoints;
}

std::uint16_t Player::getBuildingCount(Building::Color color) const noexcept
{
    switch (color)
    {
    case Building::Color::BROWN:
        return static_cast<uint16_t>(m_brownBuildings.size());
    case Building::Color::GREY:
        return static_cast<uint16_t>(m_greyBuildings.size());
    case Building::Color::BLUE:
        return static_cast<uint16_t>(m_blueBuildings.size());
    case Building::Color::GREEN:
        return static_cast<uint16_t>(m_greenBuildings.size());
    case Building::Color::YELLOW:
        return static_cast<uint16_t>(m_yellowBuildings.size());
    case Building::Color::RED:
        return static_cast<uint16_t>(m_redBuildings.size());
    case Building::Color::PURPLE:
        return static_cast<uint16_t>(m_purpleBuildings.size());
    default:
        return 0;
    }
}

std::uint16_t Player::getConstructedWondersCount() const noexcept
{
    std::uint16_t count = 0;
    for (const auto& wonderPair : m_wonders)
    {
        if (wonderPair.second.has_value()) {
            count++;
        }
    }
    return count;
}