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

Game::Game() : m_player1(), m_player2(), m_board(0), 
m_wondersDeck(loadWondersDeck()), 
m_ageIDeck(loadAgeIDeck()), 
m_ageIIDeck(loadAgeIIDeck()), 
m_ageIIIDeck(loadAgeIIIDeck()),
m_discardedCards(),
m_cardDisplay(),
endGame(false),
m_currentAge(Building::Age::AGEI)
{
	m_player1.setPlayerName("player1");
	m_player2.setPlayerName("player2");
	
}

void Game::initAgeIBoard()
{
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::vector<std::shared_ptr<Building>> copyDeck = m_ageIDeck;
	for (int i = 0; i < 5; ++i)
	{
		std::vector<std::optional<displayCard>> row;
		for (int j = 0; j < i + 2; ++j)
		{
			std::uniform_int_distribution<> dist(0, copyDeck.size() - 1);
			displayCard card;
			std::uint16_t index1 = dist(gen);
			card.setBuilding(copyDeck[index1]);
			copyDeck.erase(copyDeck.begin() + index1);
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
	std::vector<std::shared_ptr<Building>> copyDeck = m_ageIIDeck;
	for (int i = 5; i > 0; --i)
	{
		std::vector<std::optional<displayCard>> row;
		for (int j = 0; j < i + 2; ++j)
		{
			std::uniform_int_distribution<> dist(0, copyDeck.size() - 1);
			displayCard card;
			std::uint16_t index1 = dist(gen);
			card.setBuilding(copyDeck[index1]);
			copyDeck.erase(copyDeck.begin() + index1);
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
	std::vector<std::shared_ptr<Building>> copyDeck = m_ageIIIDeck;
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
			std::uint16_t index1 = dist(gen);
			card.setBuilding(copyDeck[index1]);
			copyDeck.erase(copyDeck.begin() + index1);
			if (!(i % 2))
				card.setFaceUp(true);
			else
				card.setFaceUp(false);
			m_cardDisplay[i][j] = std::make_optional(card);
		}
	}
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
					std::cout << "[" << (int)m_cardDisplay[i][j].value().getBuilding()->getId() << "] ";
				else
					std::cout << "[hidden]";
			}
			else
				std::cout << "[NC] ";
			
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
	{
		for(int i=0;i<m_ageIDeck.size();i++)
			if (m_ageIDeck[i]->getId() == searchId)
				return m_ageIDeck[i];
	}

	if (m_currentAge == Building::Age::AGEII)
	{
		for (int i = 0; i < m_ageIIDeck.size(); i++)
			if (m_ageIIDeck[i]->getId() == searchId)
				return m_ageIIDeck[i];
	}

	if (m_currentAge == Building::Age::AGEIII)
	{
		for (int i = 0; i < m_ageIIIDeck.size(); i++)
			if (m_ageIIIDeck[i]->getId() == searchId)
				return m_ageIIIDeck[i];
	}
}

bool CheckPlayerResources(const std::unique_ptr<Player>& player, const std::shared_ptr<Building>& building)
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

bool CheckPlayerCoins(const std::unique_ptr<Player>& player, const std::shared_ptr<Building>& building)
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
		for (auto lastRowCard : m_cardDisplay[m_cardDisplay.size() - 1])
		{
			if (lastRowCard.has_value())
			if (id == lastRowCard.value().getBuilding()->getId())
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
void Game::removeCardFromDeck(std::uint8_t id)
{
	for (auto row : m_cardDisplay)
	{
		for (auto cell : row)
		{
			if(cell.has_value())
			{
				if (cell.value().getBuilding()->getId() == id)
				{
					cell=std::nullopt;
					return;
				}
			}
		}
	}
}
/*
To do:
Make it so that wonders actually have an effect
Implement correct functionality for each age deck
*/
void Game::run()
{
	std::unique_ptr<Player> currentPlayer = std::make_unique<Player>(m_player1);
	std::unique_ptr<Player> otherPlayer = std::make_unique<Player>(m_player2);
	bool player1Turn= true;
	initAgeIBoard();
	m_currentAge = Building::Age::AGEI;
	std::uint8_t move;
	while (!endGame)
	{
		displayBoard();
		std::cout << "1.build\n2.discard\n3.wonder\nmove:";
		std::cin >> move;
		if (move == '1')
		{
			std::shared_ptr <Building> building = selectAcceptableCard();
			if(CheckPlayerResources(currentPlayer,building) && CheckPlayerCoins(currentPlayer, building))
				currentPlayer->addBuilding(*building);
			else
			{
				std::cout << "You don't have enough resources/coins to build this building. Retry\n";
				continue;
			}


			if (player1Turn)
				m_board.setPos(m_board.getPos() + building->getShields());
			else
				m_board.setPos(m_board.getPos() - building->getShields());

			removeCardFromDeck(building->getId());
		}
		if (move == '2')
		{
			std::shared_ptr <Building> building = selectAcceptableCard();
			std::uint8_t profit = 2 + currentPlayer->getYellowBuildings().size();
			currentPlayer->addCoin(profit);
			m_discardedCards.push_back(building);
		}
		if (move == '3')
		{
			std::cout << "WIP\n";
		}

		std::swap(currentPlayer, otherPlayer);
		player1Turn = !player1Turn;
		system("cls");
	}
}
	
