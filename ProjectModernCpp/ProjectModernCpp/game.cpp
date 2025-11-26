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
	std::uniform_int_distribution<> dist1(0, k_boardSize - 1);
	std::vector<std::shared_ptr<Card>> copyDeck = m_ageIDeck;
	for (int i = 0; i < k_boardSize; ++i)
	{
		std::uniform_int_distribution<> dist2(0, copyDeck.size() - 1);
		std::pair<std::uint16_t, bool> card;
		std::uint16_t index1 = dist2(gen);
		card.first = copyDeck[index1].get()->getId();
		copyDeck.erase(copyDeck.begin() + index1);
		while (true) {
			std::uint16_t index2 = dist1(gen);

			if ((index2 >= 2 && index2 <= 4) || (index2 >= 9 && index2 <= 13)) card.second = false;
			else card.second = true;
			if (cardDisplay[index2].first == 0)
			{
				cardDisplay[index2] = card;
				break;
			}
		}
	}
}

void Game::displayAgeIBoard()
{
	for (int i = 0; i < cardDisplay.size(); ++i)
	{
		if (cardDisplay[i].second) std::cout << "[" << cardDisplay[i].first << "] ";
		else std::cout << "[hidden]";
		if (i == 1 || i == 4 || i == 8 || i == 13) std::cout << "\n";
	}
}
	
