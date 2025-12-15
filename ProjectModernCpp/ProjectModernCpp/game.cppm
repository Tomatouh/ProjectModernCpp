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
	std::shared_ptr<Player> m_currentPlayer, m_otherPlayer;
	Board m_board;
	std::vector<std::shared_ptr<Card>> m_wondersDeck;
	std::unordered_map<std::uint16_t,std::shared_ptr<Building>> m_ageIDeck;
	std::unordered_map<std::uint16_t,std::shared_ptr<Building>> m_ageIIDeck;
	std::unordered_map<std::uint16_t,std::shared_ptr<Building>> m_ageIIIDeck;
	std::shared_ptr<std::vector<std::shared_ptr<Card>>> m_discardedCards;
	std::vector<std::vector<std::optional<displayCard>>> m_cardDisplay;

	Building::Age m_currentAge;
	std::vector< std::shared_ptr<Player::ProgressToken>> m_progressTokensDeck;
	std::array<std::shared_ptr<Player::ProgressToken>, k_tokensNumber> m_progressTokens;
	std::unordered_map<Card::Effect, std::function<void(Game& game)>> m_cardEffects;
	std::shared_ptr<Building> m_selectedBuilding;


	std::shared_ptr<Building> getBuildingById(std::uint8_t searchId);
	std::shared_ptr <Building> selectAcceptableCard();
	std::shared_ptr<Card> selectWonder(std::vector<std::optional<std::shared_ptr<Card>>>& wonders, std::uint16_t searchID);
	void removeCardFromDeck(std::uint8_t id);
	void turnCards();
	void removeWonderFromDisplay(std::vector<std::optional<std::shared_ptr<Card>>>& wonders, std::uint16_t searchId);
public:

	Game();


	enum GameState {
		GAMESTART,
		ONGOING,
		MILITARY,
		SCIENTIFIC,
		CIVILIAN
	};
	GameState m_gamestate = GAMESTART;
	/*Game(const Player& player1, const Player& player2,
		const Board& board,
		const std::vector<std::shared_ptr<Card>>& wondersCard,
		const std::vector<std::shared_ptr<Card>>& ageIDeck,
		const std::vector<std::shared_ptr<Card>>& ageIIDeck,
		const std::vector<std::shared_ptr<Card>>& m_ageIIIDeck,
		const std::vector<std::shared_ptr<Card>>& m_discardedCards);*/
	void setGamestate(GameState& gamestate);
	void initAgeIBoard();
	void initAgeIIBoard();
	void initAgeIIIBoard();
	
	void initCardEffects();

	void displayBoard();
	void clearBoard();

	void loadProgressTokens();
	void initProgressTokens();

	void showFourWonders(std::vector<std::optional<std::shared_ptr<Card>>>& wonders);

	void run();
};


