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
		std::vector<std::pair<std::uint16_t, bool>> row;
		for (int j = 0; j < i + 2; ++j)
		{
			std::uniform_int_distribution<> dist(0, copyDeck.size() - 1);
			std::pair<std::uint16_t, bool> card;
			std::uint16_t index1 = dist(gen);
			card.first = copyDeck[index1].get()->getId();
			copyDeck.erase(copyDeck.begin() + index1);
			if (!(i % 2)) card.second = true;
			row.push_back(card);
			
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
		std::vector<std::pair<std::uint16_t, bool>> row;
		for (int j = 0; j < i + 1; ++j)
		{
			std::uniform_int_distribution<> dist(0, copyDeck.size() - 1);
			std::pair<std::uint16_t, bool> card;
			std::uint16_t index1 = dist(gen);
			card.first = copyDeck[index1].get()->getId();
			copyDeck.erase(copyDeck.begin() + index1);
			if (!(i % 2)) card.second = true;
			row.push_back(card);

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
			std::pair<std::uint16_t, bool> card;
			std::uint16_t index1 = dist(gen);
			card.first = copyDeck[index1].get()->getId();
			copyDeck.erase(copyDeck.begin() + index1);
			if (!(i % 2)) card.second = true;
			m_cardDisplay[i][j] = card;
		}
	}
}

void Game::displayBoard()
{
	for (int i = 0; i < m_cardDisplay.size(); ++i)
	{
		for (int j = 0; j < m_cardDisplay[i].size(); ++j)
		{

			if (m_cardDisplay[i][j].second) std::cout << "[" << m_cardDisplay[i][j].first << "] ";
			else std::cout << "[hidden]";
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

void Game::run()
{
	std::unique_ptr<Player> currentPlayer = std::make_unique<Player>(m_player1);
	std::unique_ptr<Player> otherPlayer = std::make_unique<Player>(m_player2);
	initAgeIBoard();
	m_currentAge = Building::Age::AGEI;
	std::uint8_t move;
	while (!endGame)
	{
		displayBoard();
		std::cout << "1.build\n2.discard\n3.wonder\nmove:";
		std::cin >> move;
		std::cout << move;
		if (move == '1')
		{
			int id;
			bool acceptableCard;
			do
			{
				std::cout << "card id:";
				std::cin >> id;
				acceptableCard = 0;
				for (auto lastRowCard:m_cardDisplay[m_cardDisplay.size()-1])
				{
					if (id == lastRowCard.first)
					{
						acceptableCard = 1;
						break;
					}
				}
				if (!acceptableCard)
					std::cout << "Bad Card. Choose again\n";
			} while (!acceptableCard);

			currentPlayer->addBuilding(Building());
		}
		if (move == '2')
		{

		}
		if (move == '3')
		{

		}
		//system("cls");
	}
}
	
