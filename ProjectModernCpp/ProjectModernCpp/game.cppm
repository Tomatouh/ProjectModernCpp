export module game;
import Player;
import board;
import bank;
import card;
import Building;
import std;

export class Game {
private:
	Player m_player1, m_player2;
	Board m_board;
	Bank m_bank;
	std::vector<std::shared_ptr<Card>> m_wondersDeck;
	std::vector<std::shared_ptr<Card>> m_ageIDeck;
	std::vector<std::shared_ptr<Card>> m_ageIIDeck;
	std::vector<std::shared_ptr<Card>> m_ageIIIDeck;
	std::vector<std::shared_ptr<Card>> m_discardedCards;
	//std::array<std::pair<std::uint8_t, bool>, 20> cardDisplay;
	bool endGame;

public:

	/*Game(const Player& player1, const Player& player2,
		const std::vector<std::shared_ptr<Card>>& wondersCard,
		const std::vector<std::shared_ptr<Card>>& ageIDeck,
		const std::vector<std::shared_ptr<Card>>& ageIIDeck,
		const std::vector<std::shared_ptr<Card>>& m_ageIIIDeck,
		const std::vector<std::shared_ptr<Card>>& m_discardedCards);*/

	void setAgeIDeck(const std::vector<std::shared_ptr<Card>>& deck) { m_ageIDeck = deck; }

};

//Game::Game(const Player& player1, const Player& player2, 
//	const std::vector<std::shared_ptr<Card>>& wondersCard, 
//	const std::vector<std::shared_ptr<Card>>& ageIDeck, 
//	const std::vector<std::shared_ptr<Card>>& ageIIDeck, 
//	const std::vector<std::shared_ptr<Card>>& m_ageIIIDeck, 
//	const std::vector<std::shared_ptr<Card>>& m_discardedCards) : Player(player1)
//{
//}
