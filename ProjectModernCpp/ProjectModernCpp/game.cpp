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
m_discardedCards(std::make_shared<std::vector<std::shared_ptr<Card>>>()),
m_cardDisplay(),
m_currentAge(Building::Age::AGEI)
{
	Player player1, player2;
	m_currentPlayer = std::make_shared<Player>(player1);
	m_otherPlayer = std::make_shared<Player>(player2);
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
	GameState state = ONGOING;
	setGamestate(state);
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
	std::unordered_map<std::uint16_t, std::shared_ptr<Building>> copyDeck= m_ageIIIDeck;
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
		{Card::Effect::addScientificSymbol, [](Game& game) {game.m_currentPlayer->addScientificPoint(game.m_selectedBuilding->getScientificSymbol().value()); }}
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
	m_progressTokensDeck.push_back(std::make_shared<Player::ProgressToken>(Player::ProgressToken::agricultureToken));
	m_progressTokensDeck.push_back(std::make_shared<Player::ProgressToken>(Player::ProgressToken::architectureToken));
	m_progressTokensDeck.push_back(std::make_shared<Player::ProgressToken>(Player::ProgressToken::economyToken));
	m_progressTokensDeck.push_back(std::make_shared<Player::ProgressToken>(Player::ProgressToken::lawToken));
	m_progressTokensDeck.push_back(std::make_shared<Player::ProgressToken>(Player::ProgressToken::masonryToken));
	m_progressTokensDeck.push_back(std::make_shared<Player::ProgressToken>(Player::ProgressToken::mathematicsToken));
	m_progressTokensDeck.push_back(std::make_shared<Player::ProgressToken>(Player::ProgressToken::philosphyToken));
	m_progressTokensDeck.push_back(std::make_shared<Player::ProgressToken>(Player::ProgressToken::strategyToken));
	m_progressTokensDeck.push_back(std::make_shared<Player::ProgressToken>(Player::ProgressToken::theologyToken));
	m_progressTokensDeck.push_back(std::make_shared<Player::ProgressToken>(Player::ProgressToken::urbanismToken));
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
		m_progressTokens[i] = m_progressTokensDeck[index];
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

		for(int i=0;i<m_cardDisplay.size();i++)
			for(int j=0;j<m_cardDisplay[i].size();j++)
				if (m_cardDisplay[i][j].has_value())
					if (id == m_cardDisplay[i][j].value().getBuilding()->getId() && m_cardDisplay[i][j].value().isFaceUp()==true)
					{
						if (i == m_cardDisplay.size() - 1 || (m_cardDisplay[i+1][j].has_value() == false && m_cardDisplay[i+1][j+1].has_value() == false))
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
void Game::run()
{
	bool player1Turn = true;
	initAgeIBoard();
	m_currentAge = Building::Age::AGEI;
	std::uint8_t move;
	std::vector<std::optional<std::shared_ptr<Card>>> wonders;
	std::uint16_t iteration = 0;
	while (true)
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
				m_board.setPos(m_board.getPos() - m_selectedBuilding->getShields());*/

			removeCardFromDeck(m_selectedBuilding->getId());
			turnCards();
		}
		if (move == '2')
		{
			m_selectedBuilding = selectAcceptableCard();
			std::uint8_t profit = 2 + m_currentPlayer->getYellowBuildings().size();
			m_currentPlayer->addCoin(profit);
			m_discardedCards->push_back(m_selectedBuilding);
			removeCardFromDeck(m_selectedBuilding->getId());
			turnCards();
		}
		if (move == '3')
		{
			std::cout << "Your wonders:\n";
			for(auto wonder:m_currentPlayer->getWonders())
				std::cout << "[" << wonder.first->getId() << "] ";
			std::cout << "\n";
			auto selectedWonder=selectAcceptableWonder();
		}

		std::swap(m_currentPlayer, m_otherPlayer);
		player1Turn = !player1Turn;
		system("cls");
	}
}

