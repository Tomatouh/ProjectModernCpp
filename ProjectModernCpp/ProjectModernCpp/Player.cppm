export module Player;
import <string>;
import <vector>;
import <cstdint>;
import <iostream>;
import <memory>;
import <functional>;
import card;
import Building;
import buildingResource;

export class Player {
public:

    Player();
    //explicit Player(std::string name, std::uint16_t startCoin1Amount, std::uint16_t startCoin3Amount, std::uint16_t startCoin6Amount);
    Player(const Player& other);

    ~Player();

    const std::string& name() const noexcept;

    void setPlayerName(const std::string_view name);

    // Coin management methods
	void addCoin(std::uint16_t amount) noexcept;

    void payCoin(std::uint16_t amount) noexcept;
    std::uint16_t getCoins() const noexcept;

    void addBuilding(const Building& building); // Modificata pentru a adauga o cladire
    void discardBuilding(Building::Color color, std::uint16_t id);
    void addWonder(const std::shared_ptr<Card>& wonder);

    // Getters for Buildings, by colour
	const std::vector<Building>& getAllBuildings() const noexcept;
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

    uint16_t getShields() const noexcept;
    void addShields(uint16_t shields) noexcept;


    void addResources(const std::vector<ResourceType>& resources);
	void removeResources(const std::vector<ResourceType>& resources);

	std::unordered_map<ResourceType, std::uint16_t> getProductions() const noexcept;
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
        void applyEffect(std::shared_ptr<Player> player);
        ProgressToken(std::function<void(std::shared_ptr<Player> player)> effect, bool isOneTime, int id);
        std::uint16_t getId() const noexcept { return m_id; }
    private:

        std::uint16_t m_id;

        std::function<void(std::shared_ptr<Player> player)> m_effect;
        bool m_isOneTime;
    };
    void applyEffects();
    const std::vector<ProgressToken> getProgressTokens() const;
    void addProgressToken(const ProgressToken& token);

    std::uint16_t getTradeCost(ResourceType type,  Player& opponent) ;

    std::shared_ptr<Player> getOtherPlayer();
    void setOtherPlayer(const std::shared_ptr<Player>& otherPlayer);
    const std::shared_ptr<std::unordered_map<uint16_t,std::shared_ptr<Building>>> getDiscardPile() const;
    void setDiscardPile(const std::shared_ptr<std::unordered_map<uint16_t, std::shared_ptr<Building>>>& discardPile);
	void removeCardFromDiscardPile(uint16_t cardId);

    std::unordered_map<ResourceType, bool> getTradeDiscounts() const noexcept;
	void addTradeDiscount(ResourceType type) noexcept;

    bool hasChainId(std::uint16_t linkId) const;

    std::uint16_t getConstructionCost(const Building& building);

    bool canBuild(const Building& building);

    bool canBuildWonder(const Card& wonder);
    void buildWonder(std::uint16_t wonderId, std::shared_ptr<Building> ageCardUsed);

    uint16_t getCoinsPoints() const noexcept;
    uint16_t getBluePoints() const noexcept;
    uint16_t getFinalScore(uint16_t militaryPoints = 0) const noexcept;

    template<typename... Colors>
    std::uint16_t getBuildingCount(Colors... colors) const noexcept {
        if constexpr (sizeof...(colors) == 0) {
            return static_cast<std::uint16_t>(
                m_brownBuildings.size() +
                m_greyBuildings.size() +
                m_blueBuildings.size() +
                m_greenBuildings.size() +
                m_yellowBuildings.size() +
                m_redBuildings.size() +
                m_purpleBuildings.size()
            );
        } else {
            std::uint16_t total = 0;
            auto addForColor = [&](Building::Color color) noexcept {
                switch (color) {
                case Building::Color::BROWN: total += static_cast<uint16_t>(m_brownBuildings.size()); break;
                case Building::Color::GREY: total += static_cast<uint16_t>(m_greyBuildings.size()); break;
                case Building::Color::BLUE: total += static_cast<uint16_t>(m_blueBuildings.size()); break;
                case Building::Color::GREEN: total += static_cast<uint16_t>(m_greenBuildings.size()); break;
                case Building::Color::YELLOW: total += static_cast<uint16_t>(m_yellowBuildings.size()); break;
                case Building::Color::RED: total += static_cast<uint16_t>(m_redBuildings.size()); break;
                case Building::Color::PURPLE: total += static_cast<uint16_t>(m_purpleBuildings.size()); break;
                default: break;
                }
            };
            (addForColor(static_cast<Building::Color>(colors)), ...);
            return total;
        }
    }

    std::uint16_t getConstructedWondersCount() const noexcept;

    bool hasScientificSupremacy() const noexcept;

    bool hasTokenSelectionRight() const noexcept;
    void consumeTokenSelectionRight() noexcept;

    // Getters / setters for progress-token flags
    bool hasEconomyProgressToken() const noexcept;
    void setEconomyProgressToken(bool value) noexcept;

    bool hasMasonryProgressToken() const noexcept;
    void setMasonryProgressToken(bool value) noexcept;

    bool hasStrategyProgressToken() const noexcept;
    void setStrategyProgressToken(bool value) noexcept;

    bool hasTheologyProgressToken() const noexcept;
    void setTheologyProgressToken(bool value) noexcept;

    bool hasUrbanismProgressToken() const noexcept;
    void setUrbanismProgressToken(bool value) noexcept;

    bool hasArchitectureProgressToken() const noexcept;
    void setArchitectureProgressToken(bool value) noexcept;

    bool hasLawProgressToken() const noexcept;
    void setLawProgressToken(bool value) noexcept;

    bool hasMathematicsProgressToken() const noexcept;
    void setMathematicsProgressToken(bool value) noexcept;

    bool hasPhilosophyProgressToken() const noexcept;
    void setPhilosophyProgressToken(bool value) noexcept;

    bool hasAgricultureProgressToken() const noexcept;
    void setAgricultureProgressToken(bool value) noexcept;

private:

    std::string m_name;
    uint16_t m_coins;
    uint16_t m_victoryPoints=0;
    uint16_t m_shields;

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
    std::vector<uint16_t> m_scientificPoints = {0, 0, 0, 0, 0, 0};
    uint16_t m_scientificPointTypeNumber = 0;

    // Progress token, might delete
    std::vector<ProgressToken> m_progressTokens;

    //Daca jucatorul poate lua un ProgressToken
    bool m_hasTokenSelectionRight = false;
    //Memorarea efectelor speciale pe care le poate avea un jucator (ProgressToken)
    bool m_hasEconomyProgressToken = 0;
    bool m_hasMasonryProgressToken = 0;
    bool m_hasStrategyProgressToken = 0;
    bool m_hasTheologyProgressToken = 0;
    bool m_hasUrbanismProgressToken = 0;
    bool m_hasArchitectureProgressToken = 0;
    bool m_hasLawProgressToken = 0;
    bool m_hasMathematicsProgressToken = 0;
    bool m_hasPhilosophyProgressToken = 0;
    bool m_hasAgricultureProgressToken = 0;
    // Wonders
    std::vector<std::pair<std::shared_ptr<Card>, std::optional<std::shared_ptr<Building>>>> m_wonders;
    // pointer to the other player
    std::weak_ptr<Player> m_otherPlayer;
    // pointer to the discard pile
    std::shared_ptr<std::unordered_map<uint16_t,std::shared_ptr<Building>>> m_discardPile;

    // productions per turn
    std::unordered_map<ResourceType, std::uint16_t> m_productions;

    // trade discounts
	std::unordered_map<ResourceType, bool> m_tradeDiscounts;

    bool hasDiscountFor(ResourceType type) const;

    std::uint16_t countOpponentProduction(ResourceType type) ;

    void applyTokenDiscount(std::vector<ResourceType>& resourcesNeeded, int discountAmount) const;

};