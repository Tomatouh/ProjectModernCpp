export module Player;
import <string>;
import <vector>;
import Card;


export class Player {
public:
	std::string name;
	int score;
	std::vector<Card> ownedCards;

	Player(const std::string& n);

	void addCard(const Card& card);
};