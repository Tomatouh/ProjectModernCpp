export module Player;
import <string>;
import <vector>;
import <cstdint>;
import <iostream>;
import card;
import Building; // Building trebuie importat pentru a fi folosit in Player

export class Player {
public:
    explicit Player(std::string name, bool isPlayer1, int startCoin1Amount, int startCoin3Amount, int startCoin6Amount);

    const std::string& name() const noexcept;

    bool isPlayer1() const noexcept;
    void setIsPlayer1(bool isPlayer1) noexcept;

    // Coin management methods
    void addCoin1(int amount = 1) noexcept;
    void addCoin3(int amount = 1) noexcept;
    void addCoin6(int amount = 1) noexcept;

    void payCoin1(int amount = 1) noexcept;
    void payCoin3(int amount = 1) noexcept;
    void payCoin6(int amount = 1) noexcept;

    int coin1Count() const noexcept;
    int coin3Count() const noexcept;
    int coin6Count() const noexcept;
    int totalCoinValue() const noexcept;
    int coins() const noexcept;

    void addBuilding(const Building& building); // Modificata pentru a adauga o cladire

    // Getters pentru cladiri, pe culori
    const std::vector<Building>& getBrownBuildings() const noexcept;
    const std::vector<Building>& getGreyBuildings() const noexcept;
    const std::vector<Building>& getBlueBuildings() const noexcept;
    const std::vector<Building>& getGreenBuildings() const noexcept;
    const std::vector<Building>& getYellowBuildings() const noexcept;
    const std::vector<Building>& getRedBuildings() const noexcept;
    const std::vector<Building>& getPurpleBuildings() const noexcept;


    uint8_t getVictoryPoints() const noexcept;
    void addVictoryPoints(uint8_t points) noexcept;

    int getMilitaryPoints() const noexcept;
    void addMilitaryPoints(int points) noexcept;

    uint8_t getWood() const noexcept;
    void addWood(uint8_t amount = 1) noexcept;
    uint8_t getStone() const noexcept;
    void addStone(uint8_t amount = 1) noexcept;
    uint8_t getClay() const noexcept;
    void addClay(uint8_t amount = 1) noexcept;
    uint8_t getGlass() const noexcept;
    void addGlass(uint8_t amount = 1) noexcept;
    uint8_t getPapyrus() const noexcept;
    void addPapyrus(uint8_t amount = 1) noexcept;

    void showStatus(std::ostream& os = std::cout) const;
    void showCards(std::ostream& os = std::cout) const;

    //Functii pentru folosirea punctelor stiintifice
    enum class scientificPointType:uint8_t
    {
        Globe,
        Law,
        Time,
        Medicine,
        Architecture,
        Writing,
        Wheel
    };
    void addScientificPoint(scientificPointType point) noexcept;
    std::vector<uint8_t> getScientificPoints() noexcept;
    //Aplicare efecte
    class ProgressToken {
    public:
        static ProgressToken agricultureToken;
        static ProgressToken architectureToken;
        static ProgressToken EconomyToken;
        static ProgressToken lawToken;
        static ProgressToken masonryToken;
        static ProgressToken mathematicsToken;
        static ProgressToken philosphyToken;
        static ProgressToken strategyToken;
        static ProgressToken theologyToken;
        static ProgressToken urbanismToken;
        void applyEffect(Player*p);
        ProgressToken(void (*effect)(Player* p), bool isOneTime);
    private:
        void (*m_effect)(Player* p);
        bool m_isOneTime;
    };
    void applyEffects();
    std::vector<ProgressToken> getProgressTokens();
private:
    bool m_isPlayer1;
    std::string m_name;
    int m_coin1Count;
    int m_coin3Count;
    int m_coin6Count;
    uint8_t m_victoryPoints;
    int m_militaryPoints;

    // Resources
    uint8_t m_wood;
    uint8_t m_stone;
    uint8_t m_clay;
    uint8_t m_glass;
    uint8_t m_papyrus;

    // Colectii de cladiri, separate pe culori
    std::vector<Building> m_brownBuildings;
    std::vector<Building> m_greyBuildings;
    std::vector<Building> m_blueBuildings;
    std::vector<Building> m_greenBuildings;
    std::vector<Building> m_yellowBuildings;
    std::vector<Building> m_redBuildings;
    std::vector<Building> m_purpleBuildings;

    // Puncte stiintifice
    std::vector<uint8_t> m_scientificPoints;
    uint8_t m_scientificPointTypeNumber = 0;

    // Progress token
    std::vector<ProgressToken> m_progressTokens;

};