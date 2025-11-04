import <iostream>;
import Player;

Player::Player(const std::string& n) : name(n), score(0){}

void Player::addCard(const Card& c) {
	ownedCards.push_back(c);
	//score += c.points;
}

int Player::getScore() const
{
	return score;
}

const std::string& Player::getName() const
{
	return name;
}

void Player::showCards() const
{
	std::cout << name << " owns the following cards:\n";
	for (const auto& card : ownedCards) {
		//std::cout << " - " << card.name << " (+ " << card.points << " puncte)\n";
	}
}