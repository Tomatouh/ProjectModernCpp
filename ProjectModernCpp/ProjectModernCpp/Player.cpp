module Player;
import <iostream>;

Player::Player(const std::string& n) : name(n), score(0){}

void Player::addCard(const Card& card) {
	ownedCard.push_back(card);
	score += card.points;
}