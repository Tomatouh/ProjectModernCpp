export module Player;
import <string>;
import <vector>;
import <iostream>;
import card;
import Building; // Building trebuie importat pentru a fi folosit in Player

export class Player {
public:
    explicit Player(std::string name);

    const std::string& name() const noexcept;

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

    int getScore() const noexcept;

    void showStatus(std::ostream& os = std::cout) const;
    void showCards(std::ostream& os = std::cout) const;

private:
    std::string name_;
    int coin1_count_;
    int coin3_count_;
    int coin6_count_;
    int total_coin_value_;
    int score_;

    // Colectii de cladiri, separate pe culori
    std::vector<Building> brownBuildings_;
    std::vector<Building> greyBuildings_;
    std::vector<Building> blueBuildings_;
    std::vector<Building> greenBuildings_;
    std::vector<Building> yellowBuildings_;
    std::vector<Building> redBuildings_;
    std::vector<Building> purpleBuildings_; 
};