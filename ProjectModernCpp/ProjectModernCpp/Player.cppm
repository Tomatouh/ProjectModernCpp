export module Player;
import <string>;
import <vector>;
import <cstdint>;
import <iostream>;
import <memory>;
import <functional>;
import card;
import Building; // Building trebuie importat pentru a fi folosit in Player

export class Player {
public:

    const static std::uint16_t k_startCoin1Amount = 7, k_startCoin3Amount = 0, k_startCoin6Amount = 0;
    const static std::uint16_t k_numberOfWonders = 4;

    Player();
    explicit Player(std::string name, std::uint16_t startCoin1Amount, std::uint16_t startCoin3Amount, std::uint16_t startCoin6Amount);
    Player(const Player& other);

    const std::string& name() const noexcept;

    void setPlayerName(const std::string_view name);

    // Coin management methods
	void addCoin(std::uint16_t amount) noexcept;

    bool payCoin(std::uint16_t amount) noexcept;
    std::uint16_t coins() const noexcept;

    void addBuilding(const Building& building); // Modificata pentru a adauga o cladire
    Building discardBuilding(Building::Color color, std::uint8_t id);


    // Getters for Buildings, by colour
    const std::vector<Building>& getBrownBuildings() const noexcept;
    const std::vector<Building>& getGreyBuildings() const noexcept;
    const std::vector<Building>& getBlueBuildings() const noexcept;
    const std::vector<Building>& getGreenBuildings() const noexcept;
    const std::vector<Building>& getYellowBuildings() const noexcept;
    const std::vector<Building>& getRedBuildings() const noexcept;
    const std::vector<Building>& getPurpleBuildings() const noexcept;
    const std::array<std::shared_ptr<Card>, k_numberOfWonders> getWonders() const noexcept;


    uint16_t getVictoryPoints() const noexcept;
    void addVictoryPoints(uint16_t points) noexcept;


    uint16_t getWood() const noexcept;
    void addWood(uint16_t amount = 1) noexcept;
    uint16_t getStone() const noexcept;
    void addStone(uint16_t amount = 1) noexcept;
    uint16_t getClay() const noexcept;
    void addClay(uint16_t amount = 1) noexcept;
    uint16_t getGlass() const noexcept;
    void addGlass(uint16_t amount = 1) noexcept;
    uint16_t getPapyrus() const noexcept;
    void addPapyrus(uint16_t amount = 1) noexcept;

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
    std::array<std::pair<std::shared_ptr<Card>, std::shared_ptr<Building>>, k_numberOfWonders> m_wonders;

};