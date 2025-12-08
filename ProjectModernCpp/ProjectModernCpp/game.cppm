export module game;
import Player;
import board;
import card;
import Building;
import std;
import cardsLoader;
import displayCard;

export class Game {
private:
	const static std::uint16_t k_boardSize = 20;
	const static std::uint16_t k_tokensNumber = 5;
	Player m_player1, m_player2;
	Board m_board;
	std::vector<std::shared_ptr<Card>> m_wondersDeck;
	std::vector<std::shared_ptr<Building>> m_ageIDeck;
	std::vector<std::shared_ptr<Building>> m_ageIIDeck;
	std::vector<std::shared_ptr<Building>> m_ageIIIDeck;
	std::vector<std::shared_ptr<Card>> m_discardedCards;
	std::vector<std::vector<std::optional<displayCard>>> m_cardDisplay;
	bool endGame;
	Building::Age m_currentAge;
	std::vector< std::shared_ptr<Player::ProgressToken>> m_progressTokensDeck;
	std::array<std::shared_ptr<Player::ProgressToken>, k_tokensNumber> m_progressTokens;

	std::shared_ptr<Building> getBuildingById(std::uint8_t searchId);
	std::shared_ptr <Building> selectAcceptableCard();
	void removeCardFromDeck(std::uint8_t id);
public:

	Game();

	/*Game(const Player& player1, const Player& player2,
		const Board& board,
		const std::vector<std::shared_ptr<Card>>& wondersCard,
		const std::vector<std::shared_ptr<Card>>& ageIDeck,
		const std::vector<std::shared_ptr<Card>>& ageIIDeck,
		const std::vector<std::shared_ptr<Card>>& m_ageIIIDeck,
		const std::vector<std::shared_ptr<Card>>& m_discardedCards);*/

	void initAgeIBoard();
	void initAgeIIBoard();
	void initAgeIIIBoard();

	void displayBoard();
	void clearBoard();

	void loadProgressTokens();
	void initProgressTokens();

	void run();
};


