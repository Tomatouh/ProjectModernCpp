export module Player;
import <string>;
import <vector>;
import <iostream>;
import card;

export class Player {
public:
    explicit Player(std::string name) : name_(std::move(name)), coins_(7) {}

    const std::string& name() const noexcept { return name_; }
    int coins() const noexcept { return coins_; }
    void addCoins(int n) noexcept { coins_ += n; }
    bool spendCoins(int n) noexcept {
        if (n > coins_) return false;
        coins_ -= n;
        return true;
    }

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
        os << "Player " << name_ << " | coins=" << coins_ << "\n";
        os << "Score: " << getScore() << "\n";
    }

    void showCards(std::ostream& os = std::cout) const {
        os << "Cards owned by " << name_ << ":\n";
        for (const auto& card : ownedCards_) {
            os << " - " << card.name() << " (Value: " << card.value() << ")\n"; // Assuming Card has name() and value() methods
        }
    }

private:
    std::string name_;
    int coins_{ 7 };
    int score_{ 0 };

    std::vector<Card> ownedCards_;
};

