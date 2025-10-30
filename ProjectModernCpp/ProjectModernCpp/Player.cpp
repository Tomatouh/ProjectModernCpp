module Player;
import <iostream>;

Player::Player(const std::string& n) : name(n), score(0){}

void Player::addCard(const Card& card) {
	ownedCards.push_back(card);
	score += card.points;
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
	std::cout << name << " detine urmatoarele carti:\n";
	for (const auto& card : ownedCards) {
		std::cout << " - " << card.name << " (+ " << card.points << " puncte)\n";
	}
}




