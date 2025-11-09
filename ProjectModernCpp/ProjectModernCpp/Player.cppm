export module Player;
import <string>;
import <vector>;
import <iostream>;
import card;

export class Player {
public:
    explicit Player(std::string name)
        : name_(std::move(name)),
          coin1_count_(7),
          coin3_count_(0),
          coin6_count_(0),
          total_coin_value_(7),
          score_(0)
    {}

    const std::string& name() const noexcept { return name_; }

    // legacy compatibility: total coin value (keeps existing `coins()` name)
    int coins() const noexcept { return total_coin_value_; }

    // Add/spend operate on total value only (denomination counts are read-only here)
    void addCoins(int n) noexcept { total_coin_value_ += n; }
    bool spendCoins(int n) noexcept {
        if (n > total_coin_value_) return false;
        total_coin_value_ -= n;
        return true;
    }

    // Denomination getters (read-only)
    int coin1Count() const noexcept { return coin1_count_; }
    int coin3Count() const noexcept { return coin3_count_; }
    int coin6Count() const noexcept { return coin6_count_; }
    int totalCoinValue() const noexcept { return total_coin_value_; }

    // Card management
    void addCard(const Card& c) { ownedCards_.emplace_back(c); }
    const std::vector<Card>& ownedCards() const noexcept { return ownedCards_; }

    int getScore() const noexcept {
        // Assuming score is calculated based on the cards owned
        int totalScore = 0;
        for (const auto& card : ownedCards_) {
            totalScore += card.value(); // Assuming Card has a value() method
        }
        return totalScore;
    }

    void showStatus(std::ostream& os = std::cout) const {
        os << "Player " << name_ << " | coins=" << total_coin_value_
           << " (1s=" << coin1_count_ << ", 3s=" << coin3_count_ << ", 6s=" << coin6_count_ << ")\n";
        os << "Score: " << getScore() << "\n";
    }

    void showCards(std::ostream& os = std::cout) const {
        os << "Cards owned by " << name_ << ":\n";
        for (const auto& card : ownedCards_) {
            os << " - " << card.name() << " (Value: " << card.value() << ")\n"; // Assumes Card exposes m_name() and value()
        }
    }

private:
    std::string name_;

    // New coin state (counts by denomination)
    int coin1_count_{ 7 };      // number of 1-value coins
    int coin3_count_{ 0 };      // number of 3-value coins
    int coin6_count_{ 0 };      // number of 6-value coins
    int total_coin_value_{ 7 }; // total value of all coins

    int score_{ 0 };
    std::vector<Card> ownedCards_;
};

