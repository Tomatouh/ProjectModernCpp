export module game;
import Player;
import board;
import bank;
import card;
import Building;
import std;

export class Game {
private:
	Player player1, player2;
	Board board;
	Bank bank;
	std::vector<Card*> ageIDeck;
	std::vector<Card*> ageIIDeck;
	std::vector<Card*> ageIIIDeck;
	std::vector<Card*> discardedCards;
	std::array<std::pair<std::uint8_t, bool>, 20> cardDisplay;
	bool endGame;

public:

};