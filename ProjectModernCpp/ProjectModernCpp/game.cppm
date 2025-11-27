export module game;
import Player;
import board;
import bank;
import card;
import Building;
import std;

export class Game {
private:
	const static std::uint8_t k_boardSize = 20;
	Player m_player1, m_player2;
	Board m_board;
	std::vector<std::shared_ptr<Card>> m_wondersDeck;
	std::vector<std::shared_ptr<Card>> m_ageIDeck;
	std::vector<std::shared_ptr<Card>> m_ageIIDeck;
	std::vector<std::shared_ptr<Card>> m_ageIIIDeck;
	std::vector<std::shared_ptr<Card>> m_discardedCards;
	std::vector<std::vector<std::pair<std::uint16_t, bool>>> m_cardDisplay;
	bool endGame;

public:


	Game(const Player& player1, const Player& player2,
		const Board& board,
		const std::vector<std::shared_ptr<Card>>& wondersCard,
		const std::vector<std::shared_ptr<Card>>& ageIDeck,
		const std::vector<std::shared_ptr<Card>>& ageIIDeck,
		const std::vector<std::shared_ptr<Card>>& m_ageIIIDeck,
		const std::vector<std::shared_ptr<Card>>& m_discardedCards);

	void initAgeIBoard();
	void initAgeIIBoard();
	void initAgeIIIBoard();

	void displayBoard();
	void clearBoard();

};


