export module cardsLoader;
import card;
import Building;
import buildingResource;
import std;

export std::vector<std::shared_ptr<Card>> loadAgeIDeck() {
    /*using std::make_unique;
    using std::vector;
    using std::string;*/
    std::vector<std::shared_ptr<Card>> out;

    // BROWN CARDS
    {
        std::vector<Card::Effect> effects = { Card::Effect::addResource };
        Card::Cost cost{ 0, std::vector<ResourceType>{}, 0 };
        std::string name = "Lumber Yard";
        uint8_t id = 1;
        uint8_t vp = 0;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEI;
        auto color = Building::Color::BROWN;
        std::vector<ResourceType> resources = { ResourceType::WOOD };
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        std::vector<Card::Effect> effects = {Card::Effect::addResource};
        Card::Cost cost{ 0, std::vector<ResourceType>{}, 1 };
        std::string name = "Logging Camp";
        uint8_t id = 2;
        uint8_t vp = 0;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEI;
        auto color = Building::Color::BROWN;
        std::vector<ResourceType> resources = { ResourceType::WOOD };
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        std::vector<Card::Effect> effects = { Card::Effect::addResource };
        Card::Cost cost{ 0, std::vector<ResourceType>{}, 0 };
        std::string name = "Clay Pool";
        uint8_t id = 4;
        uint8_t vp = 0;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEI;
        auto color = Building::Color::BROWN;
        std::vector<ResourceType> resources = { ResourceType::CLAY };
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        std::vector<Card::Effect> effects = { Card::Effect::addResource };
        Card::Cost cost{ 0, std::vector<ResourceType>{}, 1 };
        std::string name = "Clay Pit";
        uint8_t id = 5;
        uint8_t vp = 0;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEI;
        auto color = Building::Color::BROWN;
        std::vector<ResourceType> resources = { ResourceType::CLAY };
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        std::vector<Card::Effect> effects = { Card::Effect::addResource };
        Card::Cost cost{ 0, std::vector<ResourceType>{}, 0 };
        std::string name = "Quarry";
        uint8_t id = 7;
        uint8_t vp = 0;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEI;
        auto color = Building::Color::BROWN;
        std::vector<ResourceType> resources = { ResourceType::STONE };
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        std::vector<Card::Effect> effects = { Card::Effect::addResource };
        Card::Cost cost{ 0, std::vector<ResourceType>{}, 1 };
        std::string name = "Stone Pit";
        uint8_t id = 8;
        uint8_t vp = 0;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEI;
        auto color = Building::Color::BROWN;
        std::vector<ResourceType> resources = { ResourceType::STONE };
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }

    // GREY CARDS

    {
        std::vector<Card::Effect> effects = { Card::Effect::addResource };
        Card::Cost cost{ 0, std::vector<ResourceType>{}, 1 };
        std::string name = "Glassworks";
        uint8_t id = 10;
        uint8_t vp = 0;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEI;
        auto color = Building::Color::GREY;
        std::vector<ResourceType> resources = { ResourceType::GLASS };
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        std::vector<Card::Effect> effects = { Card::Effect::addResource };
        Card::Cost cost{ 0, std::vector<ResourceType>{}, 1 };
        std::string name = "Press";
        uint8_t id = 12;
        uint8_t vp = 0;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEI;
        auto color = Building::Color::GREY;
        std::vector<ResourceType> resources = { ResourceType::PAPYRUS };
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }

    // RED CARDS

    {
        std::vector<Card::Effect> effects = { Card::Effect::addShields };
        Card::Cost cost{ 0, std::vector<ResourceType>{}, 0 };
        std::string name = "Guard Tower";
        uint8_t id = 14;
        uint8_t vp = 0;
        uint8_t shields = 1;
        uint8_t coins = 0;
        auto age = Building::Age::AGEI;
        auto color = Building::Color::RED;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        // must connect to horse breeders
        std::vector<Card::Effect> effects = { Card::Effect::addShields };
        Card::Cost cost{ 0, std::vector<ResourceType>{ ResourceType::WOOD }, 0 };
        std::string name = "Stable";
        uint8_t id = 15;
        uint8_t vp = 0;
        uint8_t shields = 1;
        uint8_t coins = 0;
        auto age = Building::Age::AGEI;
        auto color = Building::Color::RED;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        // must connect to barracks
        std::vector<Card::Effect> effects = { Card::Effect::addShields };
        Card::Cost cost{ 0, std::vector<ResourceType>{ ResourceType::CLAY }, 0 };
        std::string name = "Garrison";
        uint8_t id = 16;
        uint8_t vp = 0;
        uint8_t shields = 1;
        uint8_t coins = 0;
        auto age = Building::Age::AGEI;
        auto color = Building::Color::RED;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        // must connect to Fortifications
        std::vector<Card::Effect> effects = { Card::Effect::addShields };
        Card::Cost cost{ 0, std::vector<ResourceType>{}, 2 };
        std::string name = "Palisade";
        uint8_t id = 17;
        uint8_t vp = 0;
        uint8_t shields = 1;
        uint8_t coins = 0;
        auto age = Building::Age::AGEI;
        auto color = Building::Color::RED;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    // GREEN CARDS

    {
        std::vector<Card::Effect> effects = { Card::Effect::addScientificSymbol, Card::Effect::addVictoryPoints };
        Card::Cost cost{ 0, std::vector<ResourceType>{ResourceType::PAPYRUS}, 0 };
        std::string name = "Workshop";
        uint8_t id = 28;
        uint8_t vp = 1;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEI;
        auto color = Building::Color::GREEN;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = Building::ScientificSymbol::SETSQUARE;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        std::vector<Card::Effect> effects = { Card::Effect::addScientificSymbol, Card::Effect::addVictoryPoints };
        Card::Cost cost{ 0, std::vector<ResourceType>{ResourceType::GLASS}, 0 };
        std::string name = "Apothecary";
        uint8_t id = 29;
        uint8_t vp = 1;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEI;
        auto color = Building::Color::GREEN;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = Building::ScientificSymbol::WHEEL;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    
    // must connect to library
    {
        std::vector<Card::Effect> effects = { Card::Effect::addScientificSymbol};
        Card::Cost cost{ 0, std::vector<ResourceType>{}, 2 };
        std::string name = "Scriptorium";
        uint8_t id = 30;
        uint8_t vp = 0;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEI;
        auto color = Building::Color::GREEN;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = Building::ScientificSymbol::FEATHER;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }

    // must connect to dispensary
    {
        std::vector<Card::Effect> effects = { Card::Effect::addScientificSymbol };
        Card::Cost cost{ 0, std::vector<ResourceType>{}, 2 };
        std::string name = "Pharmacist";
        uint8_t id = 31;
        uint8_t vp = 0;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEI;
        auto color = Building::Color::GREEN;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = Building::ScientificSymbol::BOWL;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }

    // YELLOW CARDS

    {
        std::vector<Card::Effect> effects = { Card::Effect::oneCoinStone };
        Card::Cost cost{ 0, std::vector<ResourceType>{}, 3 };
        std::string name = "Stone Reserve";
        uint8_t id = 40;
        uint8_t vp = 0;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEI;
        auto color = Building::Color::YELLOW;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        std::vector<Card::Effect> effects = { Card::Effect::oneCoinClay };
        Card::Cost cost{ 0, std::vector<ResourceType>{}, 3 };
        std::string name = "Clay Reserve";
        uint8_t id = 41;
        uint8_t vp = 0;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEI;
        auto color = Building::Color::YELLOW;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        std::vector<Card::Effect> effects = { Card::Effect::oneCoinWood };
        Card::Cost cost{ 0, std::vector<ResourceType>{}, 3 };
        std::string name = "Wood Reserve";
        uint8_t id = 42;
        uint8_t vp = 0;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEI;
        auto color = Building::Color::YELLOW;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }

    // must connect to lighthouse
    {
        std::vector<Card::Effect> effects = { Card::Effect::addCoins };
        Card::Cost cost{ 0, std::vector<ResourceType>{}, 0 };
        std::string name = "Tavern";
        uint8_t id = 43;
        uint8_t vp = 0;
        uint8_t shields = 0;
        uint8_t coins = 4;
        auto age = Building::Age::AGEI;
        auto color = Building::Color::YELLOW;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }

    // BLUE CARDS

    // must connect to statue
    {
        std::vector<Card::Effect> effects = { Card::Effect::addVictoryPoints };
        Card::Cost cost{ 0, std::vector<ResourceType>{}, 0 };
        std::string name = "Theater";
        uint8_t id = 53;
        uint8_t vp = 3;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEI;
        auto color = Building::Color::YELLOW;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }

    // must connect to temple
    {
        std::vector<Card::Effect> effects = { Card::Effect::addVictoryPoints };
        Card::Cost cost{ 0, std::vector<ResourceType>{}, 0 };
        std::string name = "Altar";
        uint8_t id = 54;
        uint8_t vp = 3;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEI;
        auto color = Building::Color::YELLOW;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }

    // must connect to aqueduct
    {
        std::vector<Card::Effect> effects = { Card::Effect::addVictoryPoints };
        Card::Cost cost{ 0, std::vector<ResourceType>{ResourceType::STONE}, 0 };
        std::string name = "Baths";
        uint8_t id = 55;
        uint8_t vp = 3;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEI;
        auto color = Building::Color::YELLOW;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }

    // Add more cards/buildings here...
    return out;
}