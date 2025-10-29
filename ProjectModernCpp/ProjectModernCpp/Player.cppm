export module Player;
import <string>;
import <vector>;
import Card;


export class Player {
private:
	std::string name;
	int score;
	std::vector<Card> ownedCards;

public:
	Player(const std::string& n);

	void addCard(const Card& card);
	int getScore() const;
	const std::string& getName() const;
	void showCards() const;
};