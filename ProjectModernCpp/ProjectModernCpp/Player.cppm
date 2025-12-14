export module Player;
import <string>;
import <vector>;
import <cstdint>;
import <iostream>;
import <memory>;
import <functional>;
import card;
import Building; // Building trebuie importat pentru a fi folosit in Player
import buildingResource;

export class Player {
public:

    Player();
    explicit Player(std::string name, std::uint16_t startCoin1Amount, std::uint16_t startCoin3Amount, std::uint16_t startCoin6Amount);
    Player(const Player& other);

    const std::string& name() const noexcept;

    void setPlayerName(const std::string_view name);

    // Coin management methods
	void addCoin(std::uint16_t amount) noexcept;

    void payCoin(std::uint16_t amount) noexcept;
    std::uint16_t getCoins() const noexcept;

    void addBuilding(const Building& building); // Modificata pentru a adauga o cladire
    Building discardBuilding(Building::Color color, std::uint8_t id);
    void addWonder(const std::shared_ptr<Card>& wonder);

    // Getters for Buildings, by colour
    const std::vector<Building>& getBrownBuildings() const noexcept;
    const std::vector<Building>& getGreyBuildings() const noexcept;
    const std::vector<Building>& getBlueBuildings() const noexcept;
    const std::vector<Building>& getGreenBuildings() const noexcept;
    const std::vector<Building>& getYellowBuildings() const noexcept;
    const std::vector<Building>& getRedBuildings() const noexcept;
    const std::vector<Building>& getPurpleBuildings() const noexcept;
    const std::vector<std::pair<std::shared_ptr<Card>, std::optional<std::shared_ptr<Building>>>> getWonders() const noexcept;


    uint16_t getVictoryPoints() const noexcept;
    void addVictoryPoints(uint16_t points) noexcept;


    void addResources(const std::vector<ResourceType>& resources);
    void addProduction(const std::vector<ResourceType>& resources);
    


    uint16_t getWood() const noexcept;
    uint16_t getStone() const noexcept;
    uint16_t getClay() const noexcept;
    uint16_t getGlass() const noexcept;
    uint16_t getPapyrus() const noexcept;

    void showStatus(std::ostream& os = std::cout) const;
    void showCards(std::ostream& os = std::cout) const;

    //Functii pentru folosirea punctelor stiintifice
    void addScientificPoint(Building::ScientificSymbol point) noexcept;
    std::vector<uint16_t> getScientificPoints() noexcept;
    //Aplicare efecte speciale ProgressToken
    class ProgressToken {
    public:
        static ProgressToken agricultureToken;
        static ProgressToken architectureToken;
        static ProgressToken economyToken;
        static ProgressToken lawToken;
        static ProgressToken masonryToken;
        static ProgressToken mathematicsToken;
        static ProgressToken philosphyToken;
        static ProgressToken strategyToken;
        static ProgressToken theologyToken;
        static ProgressToken urbanismToken;
        void applyEffect(std::unique_ptr<Player> player);
        ProgressToken(std::function<void(std::unique_ptr<Player> player)> effect, bool isOneTime);
    private:
        std::function<void(std::unique_ptr<Player> player)> m_effect;
        bool m_isOneTime;
    };
    void applyEffects();
    std::vector<ProgressToken> getProgressTokens();

    std::uint16_t getTradeCost(ResourceType type, const Player& opponent) const;

    const std::shared_ptr<Player> getOtherPlayer();
    void setOtherPlayer(const std::shared_ptr<Player>& otherPlayer);
    const std::shared_ptr<std::vector<std::shared_ptr<Card>>> getDiscardPile();
    void setDiscardPile(const std::shared_ptr<std::vector<std::shared_ptr<Card>>>& discardPile);

    bool hasChainId(std::uint16_t linkId) const;

    std::uint16_t getConstructionCost(const Building& building) const;

private:

    std::string m_name;
    uint16_t m_coins;
    uint16_t m_victoryPoints;

    // Resources
    uint16_t m_wood;
    uint16_t m_stone;
    uint16_t m_clay;
    uint16_t m_glass;
    uint16_t m_papyrus;

    // Colectii de cladiri, separate pe culori
    std::vector<Building> m_brownBuildings;
    std::vector<Building> m_greyBuildings;
    std::vector<Building> m_blueBuildings;
    std::vector<Building> m_greenBuildings;
    std::vector<Building> m_yellowBuildings;
    std::vector<Building> m_redBuildings;
    std::vector<Building> m_purpleBuildings;

    // Puncte stiintifice
    std::vector<uint16_t> m_scientificPoints;
    uint16_t m_scientificPointTypeNumber = 0;

    // Progress token, might delete
    std::vector<ProgressToken> m_progressTokens;
    //Memorarea efectelor speciale pe care le poate avea un jucator (ProgressToken)
    bool m_hasEconomyProgressToken = 0;
    bool m_hasMasonryProgressToken = 0;
    bool m_hasStrategyProgressToken = 0;
    bool m_hasTheologyProgressToken = 0;
    bool m_hasUrbanismProgressToken = 0;
    bool m_hasArchitectureProgressToken = 0;
    // Wonders
    std::vector<std::pair<std::shared_ptr<Card>, std::optional<std::shared_ptr<Building>>>> m_wonders;
    // pointer to the other player
    std::weak_ptr<Player> m_otherPlayer;
    // pointer to the discard pile
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> m_discardPile;

    // productions per turn
    std::unordered_map<ResourceType, std::uint16_t> m_productions;

    bool hasDiscountFor(ResourceType type) const;

    std::uint16_t countOpponentProduction(ResourceType type) const;

};