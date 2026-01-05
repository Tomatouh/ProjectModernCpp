#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
module game;



//Game::Game(const Player& player1, const Player& player2,
//	const Board& board,
//	const std::vector<std::shared_ptr<Card>>& wondersCard,
//	const std::vector<std::shared_ptr<Card>>& ageIDeck,
//	const std::vector<std::shared_ptr<Card>>& ageIIDeck,
//	const std::vector<std::shared_ptr<Card>>& ageIIIDeck,
//	const std::vector<std::shared_ptr<Card>>& discardedCards) : m_player1(player1), m_player2(player2), m_board(board), m_wondersDeck(wondersCard),
//	m_ageIDeck(ageIDeck), m_ageIIDeck(ageIIDeck), m_ageIIIDeck(ageIIIDeck), m_discardedCards(discardedCards)
//{
//}

Game::Game() : m_currentPlayer(), m_otherPlayer(), m_board(0),
m_wondersDeck(loadWondersDeck()),
m_ageIDeck(loadAgeIDeck()),
m_ageIIDeck(loadAgeIIDeck()),
m_ageIIIDeck(loadAgeIIIDeck()),
m_discardedCards(std::make_shared<std::unordered_map<std::uint16_t, std::shared_ptr<Building>>>()),
m_cardDisplay(),
m_currentAge(Building::Age::AGEI)
{
	//Player player1, player2;
	m_currentPlayer = std::make_shared<Player>();
	m_otherPlayer = std::make_shared<Player>();
	m_currentPlayer->setPlayerName("player1");
	m_otherPlayer->setPlayerName("player2");
	m_currentPlayer->setOtherPlayer(m_otherPlayer);
	m_otherPlayer->setOtherPlayer(m_currentPlayer);
	m_currentPlayer->setDiscardPile(m_discardedCards);
	m_otherPlayer->setDiscardPile(m_discardedCards);
	initProgressTokens();
	initCardEffects();
}

void Game::setGamestate(GameState& gamestate)
{
	this->m_gamestate = gamestate;
}

void Game::initAgeIBoard()
{
	/*GameState state = ONGOING;
	setGamestate(state);*/
	std::random_device rd;
	std::mt19937 gen(rd());
	std::unordered_map<std::uint16_t, std::shared_ptr<Building>> copyDeck = m_ageIDeck;

	for (int i = 0; i < 5; ++i)
	{
		std::vector<std::optional<displayCard>> row;
		for (int j = 0; j < i + 2; ++j)
		{
			std::uniform_int_distribution<> dist(0, copyDeck.size() - 1);
			displayCard card;

			auto it = copyDeck.begin();
			std::advance(it, dist(gen));

			card.setBuilding(it->second);
			std::uint16_t keyToErase = it->first;
			copyDeck.erase(keyToErase);

			if (!(i % 2))
				card.setFaceUp(true);
			else
				card.setFaceUp(false);

			row.push_back(std::make_optional(card));
		}
		m_cardDisplay.push_back(row);
		row.clear();
	}
}

void Game::initAgeIIBoard()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::unordered_map<std::uint16_t, std::shared_ptr<Building>> copyDeck = m_ageIIDeck;
	for (int i = 5; i > 0; --i)
	{
		std::vector<std::optional<displayCard>> row;
		for (int j = 0; j < i + 2; ++j)
		{
			std::uniform_int_distribution<> dist(0, copyDeck.size() - 1);
			displayCard card;
			auto it = copyDeck.begin();
			std::advance(it, dist(gen));

			card.setBuilding(it->second);
			std::uint16_t keyToErase = it->first;
			copyDeck.erase(keyToErase);
			if (!(i % 2))
				card.setFaceUp(true);
			else
				card.setFaceUp(false);
			row.push_back(std::make_optional(card));

		}
		m_cardDisplay.push_back(row);
		row.clear();
	}

}

void Game::initAgeIIIBoard()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::unordered_map<std::uint16_t, std::shared_ptr<Building>> copyDeck = m_ageIIIDeck;
	m_cardDisplay.resize(7);
	for (int i = 0; i <= 3; ++i)
	{
		if (i == 3) m_cardDisplay[i].resize(2);
		else m_cardDisplay[i].resize(i + 2);
	}

	for (int i = 4; i < 7; ++i)
	{
		m_cardDisplay[i].resize(8 - i);
	}
	for (int i = 0; i < m_cardDisplay.size(); ++i)
	{
		for (int j = 0; j < m_cardDisplay[i].size(); ++j)
		{
			std::uniform_int_distribution<> dist(0, copyDeck.size() - 1);
			displayCard card;
			auto it = copyDeck.begin();
			std::advance(it, dist(gen));

			card.setBuilding(it->second);
			std::uint16_t keyToErase = it->first;
			copyDeck.erase(keyToErase);
			if (!(i % 2))
				card.setFaceUp(true);
			else
				card.setFaceUp(false);
			m_cardDisplay[i][j] = std::make_optional(card);
		}
	}
}

void Game::initCardEffects()
{
	m_cardEffects = {
		{Card::Effect::addCoins, [](Game& game) {game.m_currentPlayer->addCoin(game.m_selectedBuilding->getCoins()); }},
		{Card::Effect::addVictoryPoints, [](Game& game) {game.m_currentPlayer->addVictoryPoints(game.m_selectedBuilding->getVictoryPoints()); }},
		{Card::Effect::addResource, [](Game& game) {game.m_currentPlayer->addResources(game.m_selectedBuilding->getResources()); }},
		{Card::Effect::addScientificSymbol, [](Game& game) {game.m_currentPlayer->addScientificPoint(game.m_selectedBuilding->getScientificSymbol().value()); }},
		{Card::Effect::addShields, [](Game& game) {game.m_currentPlayer->addShields(game.m_selectedBuilding->getShields()); }},
		{Card::Effect::buildersGuild, [](Game& game) {if (game.m_gamestate != GameState::ONGOING) game.m_currentPlayer->addVictoryPoints(2 * maxConstructedWonders(game.m_currentPlayer)); }},
		{Card::Effect::addManufacturedGoodProduction, [](Game& game) {game.m_currentPlayer->addProduction(game.m_selectedBuilding->getResources()); }},
		{Card::Effect::addRawResourceProduction, [](Game& game) {game.m_currentPlayer->addProduction(game.m_selectedBuilding->getResources()); } },
		{Card::Effect::constructCard, [](Game& game) {constructCard(game.m_currentPlayer); }},
		{Card::Effect::discardBrown, [](Game& game) {discardBrown(game.m_currentPlayer); }},
		{Card::Effect::discardGrey, [](Game& game) {discardGrey(game.m_currentPlayer); }},
		{Card::Effect::drawProgress, [](Game& game) {drawProgress(game.m_currentPlayer, game.m_progressTokensDeck); }},
		{Card::Effect::loseThreeCoins, [](Game& game) {game.m_otherPlayer->addCoin(-3); }},
		{Card::Effect::magistratesGuild, [](Game& game) {
			if (game.m_gamestate != GameState::ONGOING)
			{
				game.m_currentPlayer->addVictoryPoints(std::max(game.m_currentPlayer->getBlueBuildings().size(), game.m_otherPlayer->getBlueBuildings().size()));
			}
			else {
				game.m_currentPlayer->addCoin(std::max(game.m_currentPlayer->getBlueBuildings().size(), game.m_otherPlayer->getBlueBuildings().size()));
		} }},
		{Card::Effect::moneylendersGuild, [](Game& game) {
			if (game.m_gamestate != GameState::ONGOING)
			{
				game.m_currentPlayer->addVictoryPoints(game.m_currentPlayer->getCoins() / 3);
			}} },
		{Card::Effect::scientistsGuild, [](Game& game) {
			if (game.m_gamestate != GameState::ONGOING)
			{
				game.m_currentPlayer->addVictoryPoints(std::max(game.m_currentPlayer->getGreenBuildings().size(), game.m_otherPlayer->getGreenBuildings().size()));
			}
			else {
				game.m_currentPlayer->addCoin(std::max(game.m_currentPlayer->getGreenBuildings().size(), game.m_otherPlayer->getGreenBuildings().size()));
		} }},
		{Card::Effect::tacticiansGuild, [](Game& game) {
			if (game.m_gamestate != GameState::ONGOING)
			{
				game.m_currentPlayer->addVictoryPoints(std::max(game.m_currentPlayer->getRedBuildings().size(), game.m_otherPlayer->getRedBuildings().size()));
			}
			else {
				game.m_currentPlayer->addCoin(std::max(game.m_currentPlayer->getRedBuildings().size(), game.m_otherPlayer->getRedBuildings().size()));
		} }},
		{Card::Effect::tradersGuild, [](Game& game) {
			if (game.m_gamestate != GameState::ONGOING)
			{
				game.m_currentPlayer->addVictoryPoints(std::max(game.m_currentPlayer->getYellowBuildings().size(), game.m_otherPlayer->getYellowBuildings().size()));
			}
			else {
				game.m_currentPlayer->addCoin(std::max(game.m_currentPlayer->getYellowBuildings().size(), game.m_otherPlayer->getYellowBuildings().size()));
		} }},
		{Card::Effect::shipownersGuild, [](Game& game) {
			if (game.m_gamestate != GameState::ONGOING)
			{
				game.m_currentPlayer->addVictoryPoints(std::max(game.m_currentPlayer->getBrownBuildings().size() + game.m_currentPlayer->getGreyBuildings().size(),
					game.m_otherPlayer->getBrownBuildings().size() + game.m_otherPlayer->getGreyBuildings().size()));
			}
			else {
				game.m_currentPlayer->addCoin(std::max(game.m_currentPlayer->getBrownBuildings().size() + game.m_currentPlayer->getGreyBuildings().size(),
					game.m_otherPlayer->getBrownBuildings().size() + game.m_otherPlayer->getGreyBuildings().size()));
		} }},
		{Card::Effect::threeCoinsPerGrey, [](Game& game) {game.m_currentPlayer->addCoin(game.m_currentPlayer->getGreyBuildings().size() * 3); }},
		{Card::Effect::twoCoinsPerBrown, [](Game& game) {game.m_currentPlayer->addCoin(game.m_currentPlayer->getBrownBuildings().size() * 2); }},
		{Card::Effect::oneCoinPerYellow, [](Game& game) {game.m_currentPlayer->addCoin(game.m_currentPlayer->getYellowBuildings().size()); }},
		{Card::Effect::oneCoinPerRed, [](Game& game) {game.m_currentPlayer->addCoin(game.m_currentPlayer->getRedBuildings().size()); }},
		{Card::Effect::twoCoinsPerWonder, [](Game& game) {game.m_currentPlayer->addCoin(maxConstructedWonders(game.m_currentPlayer) * 2); }},
		{Card::Effect::oneCoinClay, [](Game& game) {game.m_currentPlayer->addTradeDiscount(ResourceType::CLAY); }},
		{Card::Effect::oneCoinGlass, [](Game& game) {game.m_currentPlayer->addTradeDiscount(ResourceType::GLASS); }},
		{Card::Effect::oneCoinPapyrus, [](Game& game) {game.m_currentPlayer->addTradeDiscount(ResourceType::PAPYRUS); }},
		{Card::Effect::oneCoinStone, [](Game& game) {game.m_currentPlayer->addTradeDiscount(ResourceType::STONE); }},
		{Card::Effect::oneCoinWood, [](Game& game) {game.m_currentPlayer->addTradeDiscount(ResourceType::WOOD); }}
	};
}

void Game::displayBoard()
{
	for (int i = 0; i < m_cardDisplay.size(); ++i)
	{
		for (int j = 0; j < m_cardDisplay[i].size(); ++j)
		{
			if (m_cardDisplay[i][j].has_value())
			{
				if (m_cardDisplay[i][j].value().isFaceUp())
					std::cout << "[" << m_cardDisplay[i][j].value().getBuilding()->getId() << "] ";
				else
					std::cout << "[hidden]";
			}
			else
				std::cout << "[NC]";

		}
		std::cout << "\n";
	}
}

void Game::clearBoard()
{
	m_cardDisplay.clear();
}

void Game::loadProgressTokens()
{
	m_progressTokensDeck.push_back(std::make_unique<Player::ProgressToken>(Player::ProgressToken::agricultureToken));
	m_progressTokensDeck.push_back(std::make_unique<Player::ProgressToken>(Player::ProgressToken::architectureToken));
	m_progressTokensDeck.push_back(std::make_unique<Player::ProgressToken>(Player::ProgressToken::economyToken));
	m_progressTokensDeck.push_back(std::make_unique<Player::ProgressToken>(Player::ProgressToken::lawToken));
	m_progressTokensDeck.push_back(std::make_unique<Player::ProgressToken>(Player::ProgressToken::masonryToken));
	m_progressTokensDeck.push_back(std::make_unique<Player::ProgressToken>(Player::ProgressToken::mathematicsToken));
	m_progressTokensDeck.push_back(std::make_unique<Player::ProgressToken>(Player::ProgressToken::philosphyToken));
	m_progressTokensDeck.push_back(std::make_unique<Player::ProgressToken>(Player::ProgressToken::strategyToken));
	m_progressTokensDeck.push_back(std::make_unique<Player::ProgressToken>(Player::ProgressToken::theologyToken));
	m_progressTokensDeck.push_back(std::make_unique<Player::ProgressToken>(Player::ProgressToken::urbanismToken));
}

void Game::initProgressTokens()
{
	loadProgressTokens();
	std::random_device rd;
	std::mt19937 gen(rd());
	for (int i = 0; i < m_progressTokens.size(); ++i)
	{
		std::uniform_int_distribution<> dist(0, m_progressTokensDeck.size() - 1);
		std::uint16_t index = dist(gen);
		m_progressTokens[i] = std::make_optional<Player::ProgressToken>(*m_progressTokensDeck[index]);
		m_progressTokensDeck.erase(m_progressTokensDeck.begin() + index);
	}

}

std::shared_ptr<Building> Game::getBuildingById(std::uint8_t searchId)
{
	if (m_currentAge == Building::Age::AGEI)
		return m_ageIDeck[searchId];

	if (m_currentAge == Building::Age::AGEII)
		return m_ageIIDeck[searchId];

	if (m_currentAge == Building::Age::AGEIII)
		return m_ageIIIDeck[searchId];
}

bool CheckPlayerResources(const std::shared_ptr<Player>& player, const std::shared_ptr<Building>& building)
{
	uint16_t auxWood = 0;
	uint16_t auxStone = 0;
	uint16_t auxClay = 0;
	uint16_t auxGlass = 0;
	uint16_t auxPapyrus = 0;
	std::vector<ResourceType> cardResourceCost = building->getCost().getCostResources();
	for (auto resource : cardResourceCost)
	{
		switch (resource)
		{
		case ResourceType::WOOD:
		{
			auxWood++;
			break;
		}
		case ResourceType::STONE:
		{
			auxStone++;
			break;
		}
		case ResourceType::CLAY:
		{
			auxClay++;
			break;
		}
		case ResourceType::GLASS:
		{
			auxGlass++;
			break;
		}
		case ResourceType::PAPYRUS:
		{
			auxPapyrus++;
			break;
		}
		}
	}
	if (player->getWood() < auxWood)
		return false;
	if (player->getStone() < auxStone)
		return false;
	if (player->getClay() < auxClay)
		return false;
	if (player->getGlass() < auxGlass)
		return false;
	if (player->getPapyrus() < auxPapyrus)
		return false;
	return true;
}

bool CheckPlayerCoins(const std::shared_ptr<Player>& player, const std::shared_ptr<Building>& building)
{
	if (player->getCoins() < building->getCost().getCostCoins())
		return false;
	return true;
}
std::shared_ptr <Building> Game::selectAcceptableCard()
{
	int id;
	bool acceptableCard;
	do
	{
		std::cout << "\ncard id:";
		std::cin >> id;
		acceptableCard = 0;

		for (int i = 0; i < m_cardDisplay.size(); i++)
			for (int j = 0; j < m_cardDisplay[i].size(); j++)
				if (m_cardDisplay[i][j].has_value())
					if (id == m_cardDisplay[i][j].value().getBuilding()->getId() && m_cardDisplay[i][j].value().isFaceUp() == true)
					{
						if (i == m_cardDisplay.size() - 1 || (m_cardDisplay[i + 1][j].has_value() == false && m_cardDisplay[i + 1][j + 1].has_value() == false))
						{
							acceptableCard = 1;
							break;
						}
					}
		if (!acceptableCard)
			std::cout << "Bad Card. Choose again\n";
	} while (!acceptableCard);

	return getBuildingById(id);
}
std::shared_ptr<Card> Game::selectWonder(std::vector<std::optional<std::shared_ptr<Card>>>& wonders, std::uint16_t searchId)
{
	for (int i = 0; i < wonders.size(); ++i)
	{
		if (wonders[i].has_value() && searchId == wonders[i]->get()->getId())
		{
			return wonders[i].value();
		}
	}
	return nullptr;
}
void Game::removeCardFromDeck(std::uint8_t id)
{
	for (int i = 0; i < m_cardDisplay.size(); i++)
		for (int j = 0; j < m_cardDisplay[i].size(); j++)
			if (m_cardDisplay[i][j].has_value())
			{
				if (m_cardDisplay[i][j].value().getBuilding()->getId() == id)
				{
					m_cardDisplay[i][j] = std::nullopt;
					break;
				}
			}
}

void Game::removeWonderFromDisplay(std::vector<std::optional<std::shared_ptr<Card>>>& wonders, std::uint16_t searchId)
{
	for (int i = 0; i < wonders.size(); ++i)
	{
		if (wonders[i].has_value() && searchId == wonders[i]->get()->getId())
		{
			wonders[i] = std::nullopt;
			break;
		}
	}
}

void Game::showFourWonders(std::vector<std::optional<std::shared_ptr<Card>>>& wonders)
{

	std::random_device rd;
	std::mt19937 gen(rd());
	for (int i = 0; i < 4; ++i) {
		std::uniform_int_distribution<> dist(0, m_wondersDeck.size() - 1);
		std::uint16_t index = dist(gen);
		wonders.push_back(std::make_optional(m_wondersDeck[index]));
		m_wondersDeck.erase(m_wondersDeck.begin() + index);
	}
	for (int i = 0; i < wonders.size(); ++i) {
		if (wonders[i].has_value())
		{
			std::cout << "[" << wonders[i].value().get()->getId() << "] ";
		}
		else std::cout << "[taken] ";
	}
	std::cout << "\n";

}

void Game::turnCards()
{
	for (int i = m_cardDisplay.size() - 2; i >= 0; i--)
	{
		for (int j = 0; j < m_cardDisplay[i].size(); j++)
		{
			if (m_cardDisplay[i][j].has_value())
				if (m_cardDisplay[i][j].value().isFaceUp() == false && m_cardDisplay[i + 1][j].has_value() == false && m_cardDisplay[i + 1][j + 1].has_value() == false)
					m_cardDisplay[i][j].value().setFaceUp(true);
		}
	}
}

std::pair<std::shared_ptr<Card>, std::optional<std::shared_ptr<Building>>> Game::selectAcceptableWonder()
{
	int id;
	bool acceptableWonder;
	do
	{
		std::cout << "\nwonder id:";
		std::cin >> id;
		acceptableWonder = 0;
		for (auto& wonder : m_currentPlayer->getWonders())
		{
			if (id == wonder.first->getId())
			{
				acceptableWonder = 1;

				return wonder;
			}
		}
		if (!acceptableWonder)
			std::cout << "Bad Wonder. Choose again\n";
	} while (!acceptableWonder);
}


/*
To do:
Make it so that wonders actually have an effect
Implement correct functionality for each age deck
*/

//void Game::handleEvents(const sf::Event& event,sf::RenderWindow& window)
//{
//	if (event.is<sf::Event::Closed>())
//		window.close();
//	if (event.is<sf::Event::Resized>()) {
//		window.clear(sf::Color::White);
//		drawCurrentAgeCards(window);
//		window.display();
//	}
//		
//}



std::pair<int, int> getNextCardPosition(Building::Age age)
{

	if (age == Building::Age::AGEI)
	{
		static int x = 620;
		static int y = 20;
		static std::uint8_t maxRowCards = 2;
		static std::uint8_t currentRowCard = 0;
		static std::uint8_t centeringOffset = 1;
		if (x == 620 && y == 20)
		{
			currentRowCard = 1;
			x += BoxSizes::boxHeight;
			return { 620,20 };
		}
		if (currentRowCard == maxRowCards)
		{
			x = x - (maxRowCards + centeringOffset) * BoxSizes::boxHeight / 2;
			y += BoxSizes::boxHeight + 5;
			currentRowCard = 1;
			maxRowCards++;
			centeringOffset++;
			return { x,y };
		}
		else
		{
			if (y != 20)
				x += BoxSizes::boxHeight;
			currentRowCard++;
			return { x,y };
		}
	}
}
void Game::drawCurrentAgeCards(sf::RenderWindow& window)
{
	int contor = 0;
	for (auto& row : m_cardDisplay)
		for (auto& card : row)
		{
			contor++;
			//std::pair<int, int> pos = getNextCardPosition(m_currentAge);
			if (card.has_value())
			{
				//card.value().setPosition(pos);
				if (card.value().isFaceUp())
				{
					auto pos = getNextCardPosition(m_currentAge);
					guiCard gCard = card.value().getGuiCard();
					gCard.setPosition(pos);
					card.value().setPosition(pos);
					window.draw(gCard);
				}
				else
				{
					auto pos = getNextCardPosition(m_currentAge);

					guiCard gCard = card.value().getGuiCard();
					gCard.setText("[Hidden card]");
					gCard.setPosition(pos);
					card.value().setPosition(pos);
					window.draw(gCard);
				}
			}
			else
			{
				auto pos = getNextCardPosition(m_currentAge);

				guiCard gCard;
				gCard.setPosition(pos);
				card.value().setPosition(pos);
				window.draw(gCard);
			}
		}
	std::cout << "Ok";
}

void Game::redrawCurrentAgeCards(sf::RenderWindow& window)
{
	for (auto& row : m_cardDisplay)
		for (auto& card : row)
		{
			if (card.has_value())
			{
				if (card.value().isFaceUp())
				{
					guiCard gCard = card.value().getGuiCard();
					gCard.setPosition(card.value().getPosition());
					gCard.setHighlighted(card.value().isSelected());
					window.draw(gCard);
				}
				else
				{
					guiCard gCard = card.value().getGuiCard();
					gCard.setText("[Hidden card]");
					gCard.setPosition(card.value().getPosition());
					gCard.setHighlighted(card.value().isSelected());
					window.draw(gCard);
				}
			}
			else
			{
				guiCard gCard;
				gCard.setPosition(card.value().getPosition());
				window.draw(gCard);
			}
		}
}

void drawCardSet(const std::vector<Building>& Buildings,int& xPos, int& yPos, sf::RenderWindow& window)
{
	int spacing = 5;
	for (const auto& card : Buildings) {

		auto cardPtr = std::make_shared<Building>(card);
		guiCard gCard(cardPtr);
		gCard.setSize(sf::Vector2f(static_cast<float>(BoxSizes::boxWidth / 2.f), static_cast<float>(BoxSizes::boxHeight / 2.f)));
		gCard.setPosition({ xPos, yPos });
		window.draw(gCard);
		yPos += BoxSizes::boxHeight / 2 + spacing;
	}
	yPos += spacing * 2;
}

int drawPlayerColumn(const std::shared_ptr<Player>& player, int xPos, sf::RenderWindow& window) {
	int yPos = 20;
	
	drawCardSet(player->getBrownBuildings(), xPos, yPos, window);
	drawCardSet(player->getGreyBuildings(), xPos, yPos, window);
	drawCardSet(player->getYellowBuildings(), xPos, yPos, window);
	drawCardSet(player->getRedBuildings(), xPos, yPos, window);
	drawCardSet(player->getGreenBuildings(), xPos, yPos, window);
	drawCardSet(player->getBlueBuildings(), xPos, yPos, window);

	return yPos;
}

void drawPlayerWonders(const std::shared_ptr<Player>& player, int xPos, int startYPos, sf::RenderWindow& window)
{
	int spacing = 5;
	int wonderYPos = startYPos;

	const int winW = static_cast<int>(window.getSize().x);
	const int cardW = static_cast<int>(BoxSizes::boxWidth / 2);
	const int margin = 20;

	if (xPos >= winW - cardW - margin /*&&*/) xPos -= 420;

	for (const auto& wonderPair : player->getWonders()) {
		auto wonderPtr = wonderPair.first;
		guiCard gCard(wonderPtr);
		gCard.setSize(sf::Vector2f(static_cast<float>(BoxSizes::boxWidth / 2.f), static_cast<float>(BoxSizes::boxHeight / 2.f)));
		gCard.setPosition({ xPos, wonderYPos });
		if (wonderPair.second.has_value()) {
			gCard.setHighlighted(true);
		}
		window.draw(gCard);
		wonderYPos += BoxSizes::boxHeight / 2 + spacing;
	}
}

void Game::drawPlayerCards(sf::RenderWindow& window)
{
	constexpr int spacing = 5;
	const auto winSize = window.getSize();
	const int winWidth = static_cast<int>(winSize.x);
	const int leftX = 20;
	const int rightX = std::max(20, winWidth - static_cast<int>(BoxSizes::boxWidth / 2) - 20);
	const int startY = 20;

	
	std::shared_ptr<Player> leftPlayer = nullptr, rightPlayer = nullptr;
	if (m_currentPlayer->name() == "player1") {
		leftPlayer = m_currentPlayer;
		rightPlayer = m_otherPlayer;
	}
	else {
		leftPlayer = m_otherPlayer;
		rightPlayer = m_currentPlayer;
	}
	int leftBottomY = drawPlayerColumn(leftPlayer, leftX, window);
	int rightBottomY = drawPlayerColumn(rightPlayer, rightX, window);

	drawPlayerWonders(leftPlayer, leftX, leftBottomY, window);
	drawPlayerWonders(rightPlayer, rightX, rightBottomY, window);

}

void Game::selectCardEffect(sf::RenderWindow& window)
{
	if (window.hasFocus()) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);

			bool anySelected = findSelectedCard(mousePos, window);

			window.clear(sf::Color::White);
			redrawCurrentAgeCards(window);
			drawPlayerCards(window);
			window.display();

			while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && window.isOpen()) {
				PollEvents(window);
				sf::sleep(sf::milliseconds(10));
			}
		}
	}
}

std::pair<int, int> Game::getWonderPosition(int index, const sf::RenderWindow& window)
{
	int total = static_cast<int>(m_wondersDisplay.size());
	const int cardW = BoxSizes::boxWidth * 2;
	const int cardH = BoxSizes::boxHeight * 2;
	const int padding = 20;
	const int winW = static_cast<int>(window.getSize().x);
	int totalWidth = total * cardW + (total - 1) * padding;
	int startX = std::max(0, (winW - totalWidth) / 2);
	int x = startX + index * (cardW + padding);
	int y = 200;
	return { x, y };
}

int Game::wonderIndexAtPosition(const sf::Vector2i& mousePos, const sf::RenderWindow& window)
{
	sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

	int total = static_cast<int>(m_wondersDisplay.size());
	if (total == 0) return -1;
	const int cardW = BoxSizes::boxWidth * 2;
	const int cardH = BoxSizes::boxHeight * 2;
	for (int i = 0; i < total; ++i) {
		auto pos = getWonderPosition(i, window);
		sf::FloatRect rect(sf::Vector2f(pos.first, pos.second), sf::Vector2f(cardW, cardH));
		if (rect.contains(worldPos)) return i;
	}
	return -1;
}

void Game::drawWondersSelection(sf::RenderWindow& window)
{

	if (m_wondersDisplay.empty())
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		for (int i = 0; i < 4; ++i)
		{
			std::uniform_int_distribution<> dist(0, m_wondersDeck.size() - 1);
			std::uint16_t index = dist(gen);
			m_wondersDisplay.push_back(std::make_optional(m_wondersDeck[index]));
			m_wondersDeck.erase(m_wondersDeck.begin() + index);
		}
	}

	int total = static_cast<int>(m_wondersDisplay.size());
	const float cardW = BoxSizes::boxWidth * 2;
	const float cardH = BoxSizes::boxHeight * 2;
	for (int i = 0; i < total; ++i)
	{
		auto pos = getWonderPosition(i, window);

		if (m_wondersDisplay[i].has_value())
		{
			guiCard gCard(m_wondersDisplay[i].value());
			gCard.setPosition(pos);
			gCard.setSize({ cardW, cardH });
			window.draw(gCard);
		}
		else {
			guiCard placeholder;
			placeholder.setText("[Taken]");
			placeholder.setPosition(pos);
			placeholder.setSize({ cardW, cardH });
			window.draw(placeholder);
		}
	}
}

void Game::wondersSetup(sf::RenderWindow& window)
{
	int step = 1;
	if (m_gamestate == GAMESTART) {
		while (step <= 2) {
			window.clear(sf::Color::White);
			drawWondersSelection(window);
			window.display();
			int iteration = 1;
			while (iteration <= 4) {
				PollEvents(window);
				if (window.hasFocus() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					int index = wonderIndexAtPosition(mousePos, window);
					if (index >= 0 && index < static_cast<int>(m_wondersDisplay.size())
						&& m_wondersDisplay[index].has_value()) {
						m_currentPlayer->addWonder(m_wondersDisplay[index].value());
						m_wondersDisplay[index] = std::nullopt;


						switch (step) {
						case 1:
							if (m_currentPlayer.get()->name() == "player1") {
								std::swap(m_currentPlayer, m_otherPlayer);
								iteration++;
							}
							else if (m_currentPlayer.get()->name() == "player2" && iteration == 3) {
								std::swap(m_currentPlayer, m_otherPlayer);
								iteration++;
							}
							else { iteration++; }
							break;
						case 2:
							if (m_currentPlayer.get()->name() == "player2") {
								std::swap(m_currentPlayer, m_otherPlayer);
								iteration++;
							}
							else if (m_currentPlayer.get()->name() == "player1" && iteration == 3) {
								std::swap(m_currentPlayer, m_otherPlayer);
								iteration++;

							}
							else { iteration++; }
							break;
						}


						window.clear(sf::Color::White);
						drawWondersSelection(window);
						window.display();

						while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && window.isOpen()) {
							PollEvents(window);
							sf::sleep(sf::milliseconds(10));
						}
					}
				}

			}
			m_wondersDisplay.clear();
			step++;
		}
		m_gamestate = ONGOING;
	}
}

bool Game::findSelectedCard(const sf::Vector2i& mousePos, const sf::RenderWindow& window) {
	bool found = false;
	for (int i = 0; i < m_cardDisplay.size(); i++)
		for (int j = 0; j < m_cardDisplay[i].size(); j++)
			if (m_cardDisplay[i][j].has_value()) {
				if (m_cardDisplay[i][j].value().isFaceUp() == true && m_cardDisplay[i][j].value().containsPoint(mousePos, window))
				{
					if (i == m_cardDisplay.size() - 1 || (m_cardDisplay[i + 1][j].has_value() == false && m_cardDisplay[i + 1][j + 1].has_value() == false))
					{
						m_cardDisplay[i][j].value().setSelected(true);
						found = true;
					}
					else {
						m_cardDisplay[i][j].value().setSelected(false);
					}
				}
				else {
					m_cardDisplay[i][j].value().setSelected(false);
				}
			}
	if (found)
		return true;
	return false;
}

void Game::PollEvents(sf::RenderWindow& window)
{

	while (const std::optional event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			window.close();
		if (event->is<sf::Event::Resized>()) {
			window.setView(window.getDefaultView());
			window.clear(sf::Color::White);
			m_wonderRects.clear();
			if (m_gamestate == GAMESTART)
				drawWondersSelection(window);
			if (m_gamestate == ONGOING) {
				redrawCurrentAgeCards(window);
				drawPlayerCards(window);
			}
			window.display();
		}
	}
}

void Game::run()
{
	m_gamestate = GAMESTART;
	bool player1Turn = true;
	initAgeIBoard();
	m_currentAge = Building::Age::AGEI;
	std::uint8_t move;
	std::vector<std::optional<std::shared_ptr<Card>>> wonders;
	//std::uint16_t iteration = 0;

	sf::RenderWindow window(sf::VideoMode({ 1500, 900 }), "7Wonders");
	window.setFramerateLimit(60);
	bool alreadyDrawn = false;
	int step = 1;

	while (window.isOpen())
	{

		PollEvents(window);
		wondersSetup(window);
		if (alreadyDrawn) {
			selectCardEffect(window);
		}

		if (!alreadyDrawn && m_gamestate == ONGOING) {
			window.clear(sf::Color::White);
			drawCurrentAgeCards(window);
			drawPlayerCards(window);
			window.display();
			alreadyDrawn = true;
		}





		/*while (true)
		{
			bool setup = true;
			showFourWonders(wonders);
			std::uint16_t step = 0;
			bool secondTurn = true;
			while (setup) {
				std::uint16_t id;
				std::cout << "current player: " << m_currentPlayer->name() << "\n";
				std::cout << "choose one wonder: ";
				std::cin >> id;
				std::shared_ptr<Card> selectedWonder = selectWonder(wonders, id);
				if (selectedWonder)
				{
					m_currentPlayer->addWonder(selectedWonder);
					removeWonderFromDisplay(wonders, id);
				}
				else {
					std::cout << "wonder not available\n";
					continue;
				}
				if (iteration == 0) {
					if (m_currentPlayer->name() == "player2" && secondTurn) {
						secondTurn = false;
						step++;

					}
					else {
						step++;
						std::swap(m_currentPlayer, m_otherPlayer);
					}
				}
				else if (iteration == 1)
				{
					if (m_currentPlayer->name() == "player1" && secondTurn) {
						secondTurn = false;
						step++;

					}
					else {
						step++;
						std::swap(m_currentPlayer, m_otherPlayer);
					}
				}
				if (step == 4)
				{
					setup = false;
				}
			}
			if (iteration == 1) break;
			iteration++;
			wonders.clear();
			system("cls");
		}
		system("cls");
		while (this->m_gamestate==ONGOING)
		{
			displayBoard();
			std::cout << "current player: " << m_currentPlayer->name() << "\n";
			std::cout << "1.build\n2.discard\n3.wonder\nmove:";
			std::cin >> move;
			if (move == '1')
			{
				m_selectedBuilding = selectAcceptableCard();
				if (CheckPlayerResources(m_currentPlayer, m_selectedBuilding) && CheckPlayerCoins(m_currentPlayer, m_selectedBuilding))
					m_currentPlayer->addBuilding(*m_selectedBuilding);
				else
				{
					std::cout << "You don't have enough resources/coins to build this building. Retry\n";
					continue;
				}

				/*if (player1Turn && m_selectedBuilding->getColor() == Building::Color::RED)
					m_board.setPos(m_board.getPos() + m_selectedBuilding->getShields());
				else
					m_board.setPos(m_board.getPos() - m_selectedBuilding->getShields());/*

				removeCardFromDeck(m_selectedBuilding->getId());
				turnCards();
			}
			if (move == '2')
			{
				m_selectedBuilding = selectAcceptableCard();
				std::uint8_t profit = 2 + m_currentPlayer->getYellowBuildings().size();
				m_currentPlayer->addCoin(profit);
				m_discardedCards->insert({ m_selectedBuilding->getId(), m_selectedBuilding });
				removeCardFromDeck(m_selectedBuilding->getId());
				turnCards();
			}
			if (move == '3')
			{
				if (Game::m_constructedWonders == 7)
				{
					system("cls");
					std::cout << "Nu se mai pot construi minuni";
					continue;
				}
				std::cout << "Your wonders:\n";
				for(auto wonder:m_currentPlayer->getWonders())
					std::cout << "[" << wonder.first->getId() << "] ";
				std::cout << "\n";
				auto selectedWonder=selectAcceptableWonder();
				m_selectedBuilding = selectAcceptableCard();
				if(m_currentPlayer->canBuildWonder(*(selectedWonder.first)))
				{
					m_currentPlayer->buildWonder(selectedWonder.first->getId(), m_selectedBuilding);
					Game::m_constructedWonders++;
					removeCardFromDeck(m_selectedBuilding->getId());
				}
				else
				{
					system("cls");
					std::cout << "You cannot build this wonder now. Retry\n";
					continue;
				}
			}

			std::swap(m_currentPlayer, m_otherPlayer);
			player1Turn = !player1Turn;
			system("cls");
		}*/
	}
}

std::uint8_t Game::m_constructedWonders = 0;