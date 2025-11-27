module game;



Game::Game(const Player& player1, const Player& player2,
	const Board& board,
	const std::vector<std::shared_ptr<Card>>& wondersCard,
	const std::vector<std::shared_ptr<Card>>& ageIDeck,
	const std::vector<std::shared_ptr<Card>>& ageIIDeck,
	const std::vector<std::shared_ptr<Card>>& ageIIIDeck,
	const std::vector<std::shared_ptr<Card>>& discardedCards) : m_player1(player1), m_player2(player2), m_board(board), m_wondersDeck(wondersCard),
	m_ageIDeck(ageIDeck), m_ageIIDeck(ageIIDeck), m_ageIIIDeck(ageIIIDeck), m_discardedCards(discardedCards)
{
}

void Game::initAgeIBoard()
{
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::vector<std::shared_ptr<Card>> copyDeck = m_ageIDeck;
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
	std::vector<std::shared_ptr<Card>> copyDeck = m_ageIIDeck;
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
	std::vector<std::shared_ptr<Card>> copyDeck = m_ageIIIDeck;
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
	
