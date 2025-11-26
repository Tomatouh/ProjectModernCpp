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
export std::vector<std::shared_ptr<Card>> loadAgeIIDeck() {
    std::vector<std::shared_ptr<Card>> out;

    // BROWN CARDS
    {
        std::vector<Card::Effect> effects = { Card::Effect::addResource };
        Card::Cost cost{ 0, std::vector<ResourceType>{}, 2 };
        std::string name = "Sawmill";
        uint8_t id = 3;
        uint8_t vp = 0;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::BROWN;
        std::vector<ResourceType> resources = { ResourceType::WOOD, ResourceType::WOOD };
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        std::vector<Card::Effect> effects = { Card::Effect::addResource };
        Card::Cost cost{ 0, std::vector<ResourceType>{}, 2 };
        std::string name = "Brickyard";
        uint8_t id = 6;
        uint8_t vp = 0;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::BROWN;
        std::vector<ResourceType> resources = { ResourceType::CLAY, ResourceType::CLAY };
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        std::vector<Card::Effect> effects = { Card::Effect::addResource };
        Card::Cost cost{ 0, std::vector<ResourceType>{}, 2 };
        std::string name = "Shelf Quarry";
        uint8_t id = 9;
        uint8_t vp = 0;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::BROWN;
        std::vector<ResourceType> resources = { ResourceType::STONE, ResourceType::STONE };
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }

    // GREY CARDS

    {
        std::vector<Card::Effect> effects = { Card::Effect::addResource };
        Card::Cost cost{ 0, std::vector<ResourceType>{}, 0 };
        std::string name = "Glass Blower";
        uint8_t id = 11;
        uint8_t vp = 0;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::GREY;
        std::vector<ResourceType> resources = { ResourceType::GLASS };
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
    std::vector<Card::Effect> effects = { Card::Effect::addResource };
    Card::Cost cost{ 0, std::vector<ResourceType>{}, 0 };
    std::string name = "Drying Room";
    uint8_t id = 13;
    uint8_t vp = 0;
    uint8_t shields = 0;
    uint8_t coins = 0;
    auto age = Building::Age::AGEII;
    auto color = Building::Color::GREY;
    std::vector<ResourceType> resources = { ResourceType::PAPYRUS };
    std::optional<Building::ScientificSymbol> sym = std::nullopt;

    out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }

    // RED CARDS

    {
        std::vector<Card::Effect> effects = { Card::Effect::addShields };
        Card::Cost cost{ 15, std::vector<ResourceType>{ ResourceType::CLAY, ResourceType::WOOD}, 0 };
        std::string name = "Horse Breeders";
        uint8_t id = 18;
        uint8_t vp = 0;
        uint8_t shields = 1;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::RED;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        std::vector<Card::Effect> effects = { Card::Effect::addShields };
        Card::Cost cost{ 16, std::vector<ResourceType>{}, 3 };
        std::string name = "Barracks";
        uint8_t id = 19;
        uint8_t vp = 0;
        uint8_t shields = 1;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::RED;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        std::vector<Card::Effect> effects = { Card::Effect::addShields };
        Card::Cost cost{ 0, std::vector<ResourceType>{ ResourceType::STONE, ResourceType::STONE}, 0 };
        std::string name = "Walls";
        uint8_t id = 20;
        uint8_t vp = 0;
        uint8_t shields = 2;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::RED;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }

    // must connect to siege workshop
    {
        std::vector<Card::Effect> effects = { Card::Effect::addShields };
        Card::Cost cost{ 0, std::vector<ResourceType>{ ResourceType::STONE, ResourceType::WOOD, ResourceType::PAPYRUS}, 0 };
        std::string name = "Archery Range";
        uint8_t id = 21;
        uint8_t vp = 0;
        uint8_t shields = 2;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::RED;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }

    // must connect to circus
    {
        std::vector<Card::Effect> effects = { Card::Effect::addShields };
        Card::Cost cost{ 0, std::vector<ResourceType>{ ResourceType::CLAY, ResourceType::CLAY, ResourceType::GLASS}, 0 };
        std::string name = "Parade Ground";
        uint8_t id = 22;
        uint8_t vp = 0;
        uint8_t shields = 2;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::RED;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }

    // GREEN CARDS

    {
        std::vector<Card::Effect> effects = { Card::Effect::addScientificSymbol, Card::Effect::addVictoryPoints };
        Card::Cost cost{ 30, std::vector<ResourceType>{ ResourceType::STONE, ResourceType::WOOD, ResourceType::GLASS}, 0 };
        std::string name = "Library";
        uint8_t id = 32;
        uint8_t vp = 2;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::GREEN;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = Building::ScientificSymbol::FEATHER;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        std::vector<Card::Effect> effects = { Card::Effect::addScientificSymbol, Card::Effect::addVictoryPoints };
        Card::Cost cost{ 31, std::vector<ResourceType>{ ResourceType::CLAY, ResourceType::CLAY, ResourceType::STONE}, 0 };
        std::string name = "Dispensary";
        uint8_t id = 33;
        uint8_t vp = 2;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::GREEN;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = Building::ScientificSymbol::BOWL;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }

    // must connect to university
    {
        std::vector<Card::Effect> effects = { Card::Effect::addScientificSymbol, Card::Effect::addVictoryPoints };
        Card::Cost cost{ 0, std::vector<ResourceType>{ ResourceType::WOOD, ResourceType::PAPYRUS, ResourceType::PAPYRUS}, 0 };
        std::string name = "School";
        uint8_t id = 34;
        uint8_t vp = 1;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::GREEN;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = Building::ScientificSymbol::WHEEL;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }

    // must connect to observatory
    {
        std::vector<Card::Effect> effects = { Card::Effect::addScientificSymbol, Card::Effect::addVictoryPoints };
        Card::Cost cost{ 0, std::vector<ResourceType>{ ResourceType::WOOD, ResourceType::PAPYRUS, ResourceType::PAPYRUS}, 0 };
        std::string name = "Laboratory";
        uint8_t id = 35;
        uint8_t vp = 1;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::GREEN;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = Building::ScientificSymbol::SETSQUARE;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }

    // YELLOW CARDS

    {
        std::vector<Card::Effect> effects = { Card::Effect::ChooseResource };
        Card::Cost cost{ 0, std::vector<ResourceType>{ ResourceType::CLAY }, 3 };
        std::string name = "Forum";
        uint8_t id = 44;
        uint8_t vp = 0;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::YELLOW;
        std::vector<ResourceType> resources = {ResourceType::GLASS, ResourceType::PAPYRUS};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        std::vector<Card::Effect> effects = { Card::Effect::ChooseResource };
        Card::Cost cost{ 0, std::vector<ResourceType>{ ResourceType::GLASS, ResourceType::PAPYRUS }, 2 };
        std::string name = "Caravansery";
        uint8_t id = 45;
        uint8_t vp = 0;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::YELLOW;
        std::vector<ResourceType> resources = { ResourceType::WOOD, ResourceType::CLAY, ResourceType::STONE };
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        std::vector<Card::Effect> effects = { Card::Effect::oneCoinPapyrus, Card::Effect::oneCoinGlass };
        Card::Cost cost{ 0, std::vector<ResourceType>{}, 4 };
        std::string name = "Customs House";
        uint8_t id = 46;
        uint8_t vp = 0;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::YELLOW;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }

    // must connect to arena
    {
        std::vector<Card::Effect> effects = { Card::Effect::addCoins };
        Card::Cost cost{ 0, std::vector<ResourceType>{}, 0 };
        std::string name = "Brewery";
        uint8_t id = 47;
        uint8_t vp = 0;
        uint8_t shields = 0;
        uint8_t coins = 6;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::YELLOW;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }

    // BLUE CARDS

    {
        std::vector<Card::Effect> effects = { Card::Effect::addVictoryPoints };
        Card::Cost cost{ 0, std::vector<ResourceType>{ ResourceType::WOOD, ResourceType::WOOD, ResourceType::GLASS }, 0 };
        std::string name = "Courthouse";
        uint8_t id = 56;
        uint8_t vp = 5;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::BLUE;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }

    // must connect to gardens
    {
        std::vector<Card::Effect> effects = { Card::Effect::addVictoryPoints };
        Card::Cost cost{ 53, std::vector<ResourceType>{ ResourceType::CLAY, ResourceType::CLAY }, 0 };
        std::string name = "Satue";
        uint8_t id = 57;
        uint8_t vp = 4;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::BLUE;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }

    // must connect to pantheon
    {
        std::vector<Card::Effect> effects = { Card::Effect::addVictoryPoints };
        Card::Cost cost{ 54, std::vector<ResourceType>{ ResourceType::WOOD, ResourceType::PAPYRUS }, 0 };
        std::string name = "Temple";
        uint8_t id = 58;
        uint8_t vp = 4;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::BLUE;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }

    {
        std::vector<Card::Effect> effects = { Card::Effect::addVictoryPoints };
        Card::Cost cost{ 55, std::vector<ResourceType>{ ResourceType::STONE, ResourceType::STONE, ResourceType::STONE }, 0 };
        std::string name = "Aqueduct";
        uint8_t id = 59;
        uint8_t vp = 5;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::BLUE;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }

    // must connect to senate
    {
        std::vector<Card::Effect> effects = { Card::Effect::addVictoryPoints };
        Card::Cost cost{ 0, std::vector<ResourceType>{ ResourceType::STONE, ResourceType::WOOD }, 0 };
        std::string name = "Rostrum";
        uint8_t id = 60;
        uint8_t vp = 4;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::BLUE;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }

    return out;
}
export std::vector<std::shared_ptr<Card>> loadAgeIIIDeck() {
    std::vector<std::shared_ptr<Card>> out;

    // RED CARDS

    {
        std::vector<Card::Effect> effects = { Card::Effect::addShields };
        Card::Cost cost{ 17, std::vector<ResourceType>{ ResourceType::STONE, ResourceType::STONE, ResourceType::CLAY, ResourceType::PAPYRUS}, 0 };
        std::string name = "Fortifications";
        uint8_t id = 23;
        uint8_t vp = 0;
        uint8_t shields = 2;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::RED;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;
        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
    std::vector<Card::Effect> effects = { Card::Effect::addShields };
    Card::Cost cost{ 21, std::vector<ResourceType>{ ResourceType::WOOD, ResourceType::WOOD, ResourceType::WOOD, ResourceType::GLASS}, 0 };
    std::string name = "Siege Workshop";
    uint8_t id = 24;
    uint8_t vp = 0;
    uint8_t shields = 2;
    uint8_t coins = 0;
    auto age = Building::Age::AGEII;
    auto color = Building::Color::RED;
    std::vector<ResourceType> resources = {};
    std::optional<Building::ScientificSymbol> sym = std::nullopt;
    out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        std::vector<Card::Effect> effects = { Card::Effect::addShields };
        Card::Cost cost{ 22, std::vector<ResourceType>{ ResourceType::CLAY, ResourceType::CLAY, ResourceType::STONE, ResourceType::STONE}, 0 };
        std::string name = "Circus";
        uint8_t id = 25;
        uint8_t vp = 0;
        uint8_t shields = 2;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::RED;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;
        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        std::vector<Card::Effect> effects = { Card::Effect::addShields };
        Card::Cost cost{ 0, std::vector<ResourceType>{ ResourceType::CLAY, ResourceType::CLAY, ResourceType::CLAY, ResourceType::WOOD, ResourceType::WOOD}, 0 };
        std::string name = "Arsenal";
        uint8_t id = 26;
        uint8_t vp = 0;
        uint8_t shields = 3;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::RED;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;
        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        std::vector<Card::Effect> effects = { Card::Effect::addShields };
        Card::Cost cost{ 0, std::vector<ResourceType>{}, 8 };
        std::string name = "Siege Workshop";
        uint8_t id = 27;
        uint8_t vp = 0;
        uint8_t shields = 3;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::RED;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;
        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }

    // GREEN CARDS

    {
        std::vector<Card::Effect> effects = { Card::Effect::addScientificSymbol, Card::Effect::addVictoryPoints };
        Card::Cost cost{ 0, std::vector<ResourceType>{ ResourceType::STONE, ResourceType::WOOD, ResourceType::GLASS, ResourceType::GLASS}, 0 };
        std::string name = "Academy";
        uint8_t id = 36;
        uint8_t vp = 3;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::GREEN;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = Building::ScientificSymbol::SUNDIAL;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        std::vector<Card::Effect> effects = { Card::Effect::addScientificSymbol, Card::Effect::addVictoryPoints };
        Card::Cost cost{ 0, std::vector<ResourceType>{ ResourceType::WOOD, ResourceType::WOOD, ResourceType::GLASS, ResourceType::PAPYRUS}, 0 };
        std::string name = "Study";
        uint8_t id = 37;
        uint8_t vp = 3;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::GREEN;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = Building::ScientificSymbol::SUNDIAL;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        std::vector<Card::Effect> effects = { Card::Effect::addScientificSymbol, Card::Effect::addVictoryPoints };
        Card::Cost cost{ 34, std::vector<ResourceType>{ ResourceType::CLAY, ResourceType::GLASS, ResourceType::PAPYRUS}, 0 };
        std::string name = "University";
        uint8_t id = 38;
        uint8_t vp = 2;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::GREEN;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = Building::ScientificSymbol::GLOBE;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        std::vector<Card::Effect> effects = { Card::Effect::addScientificSymbol, Card::Effect::addVictoryPoints };
        Card::Cost cost{ 35, std::vector<ResourceType>{ ResourceType::STONE, ResourceType::PAPYRUS, ResourceType::PAPYRUS}, 0 };
        std::string name = "Observatory";
        uint8_t id = 39;
        uint8_t vp = 2;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::GREEN;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = Building::ScientificSymbol::GLOBE;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }

    // YELLOW CARDS
    {
        std::vector<Card::Effect> effects = { Card::Effect::threeCoinsPerGrey, Card::Effect::addVictoryPoints };
        Card::Cost cost{ 0, std::vector<ResourceType>{ ResourceType::PAPYRUS, ResourceType::PAPYRUS }, 0 };
        std::string name = "Chamber of Commerce";
        uint8_t id = 48;
        uint8_t vp = 3;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::YELLOW;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        std::vector<Card::Effect> effects = { Card::Effect::twoCoinsPerBrown, Card::Effect::addVictoryPoints };
        Card::Cost cost{ 0, std::vector<ResourceType>{ ResourceType::WOOD, ResourceType::GLASS }, 0 };
        std::string name = "Port";
        uint8_t id = 49;
        uint8_t vp = 3;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::YELLOW;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        std::vector<Card::Effect> effects = { Card::Effect::oneCoinPerRed, Card::Effect::addVictoryPoints };
        Card::Cost cost{ 0, std::vector<ResourceType>{ ResourceType::STONE, ResourceType::STONE, ResourceType::GLASS }, 0 };
        std::string name = "Armory";
        uint8_t id = 50;
        uint8_t vp = 3;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::YELLOW;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        std::vector<Card::Effect> effects = { Card::Effect::oneCoinPerYellow, Card::Effect::addVictoryPoints };
        Card::Cost cost{ 43, std::vector<ResourceType>{ ResourceType::CLAY, ResourceType::CLAY, ResourceType::GLASS }, 0 };
        std::string name = "Lighthouse";
        uint8_t id = 51;
        uint8_t vp = 3;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::YELLOW;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }
    {
        std::vector<Card::Effect> effects = { Card::Effect::twoCoinsPerWonder, Card::Effect::addVictoryPoints };
        Card::Cost cost{ 47, std::vector<ResourceType>{ ResourceType::CLAY, ResourceType::STONE, ResourceType::WOOD }, 0 };
        std::string name = "Arena";
        uint8_t id = 52;
        uint8_t vp = 3;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::YELLOW;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }

    // BLUE CARDS

    {
        std::vector<Card::Effect> effects = { Card::Effect::addVictoryPoints };
        Card::Cost cost{ 0, std::vector<ResourceType>{ ResourceType::CLAY, ResourceType::STONE, ResourceType::WOOD, ResourceType::GLASS, ResourceType::GLASS }, 0 };
        std::string name = "Palace";
        uint8_t id = 56;
        uint8_t vp = 5;
        uint8_t shields = 0;
        uint8_t coins = 0;
        auto age = Building::Age::AGEII;
        auto color = Building::Color::BLUE;
        std::vector<ResourceType> resources = {};
        std::optional<Building::ScientificSymbol> sym = std::nullopt;

        out.push_back(std::make_shared<Building>(effects, cost, name, id, vp, shields, coins, age, color, resources, sym));
    }


    return out;
}
