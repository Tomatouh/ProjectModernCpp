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
	std::vector<std::shared_ptr<Card>> wondersDeck;
	std::vector<std::shared_ptr<Card>> ageIDeck;
	std::vector<std::shared_ptr<Card>> ageIIDeck;
	std::vector<std::shared_ptr<Card>> ageIIIDeck;
	std::vector<std::shared_ptr<Card>> discardedCards;
	//std::array<std::pair<std::uint8_t, bool>, 20> cardDisplay;
	bool endGame;

public:

	Game() = default;
	
	void setAgeIDeck(const std::vector<std::shared_ptr<Card>>& deck) { ageIDeck = deck; }

};