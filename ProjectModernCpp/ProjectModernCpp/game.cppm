#include <SFML/Graphics.hpp>
export module game;
import Player;
import board;
import card;
import Building;
import std;
import cardsLoader;
import displayCard;
import effects;
import guiCard;
import drawableGroup;
import choiceBox;

export class Game {
private:
	const static std::uint16_t k_boardSize = 20;
	static sf::Texture m_background;
	static sf::Sprite m_backgroundSprite;
	static std::uint8_t m_constructedWonders;
	static bool m_isInPlayerBox;
	static bool m_isInCardsBox;
	static bool m_isFirstPlayerBox;
	std::shared_ptr<Player> m_currentPlayer, m_otherPlayer;
	Board m_board;
	std::array<bool, 6> m_zoneRewardsGiven = { false, false, false, false, false, false };
	std::array<int, 6> m_pendingZoneVictoryPoints = { 0, 0, 0, 0, 0, 0 };
	std::vector<std::shared_ptr<Card>> m_wondersDeck;
	std::vector<std::optional<std::shared_ptr<Card>>> m_wondersDisplay;
	std::vector<sf::FloatRect> m_wonderRects;
	std::unordered_map<std::uint16_t, std::shared_ptr<Building>> m_ageIDeck;
	std::unordered_map<std::uint16_t, std::shared_ptr<Building>> m_ageIIDeck;
	std::unordered_map<std::uint16_t, std::shared_ptr<Building>> m_ageIIIDeck;
	std::shared_ptr<std::vector<std::shared_ptr<Building>>> m_discardedCards;
	std::vector<std::vector<std::optional<displayCard>>> m_cardDisplay;
	std::unordered_map<std::uint16_t, std::optional<guiCard>> m_guiCardDisplay;

	Building::Age m_currentAge;
	std::vector< std::unique_ptr<Player::ProgressToken>> m_progressTokensDeck;
	std::vector<std::unique_ptr<Player::ProgressToken>> m_remainingProgressTokens;
	std::unordered_map<Card::Effect, std::function<void(Game& game)>> m_cardEffects;
	std::shared_ptr<Building> m_selectedBuilding;
	enum GameState {
		GAMESTART,
		ONGOING,
		MILITARY,
		SCIENTIFIC,
		CIVILIAN
	};
	GameState m_gamestate = GAMESTART;
	bool m_waitingForDiscardedChoice = false;
	bool m_waitingToDiscardBrown = false;
	bool m_waitingToDiscardGrey = false;
	bool m_waitingForTokenSelection = false;
	std::vector<std::unique_ptr<Player::ProgressToken>> m_current3TokenChoices;
	bool m_activatedGuildCards = false;


	std::shared_ptr<Building> getBuildingById(std::uint8_t searchId);
	std::shared_ptr<Card> getWonderById(std::uint8_t searchId);
	std::shared_ptr <Building> selectAcceptableCard();
	std::pair<std::shared_ptr<Card>, std::optional<std::shared_ptr<Building>>> selectAcceptableWonder();
	std::shared_ptr<Card> selectWonder(std::vector<std::optional<std::shared_ptr<Card>>>& wonders, std::uint16_t searchID);
	void removeCardFromDeck(std::uint8_t id, bool discarded);
	void turnCards();
	void removeWonderFromDisplay(std::vector<std::optional<std::shared_ptr<Card>>>& wonders, std::uint16_t searchId);
	bool findSelectedCard(const sf::Vector2i& mousePos, sf::RenderWindow& window);
	void PollEvents(sf::RenderWindow& window);
	void drawCurrentAgeCards(sf::RenderWindow& window);
	void redrawCurrentAgeCards(sf::RenderWindow& window);
	void drawPlayerCards(sf::RenderWindow& window);
	bool selectCardEffect(sf::RenderWindow& window, sf::Vector2i&& mousePos);
	std::pair<int, int> getWonderPosition(int index, const sf::RenderWindow& window);
	int wonderIndexAtPosition(const sf::Vector2i& mousePos, const sf::RenderWindow& window);
	void drawWondersSelection(sf::RenderWindow& window);
	void wondersSetup(sf::RenderWindow& window, const sf::Vector2i mousePos);
	void drawConstructionChoices(sf::RenderWindow& window);
	int getConstructionOption(sf::RenderWindow& window, const sf::Vector2i& mousePos);
	int chooseConstructionOption(sf::RenderWindow& window, const sf::Vector2i& mousePos);
	void activateCardEffects(std::shared_ptr<Building> building);
	void activateWonderEffects(std::shared_ptr<Card> card);
	void drawMilitaryBoard(sf::RenderWindow& window);
	void drawTokenSelection(sf::RenderWindow& window);
	bool selectToken(sf::RenderWindow& window, const sf::Vector2i& mousePos);
	void drawPlayerTurn(sf::RenderWindow& window);
	void drawDiscardedCards(sf::RenderWindow& window);
	bool selectDiscardedCard(sf::RenderWindow& window, const sf::Vector2i& mousePos);
	void constructDiscardedCard(sf::RenderWindow& window);
	void checkAndApplyZoneRewards();
	void drawOpponentGreyOrBrownBuildings(sf::RenderWindow& window, Building::Color color);
	bool selectGreyOrBrownCard(sf::RenderWindow& window, const sf::Vector2i& mousePos, Building::Color color);
	void discardOpponentCard(sf::RenderWindow& window, Building::Color color);

	void drawSelectedCard(sf::RenderWindow& window);
	void drawPlayerCardsBox(sf::RenderWindow& window);
	void checkMilitaryVictory();
	void drawMilitaryVictoryScreen(sf::RenderWindow& window);
	void drawCivilianVictoryScreen(sf::RenderWindow& window);

	void drawScientificVictoryScreen(sf::RenderWindow& window);

	void awardPendingZoneVictoryPoints();

	void draw3ProgressTokens(sf::RenderWindow& window);
	bool selectFrom3ProgressTokens(sf::RenderWindow& window, const sf::Vector2i& mousePos);
	void takeProgressToken(sf::RenderWindow& window);

public:

	Game();

	void saveGame();
	bool loadGame();
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

	void initCardEffects();

	void loadProgressTokens();
	void initProgressTokens();

	void showFourWonders(std::vector<std::optional<std::shared_ptr<Card>>>& wonders);

	void handleClick(sf::RenderWindow& window, sf::Vector2i&& mousePos);

	template<typename... Args>
	void drawAll(sf::RenderWindow& window, Args... args);

	void drawPlayerBox(sf::RenderWindow& window, const std::shared_ptr<Player>& selectedPlayer);


	void run();

};


