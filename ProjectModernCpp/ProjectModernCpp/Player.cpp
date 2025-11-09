module Player;
import <iostream>;
import card;

Player::Player(std::string name) : name_(std::move(name)) {}

const std::string& Player::name() const noexcept { return name_; }
int Player::coins() const noexcept { return coins_; }
void Player::addCoins(int n) noexcept { coins_ += n; }
bool Player::spendCoins(int n) noexcept {
    if (n > coins_) return false;
    coins_ -= n;
    return true;
}

void Player::addCard(const Card& c) {
    ownedCards_.push_back(c);
    // card internals (name, victory points, etc.) are private in `card` module;
    // so we don't attempt to read them here. If you add accessors in `card`,
    // you can update score_ here (e.g. score_ += c.victoryPoints()).
}

const std::vector<Card>& Player::ownedCards() const noexcept {
    return ownedCards_;
}

int Player::getScore() const noexcept {
    return score_;
}

void Player::showStatus(std::ostream& os) const {
    os << "Player " << name_ << " | coins=" << coins_ << " | cards=" << ownedCards_.size() << "\n";
}

void Player::showCards(std::ostream& os) const {
    os << name_ << " owns " << ownedCards_.size() << " cards\n";
}