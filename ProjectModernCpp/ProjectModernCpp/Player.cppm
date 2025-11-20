export module Player;
import <string>;
import <vector>;
import <cstdint>;
import <iostream>;
import card;
import Building; // Building trebuie importat pentru a fi folosit in Player

export class Player {
public:
    explicit Player(std::string name, bool isPlayer1);

    const std::string& name() const noexcept;

    bool isPlayer1() const noexcept;
    void setIsPlayer1(bool isPlayer1) noexcept;

    int coins() const noexcept;
    void addCoins(int n) noexcept;
    bool spendCoins(int n) noexcept;

    int coin1Count() const noexcept;
    int coin3Count() const noexcept;
    int coin6Count() const noexcept;
    int totalCoinValue() const noexcept;

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

private:
    bool m_isPlayer1;
    std::string m_name;
    int m_coin1Count;
    int m_coin3Count;
    int m_coin6Count;
    int m_totalCoinValue;
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
};