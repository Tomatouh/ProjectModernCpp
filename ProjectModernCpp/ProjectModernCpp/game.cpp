#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <fstream>
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
m_discardedCards(std::make_shared<std::vector<std::shared_ptr<Building>>>()),
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
void Game::loadGame()
{
	std::ifstream f("save.txt", std::ios::in);
	if (!f)
		return;
	else
	{
		//load game state from file
	}
}
void Game::saveGame()
{
	std::ofstream f("save.txt", std::ios::out);
	std::vector<Building> playerBuildings;

	f << "common ";
	f << "age " << static_cast<int>(this->m_currentAge) << "\n";

	f << "peon " << this->m_board.getPos() << "\n";
	std::vector<bool>ZT = this->m_board.getZoneTriggers();
	f << "zTriggers ";
	for (int i = 0; i < ZT.size(); i++)
	{
		f << ZT[i] << " ";
	}
	f << "\n";

	f << "progressBoard ";
	//std::vector< std::unique_ptr<Player::ProgressToken>>
	for (int i = 0; i < this->m_progressTokensDeck.size(); i++)
	{
		f << this->m_progressTokensDeck[i].get()->getId() << " ";
	}
	f << "\n";
	f << "discard ";
	for (int i = 0; i < this->m_discardedCards->size(); i++) {
		auto it = this->m_discardedCards->begin();
		std::advance(it, i);
		f << it->get()->getId() << " ";
	}
	f << "\n";
	f << "gui" << "\n";
	for (auto& row : m_cardDisplay) {
		for (auto& card : row)
		{
			if (card.has_value())
			{
				f << card.value().getBuilding()->getId() << " ";
			}
			else
			{
				f << "missing" << " ";
			}
		}
		f << "\n";
	}
	f << "playerCURRENT" << "\n";

	playerBuildings = this->m_currentPlayer->getAllBuildings();
	f << "b ";
	for (int i = 0; i < this->m_currentPlayer->getBuildingCount(); i++) {
		f << playerBuildings[i].getId() << " ";
	}
	f << "\n";
	f << "c " << this->m_currentPlayer->getCoins() << "\n";
	f << "vp " << this->m_currentPlayer->getVictoryPoints() << "\n";
	f << "s " << this->m_currentPlayer->getShields() << "\n";

	f << "p " << this->m_currentPlayer->getWood() << " " << this->m_currentPlayer->getStone() << " "
		<< this->m_currentPlayer->getClay() << " " << this->m_currentPlayer->getGlass() << " "
		<< this->m_currentPlayer->getPapyrus() << "\n";
	f << "science ";
	std::vector<uint16_t> sci_Points = this->m_currentPlayer->getScientificPoints();
	for (int i = 0; i < sci_Points.size(); i++)
	{
		f << sci_Points[i] << " ";
	}
	f << "\n";
	f << "progress ";
	f << this->m_currentPlayer->hasAgricultureProgressToken() << " "
		<< this->m_currentPlayer->hasArchitectureProgressToken() << " "
		<< this->m_currentPlayer->hasEconomyProgressToken() << " "
		<< this->m_currentPlayer->hasLawProgressToken() << " "
		<< this->m_currentPlayer->hasMasonryProgressToken() << " "
		<< this->m_currentPlayer->hasMathematicsProgressToken() << " "
		<< this->m_currentPlayer->hasPhilosophyProgressToken() << " "
		<< this->m_currentPlayer->hasStrategyProgressToken() << " "
		<< this->m_currentPlayer->hasTheologyProgressToken() << " "
		<< this->m_currentPlayer->hasUrbanismProgressToken() << "\n";
	f << "\n";
	f << "wonder ";
	for (int i = 0; i < this->m_currentPlayer->getWonders().size(); i++)
	{
		f << this->m_currentPlayer->getWonders()[i].first->getId() << " ";
		if (this->m_currentPlayer->getWonders()[i].second.has_value())
			switch (this->m_currentPlayer->getWonders()[i].second.value()->getAge())
			{
			case Building::Age::AGEI:
				f << "1" << " ";
				break;
			case Building::Age::AGEII:
				f << "2" << " ";
				break;
			case Building::Age::AGEIII:
				f << "3" << " ";
				break;
			}
		else
			f << "0" << " ";
	}

	f << "playerOTHER" << "\n";
	playerBuildings.clear();
	playerBuildings = this->m_otherPlayer->getAllBuildings();
	f << "b ";
	for (int i = 0; i < this->m_otherPlayer->getBuildingCount(); i++) {
		f << playerBuildings[i].getId() << " ";
	}
	f << "\n";

	f << "c " << this->m_otherPlayer->getCoins() << "\n";
	f << "vp " << this->m_otherPlayer->getVictoryPoints() << "\n";
	f << "s " << this->m_otherPlayer->getShields() << "\n";

	f << "p " << this->m_otherPlayer->getWood() << " " << this->m_otherPlayer->getStone() << " "
		<< this->m_otherPlayer->getClay() << " " << this->m_otherPlayer->getGlass() << " "
		<< this->m_otherPlayer->getPapyrus() << "\n";
	f << "science ";
	std::vector<uint16_t> sciPoints = this->m_otherPlayer->getScientificPoints();
	for (int i = 0; i < sciPoints.size(); i++)
	{
		f << sciPoints[i] << " ";
	}
	f << "\n";
	f << "progress ";
	f << this->m_otherPlayer->hasAgricultureProgressToken() << " "
		<< this->m_otherPlayer->hasArchitectureProgressToken() << " "
		<< this->m_otherPlayer->hasEconomyProgressToken() << " "
		<< this->m_otherPlayer->hasLawProgressToken() << " "
		<< this->m_otherPlayer->hasMasonryProgressToken() << " "
		<< this->m_otherPlayer->hasMathematicsProgressToken() << " "
		<< this->m_otherPlayer->hasPhilosophyProgressToken() << " "
		<< this->m_otherPlayer->hasStrategyProgressToken() << " "
		<< this->m_otherPlayer->hasTheologyProgressToken() << " "
		<< this->m_otherPlayer->hasUrbanismProgressToken() << "\n";
	f << "\n";
	f << "wonder ";
	for (int i = 0; i < this->m_otherPlayer->getWonders().size(); i++)
	{
		f << this->m_otherPlayer->getWonders()[i].first->getId() << " ";
		if (this->m_otherPlayer->getWonders()[i].second.has_value())
			switch (this->m_otherPlayer->getWonders()[i].second.value()->getAge())
			{
			case Building::Age::AGEI:
				f << "1" << " ";
				break;
			case Building::Age::AGEII:
				f << "2" << " ";
				break;
			case Building::Age::AGEIII:
				f << "3" << " ";
				break;
			}
		else
			f << "0" << " ";
	}
	f << "\n";



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
		for (int j = 0; j < i + 1; ++j)
		{
			std::uniform_int_distribution<> dist(0, copyDeck.size() - 1);
			displayCard card;
			auto it = copyDeck.begin();
			std::advance(it, dist(gen));

			card.setBuilding(it->second);
			std::uint16_t keyToErase = it->first;
			copyDeck.erase(keyToErase);
			if (i % 2)
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
		{Card::Effect::constructCard, [](Game& game) {game.m_waitingForDiscardedChoice = true; }},
		{Card::Effect::discardBrown, [](Game& game) { game.m_waitingToDiscardBrown = true; }},
		{Card::Effect::discardGrey, [](Game& game) { game.m_waitingToDiscardBrown = true; }},
		{Card::Effect::drawProgress, [](Game& game) { game.m_waitingForTokenSelection = true; }},
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
		{Card::Effect::oneCoinWood, [](Game& game) {game.m_currentPlayer->addTradeDiscount(ResourceType::WOOD); }},
		{Card::Effect::playSecondTurn,[](Game& game) {game.m_currentPlayer->setSecondTurn(true); }}

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
	for (int i = 0; i < 5; ++i)
	{
		std::uniform_int_distribution<> dist(0, m_progressTokensDeck.size() - 1);
		std::uint16_t index = dist(gen);
		m_remainingProgressTokens.emplace_back(std::move(m_progressTokensDeck[index]));
		m_progressTokensDeck.erase(m_progressTokensDeck.begin() + index);
	}

}

std::shared_ptr<Building> Game::getBuildingById(std::uint8_t searchId)
{
	if (m_ageIDeck[searchId])
		return m_ageIDeck[searchId];

	if (m_ageIIDeck[searchId])
		return m_ageIIDeck[searchId];

	if (m_ageIIIDeck[searchId])
		return m_ageIIIDeck[searchId];
}
std::shared_ptr<Card> Game::getWonderById(std::uint8_t searchId)
{
	auto it = std::find_if(m_wondersDeck.begin(), m_wondersDeck.end(),
		[searchId](const std::shared_ptr<Card>& card) {
			return card && card->getId() == searchId;
		});
	return it != m_wondersDeck.end() ? *it : nullptr;
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
void Game::removeCardFromDeck(std::uint8_t id, bool discarded)
{
	for (int i = 0; i < m_cardDisplay.size(); i++)
		for (int j = 0; j < m_cardDisplay[i].size(); j++) {
			if (m_cardDisplay[i][j].has_value())
			{
				if (m_cardDisplay[i][j].value().getBuilding()->getId() == id)
				{
					if (discarded)
					{
						m_discardedCards->emplace_back(m_cardDisplay[i][j].value().getBuilding());
					}
					m_cardDisplay[i][j] = std::nullopt;
					m_guiCardDisplay.erase(id);
					break;
				}
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
	if (m_currentAge == Building::Age::AGEI)
	{
		for (int i = m_cardDisplay.size() - 2; i >= 0; i--)
			for (int j = 0; j < m_cardDisplay[i].size(); j++)
				if (m_cardDisplay[i][j].has_value())
					if (m_cardDisplay[i][j].value().isFaceUp() == false && m_cardDisplay[i + 1][j].has_value() == false && m_cardDisplay[i + 1][j + 1].has_value() == false)
					{
						m_cardDisplay[i][j].value().setFaceUp(true);
						std::uint16_t faceUpCardIndex = m_cardDisplay[i][j].value().getBuilding()->getId();
						sf::Texture texture;
						texture.loadFromFile("..\\..\\Images\\" + std::to_string(faceUpCardIndex) + ".jpg");
						m_guiCardDisplay[faceUpCardIndex].value().setTexture(texture);
					}

	}
	if (m_currentAge == Building::Age::AGEII)
	{
		for (int i = m_cardDisplay.size() - 2; i >= 0; i--)
		{
			for (int j = 0; j < m_cardDisplay[i].size(); j++)
			{
				if (m_cardDisplay[i][j].has_value())
				{
					auto& card = m_cardDisplay[i][j].value();

					if (!card.isFaceUp())
					{
						bool isCovered = false;

						if (j > 0 && m_cardDisplay[i + 1][j - 1].has_value()) {
							isCovered = true;
						}

						if (j < m_cardDisplay[i + 1].size() && m_cardDisplay[i + 1][j].has_value()) {
							isCovered = true;
						}

						if (!isCovered)
						{
							card.setFaceUp(true);
							std::uint16_t faceUpCardIndex = card.getBuilding()->getId();

							sf::Texture texture;
							texture.loadFromFile("..\\..\\Images\\" + std::to_string(faceUpCardIndex) + ".jpg");
							m_guiCardDisplay[faceUpCardIndex].value().setTexture(texture);
						}
					}
				}
			}
		}
	}if (m_currentAge == Building::Age::AGEIII)
	{
		for (int i = m_cardDisplay.size() - 2; i >= 0; i--)
		{
			for (int j = 0; j < m_cardDisplay[i].size(); j++)
			{
				if (m_cardDisplay[i][j].has_value())
				{
					auto& card = m_cardDisplay[i][j].value();
					if (card.isFaceUp()) continue;

					bool isCovered = false;

					if (i == 3)
					{
						int startIndex = (j == 0) ? 0 : 2;
						if (m_cardDisplay[i + 1][startIndex].has_value() ||
							m_cardDisplay[i + 1][startIndex + 1].has_value())
						{
							isCovered = true;
						}
					}
					else if (m_cardDisplay[i + 1].size() > m_cardDisplay[i].size())
					{
						if (m_cardDisplay[i + 1][j].has_value() ||
							m_cardDisplay[i + 1][j + 1].has_value())
						{
							isCovered = true;
						}
					}
					else
					{
						int targetJ = j / 2;
						if (m_cardDisplay[i + 1][targetJ].has_value())
						{
							isCovered = true;
						}
					}

					if (!isCovered)
					{
						card.setFaceUp(true);
						std::uint16_t id = card.getBuilding()->getId();

						static std::map<uint16_t, sf::Texture> textureCache;
						if (textureCache.find(id) == textureCache.end()) {
							textureCache[id].loadFromFile("..\\..\\Images\\" + std::to_string(id) + ".jpg");
						}
						m_guiCardDisplay[id].value().setTexture(textureCache[id]);
					}
				}
			}
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
void drawClickAreaForPlayerDetails(sf::RenderWindow& window)
{
	constexpr float boxWidth = 170.f;
	constexpr float boxHeight = 50.f;
	const float leftX = 175.f;
	const float rightX = static_cast<float>(window.getSize().x) - boxWidth - leftX;
	const float yPos = static_cast<float>(window.getSize().y) - boxHeight - 10.f;
	sf::RectangleShape leftBox(sf::Vector2f(boxWidth, boxHeight));
	leftBox.setPosition({ leftX, yPos });
	leftBox.setFillColor(sf::Color(200, 200, 200, 100));
	leftBox.setOutlineColor(sf::Color::Black);
	leftBox.setOutlineThickness(2.f);
	sf::RectangleShape rightBox(sf::Vector2f(boxWidth, boxHeight));
	rightBox.setPosition({ rightX, yPos });
	rightBox.setFillColor(sf::Color(200, 200, 200, 100));
	rightBox.setOutlineColor(sf::Color::Black);
	rightBox.setOutlineThickness(2.f);
	window.draw(leftBox);
	window.draw(rightBox);

	const sf::Font font = []() {
		sf::Font font("C:\\Windows\\Fonts\\cour.ttf");
		return font;
		}();

	sf::Text leftText(font, "Player 1 Details", 16);
	leftText.setFillColor(sf::Color::Blue);
	leftText.setPosition({ leftX + 5.f, yPos + 10.f });
	sf::Text rightText(font, "Player 2 Details", 16);
	rightText.setFillColor(sf::Color::Red);
	rightText.setPosition({ rightX + 5.f, yPos + 10.f });
	window.draw(leftText);
	window.draw(rightText);


}



std::pair<int, int> getNextCardPosition(Building::Age age)
{

	if (age == Building::Age::AGEI)
	{
		static int x = 647;
		static int y = 10;
		static std::uint8_t maxRowCards = 2;
		static std::uint8_t currentRowCard = 0;
		static std::uint8_t centeringOffset = 1;
		if (x == 647 && y == 10)
		{
			currentRowCard = 1;
			x += BoxSizes::boxHeight;
			return { 647,10 };
		}
		if (currentRowCard == maxRowCards)
		{
			x = x - (maxRowCards + centeringOffset) * BoxSizes::boxHeight / 2;
			y += BoxSizes::boxHeight * 0.75 + 5;
			currentRowCard = 1;
			maxRowCards++;
			centeringOffset++;
			return { x,y };
		}
		else
		{
			if (y != 10)
				x += BoxSizes::boxHeight;
			currentRowCard++;
			return { x,y };
		}
	}
	if (age == Building::Age::AGEII)
	{
		static int x = 400;
		static int y = 10;
		static std::uint8_t maxRowCards = 6;
		static std::uint8_t currentRowCard = 0;
		static std::uint8_t centeringOffset = 3;
		static bool firstCall = true;
		if (x == 400 && y == 10)
		{
			currentRowCard = 1;
			x = x + BoxSizes::boxHeight;
			return { 400,10 };
		}
		if (currentRowCard == maxRowCards)
		{
			x = x - (maxRowCards + centeringOffset) * BoxSizes::boxHeight / 2;
			y += BoxSizes::boxHeight * 0.75 + 5;
			currentRowCard = 1;
			maxRowCards--;
			centeringOffset--;
			return { x,y };
		}
		else
		{
			if (!firstCall)
				x += BoxSizes::boxHeight;
			firstCall = false;
			currentRowCard++;
			return { x,y };
		}
	}
	if (age == Building::Age::AGEIII)
	{
		static int x = 647;
		static int y = 10;
		static std::uint8_t maxRowCards = 2;
		static std::uint8_t currentRowCard = 0;
		static std::uint8_t centeringOffset = 1;
		static bool firstSectionDone = false;
		static bool secondSectionDone = false;
		static bool thirdSectionDone = false;

		static bool firstCall = true;
		if (!firstSectionDone)
		{
			if (x == 647 && y == 10)
			{
				currentRowCard = 1;
				x += BoxSizes::boxHeight;
				return { 647,10 };
			}
			if (currentRowCard == maxRowCards)
			{
				x = x - (maxRowCards + centeringOffset) * BoxSizes::boxHeight / 2;
				y += BoxSizes::boxHeight * 0.75 + 5;
				currentRowCard = 1;
				maxRowCards++;
				centeringOffset++;
				if (maxRowCards == 5)
				{
					firstSectionDone = true;
					currentRowCard = 0;
				}
				else
					return { x,y };
			}
			else
			{
				if (y != 10)
					x += BoxSizes::boxHeight;
				currentRowCard++;
				return { x,y };
			}
		}
		if (!secondSectionDone)
		{
			if (currentRowCard == 0)
				x = 647 - BoxSizes::boxHeight / 2;
			else
				x += BoxSizes::boxHeight * 2;
			currentRowCard++;
			if (currentRowCard == 2)
			{
				secondSectionDone = true;
				currentRowCard = 0;
				maxRowCards = 4;
				centeringOffset = 1;
				auto auxX = x;
				auto auxY = y;
				y += BoxSizes::boxHeight * 0.75 + 5;
				x = 647 - BoxSizes::boxHeight;
				return { auxX,auxY };

			}
			return { x,y };
		}
		if (!thirdSectionDone)
		{
			if (currentRowCard == 0)
			{
				currentRowCard = 1;
				x = x + BoxSizes::boxHeight;
				return { x - BoxSizes::boxHeight,y };
			}
			if (currentRowCard == maxRowCards)
			{
				x = x - (maxRowCards + centeringOffset) * BoxSizes::boxHeight / 2;
				y += BoxSizes::boxHeight * 0.75 + 5;
				currentRowCard = 1;
				maxRowCards--;
				centeringOffset--;
				return { x,y };
			}
			else
			{
				if (!firstCall)
					x += BoxSizes::boxHeight;
				firstCall = false;
				currentRowCard++;
				return { x,y };
			}if (currentRowCard == 0)
				x = 647 - BoxSizes::boxHeight;
			else
				x += BoxSizes::boxHeight;
			currentRowCard++;
			if (currentRowCard == 4)
			{
				thirdSectionDone = true;
				currentRowCard = 0;
			}
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
					std::uint16_t id = card.value().getBuilding()->getId();
					auto pos = getNextCardPosition(m_currentAge);
					guiCard gCard = card.value().getGuiCard();
					gCard.setPosition(pos);
					card.value().setPosition(pos);
					sf::Texture texture;
					texture.loadFromFile("..\\..\\Images\\" + std::to_string(id) + ".jpg");
					gCard.setTexture(texture);
					m_guiCardDisplay.insert({ id, gCard });
					window.draw(gCard);
				}
				else
				{
					auto pos = getNextCardPosition(m_currentAge);

					guiCard gCard = card.value().getGuiCard();
					std::string currentAgeNumber;
					switch (m_currentAge)
					{
					case Building::Age::AGEI:
					{
						currentAgeNumber = "I";
						break;
					}
					case Building::Age::AGEII:
					{
						currentAgeNumber = "II";
						break;
					}
					case Building::Age::AGEIII:
					{
						currentAgeNumber = "III";
						break;
					}
					default:
						break;
					}
					sf::Texture texture;
					texture.loadFromFile("..\\..\\Images\\Miscellaneous\\age " + currentAgeNumber + " deck.png");
					gCard.setTexture(texture);
					gCard.setPosition(pos);
					card.value().setPosition(pos);
					m_guiCardDisplay.insert({ card.value().getBuilding()->getId(), gCard });

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
				auto gCard = m_guiCardDisplay[card.value().getBuilding()->getId()].value();
				gCard.setPosition(card.value().getPosition());
				window.draw(gCard);
			}
		}
}

void drawCardSet(const std::vector<Building>& Buildings, int xPos, int& yPos, sf::RenderWindow& window, bool isLeft)
{
	int spacing = 5;

	for (const auto& card : Buildings) {

		auto cardPtr = std::make_shared<Building>(card);
		sf::Texture cardTexture;
		cardTexture.loadFromFile("..\\..\\Images\\" + std::to_string(cardPtr->getId()) + ".jpg");
		guiCard gCard(cardPtr);
		gCard.setSize(sf::Vector2f(static_cast<float>(BoxSizes::boxWidth / 2.f), static_cast<float>(BoxSizes::boxHeight / 2.f)));
		gCard.setPosition({ xPos, yPos });
		gCard.setTexture(cardTexture);
		window.draw(gCard);
		//yPos += BoxSizes::boxHeight / 2 + spacing;
		if (isLeft)
			xPos += BoxSizes::boxWidth / 2 + spacing;
		else
			xPos -= BoxSizes::boxWidth / 2 + spacing;
	}
	yPos += BoxSizes::boxHeight / 2 + spacing;
}

int drawPlayerColumn(const std::shared_ptr<Player>& player, int xPos, sf::RenderWindow& window) {
	int yPos = 20;
	if (player->name() == "player1") {
		drawCardSet(player->getBrownBuildings(), xPos, yPos, window, true);
		drawCardSet(player->getGreyBuildings(), xPos, yPos, window, true);
		drawCardSet(player->getYellowBuildings(), xPos, yPos, window, true);
		drawCardSet(player->getRedBuildings(), xPos, yPos, window, true);
		drawCardSet(player->getGreenBuildings(), xPos, yPos, window, true);
		drawCardSet(player->getBlueBuildings(), xPos, yPos, window, true);
		drawCardSet(player->getPurpleBuildings(), xPos, yPos, window, true);
	}
	else {
		drawCardSet(player->getBrownBuildings(), xPos, yPos, window, false);
		drawCardSet(player->getGreyBuildings(), xPos, yPos, window, false);
		drawCardSet(player->getYellowBuildings(), xPos, yPos, window, false);
		drawCardSet(player->getRedBuildings(), xPos, yPos, window, false);
		drawCardSet(player->getGreenBuildings(), xPos, yPos, window, false);
		drawCardSet(player->getBlueBuildings(), xPos, yPos, window, false);
		drawCardSet(player->getPurpleBuildings(), xPos, yPos, window, false);

	}

	return yPos;
}

void drawPlayerWonders(const std::shared_ptr<Player>& player, int xPos, int startYPos, sf::RenderWindow& window)
{
	float spacing = 23.0f;
	int wonderYPos = startYPos;

	const int winW = static_cast<int>(window.getSize().x);
	const int cardW = static_cast<int>(BoxSizes::boxHeight);
	const int margin = 20;

	//if (xPos >= winW - cardW - margin /*&&*/) xPos -= 420;

	for (const auto& wonderPair : player->getWonders()) {
		auto wonderPtr = wonderPair.first;
		sf::Texture texture("..\\..\\Images\\Wonders\\" + std::to_string(wonderPtr->getId()) + ".jpg");

		guiCard gCard(wonderPtr);

		gCard.setSize(sf::Vector2f(static_cast<float>(BoxSizes::boxHeight), static_cast<float>(BoxSizes::boxWidth)));
		gCard.setPosition({ xPos, wonderYPos });
		if (wonderPair.second.has_value()) {
			gCard.setHighlighted(true);
		}
		gCard.setTexture(texture);
		if (wonderPair.second.has_value())
		{
			auto ageCard = wonderPair.second.value()->getAge();
			sf::Texture ageTexture;
			std::string ageNumber;
			switch (ageCard)
			{
			case Building::Age::AGEI:
			{
				ageNumber = "I";
				break;
			}
			case Building::Age::AGEII:
			{
				ageNumber = "II";
				break;
			}
			case Building::Age::AGEIII:
			{
				ageNumber = "III";
				break;
			}
			}
			ageTexture.loadFromFile("..\\..\\Images\\Miscellaneous\\age " + ageNumber + " deck.png");
			sf::Sprite ageSprite(ageTexture);
			ageSprite.setScale({ 0.1f, 0.1f });
			if (player->name() == "player1")
			{
				sf::Angle angle = sf::degrees(90.f);
				ageSprite.rotate(angle);
				ageSprite.setPosition({ xPos + 150.f, wonderYPos + 14.f });
			}
			else
			{
				sf::Angle angle = sf::degrees(270.f);
				ageSprite.rotate(angle);
				ageSprite.setPosition({ xPos - 25.f, wonderYPos + 70.f });
			}
			window.draw(ageSprite);
		}
		window.draw(gCard);
		wonderYPos += BoxSizes::boxWidth + spacing;
	}
}

void Game::drawPlayerCards(sf::RenderWindow& window)
{
	constexpr int spacing = 5;
	const auto winSize = window.getSize();
	const int winWidth = static_cast<int>(winSize.x);
	const int leftX = 10;
	int rightX = std::max(20, winWidth - static_cast<int>(BoxSizes::boxWidth / 2) - 20);
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
	drawPlayerColumn(leftPlayer, leftX, window);
	drawPlayerColumn(rightPlayer, rightX, window);
	/*int leftBottomY = drawPlayerColumn(leftPlayer, leftX, window);
	int rightBottomY = drawPlayerColumn(rightPlayer, rightX, window);*/
	int bottomY = 485.0f;
	rightX = winWidth - static_cast<int>(BoxSizes::boxHeight) - 10;


	drawPlayerWonders(leftPlayer, leftX, bottomY, window);
	drawPlayerWonders(rightPlayer, rightX, bottomY, window);

}

bool Game::selectCardEffect(sf::RenderWindow& window, sf::Vector2i&& mousePos)
{
	bool anySelected = findSelectedCard(mousePos, window);
	window.draw(m_backgroundSprite);
	redrawCurrentAgeCards(window);
	drawPlayerCards(window);
	//window.display();
	return anySelected;
}

std::pair<int, int> Game::getWonderPosition(int index, const sf::RenderWindow& window)
{
	int total = static_cast<int>(m_wondersDisplay.size());
	const int cardW = BoxSizes::boxHeight * 2;
	const int cardH = BoxSizes::boxWidth * 2;
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
	const int cardW = BoxSizes::boxHeight * 2;
	const int cardH = BoxSizes::boxWidth * 2;
	for (int i = 0; i < total; ++i) {
		auto pos = getWonderPosition(i, window);
		sf::FloatRect rect(sf::Vector2f(pos.first, pos.second), sf::Vector2f(cardW, cardH));
		if (rect.contains(worldPos)) return i;
	}
	return -1;
}

void Game::drawWondersSelection(sf::RenderWindow& window)
{
	int total = 4;
	const float cardW = BoxSizes::boxHeight * 2;
	const float cardH = BoxSizes::boxWidth * 2;
	if (m_gamestate == GAMESTART)
	{
		std::vector<guiCard> guiWonders;
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



		for (int i = 0; i < total; ++i)
		{
			auto pos = getWonderPosition(i, window);

			if (m_wondersDisplay[i].has_value())
			{
				sf::Texture texture("..\\..\\Images\\Wonders\\" + std::to_string(m_wondersDisplay[i].value()->getId()) + ".jpg");
				guiCard gCard(m_wondersDisplay[i].value());
				gCard.setPosition(pos);
				gCard.setSize({ cardW, cardH });
				gCard.setTexture(texture);
				window.draw(gCard);
			}
		}
	}
	if (m_gamestate == ONGOING)
	{
		m_wondersDisplay.clear();
		total = 0;
		for (auto& wonderPair : m_currentPlayer->getWonders())
		{
			if (!wonderPair.second.has_value())
			{
				m_wondersDisplay.push_back(std::make_optional(wonderPair.first));
				total++;
			}
		}

		for (int i = 0; i < total; ++i)
		{
			auto pos = getWonderPosition(i, window);

			if (m_wondersDisplay[i].has_value())
			{
				sf::Texture texture("..\\..\\Images\\Wonders\\" + std::to_string(m_wondersDisplay[i].value()->getId()) + ".jpg");
				guiCard gCard(m_wondersDisplay[i].value());
				gCard.setPosition(pos);
				gCard.setSize({ cardW, cardH });
				gCard.setTexture(texture);
				window.draw(gCard);
			}
		}

	}
}

void Game::wondersSetup(sf::RenderWindow& window, const sf::Vector2i mousePos)
{
	static int step = 1;
	if (m_gamestate == GAMESTART) {
		if (step <= 2) {
			static int iteration = 1;
			if (iteration <= 4) {
				//PollEvents(window);
					//sf::Vector2i mousePos = sf::Mouse::getPosition(window);
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


					window.draw(m_backgroundSprite);
					drawWondersSelection(window);
					window.display();
					if (iteration > 4)
					{
						m_wondersDisplay.clear();
						step++;
						iteration = 1;
						if (step == 2)
						{
							window.draw(m_backgroundSprite);
							drawWondersSelection(window);
							window.display();
						}
					}
					/*while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && window.isOpen()) {
						PollEvents(window);
						sf::sleep(sf::milliseconds(10));
					}*/
				}
			}
		}

		if (step > 2)
			m_gamestate = ONGOING;
	}
}

void Game::drawConstructionChoices(sf::RenderWindow& window)
{
	ChoiceBox box;
	box.setPosition({ static_cast<float>(window.getSize().x) / 2 - 250.f, static_cast<float>(window.getSize().y) - 50.f });
	window.draw(box);
	box.drawOptions(window);
}

bool Game::selectToken(sf::RenderWindow& window, const sf::Vector2i& mousePos)
{
	sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
	const float xPosStart = static_cast<float>(window.getSize().x) / 2.f - (m_progressTokensDeck.size() * 148.f) / 2.f;
	const float yPos = static_cast<float>(window.getSize().y) / 2.f - 75.f;
	const float tokenBoxWidth = 100.f;
	const float tokenBoxHeight = 80.f;
	for (int i = 0; i < m_progressTokensDeck.size(); ++i) {
		sf::FloatRect tokenRect(
			sf::Vector2f(xPosStart + i * 154, yPos),
			sf::Vector2f(tokenBoxWidth, tokenBoxHeight)
		);
		if (tokenRect.contains(worldPos)) {
			m_currentPlayer->addProgressToken(*(m_progressTokensDeck[i]));
			m_progressTokensDeck[i]->applyEffect(m_currentPlayer);
			m_progressTokensDeck.erase(m_progressTokensDeck.begin() + i);
			return true;
		}
	}
	return false;
}
int Game::getConstructionOption(sf::RenderWindow& window, const sf::Vector2i& mousePos)
{
	sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

	int numberOfOptions = 3;
	const float xPosStart = static_cast<float>(window.getSize().x) / 2 - 245.f;
	const float yPos = static_cast<float>(window.getSize().y) - 50.f;

	for (int i = 0; i < numberOfOptions; ++i) {
		sf::FloatRect optionRect(
			sf::Vector2f(xPosStart + i * (ChoiceBoxSizes::boxWidth / 3), yPos),
			sf::Vector2f(static_cast<float>(ChoiceBoxSizes::optionBoxWidth), static_cast<float>(ChoiceBoxSizes::optionBoxHeight))
		);
		if (optionRect.contains(worldPos)) {
			return i;
		}
	}
	return -1;

}

int Game::chooseConstructionOption(sf::RenderWindow& window, const sf::Vector2i& mousePos)
{
	int option = getConstructionOption(window, mousePos);
	std::uint16_t sellProfit = 2 + m_currentPlayer->getYellowBuildings().size();

	std::shared_ptr<Player> leftPlayer = nullptr, rightPlayer = nullptr;

	switch (option)
	{
	case 0:
		// Use Player::canBuild to check for resources, coins, trading logic, and chains
		if (m_currentPlayer->canBuild(*m_selectedBuilding)) {
			// Player::addBuilding handles payment (including trading costs to opponent) and adding the building to vectors
			m_currentPlayer->addBuilding(*m_selectedBuilding);

			removeCardFromDeck(m_selectedBuilding->getId(), false);
			activateCardEffects(m_selectedBuilding);
			m_board.movePeon(m_selectedBuilding->getShields() * (m_currentPlayer->name() == "player1" ? -1 : 1));
			checkAndApplyZoneRewards();
			checkMilitaryVictory();
			if (m_gamestate == MILITARY)
			{

				PollEvents(window);
				break;
			}
			if (m_currentPlayer->hasScientificSupremacy())
			{
				m_gamestate = SCIENTIFIC;
				PollEvents(window);
			}
			turnCards();


			if (m_currentPlayer->hasTokenSelectionRight())
			{
				window.draw(m_backgroundSprite);
				drawTokenSelection(window);
				window.display();
				while (const std::optional event = window.waitEvent())
				{
					if (event->is<sf::Event::MouseButtonPressed>())
					{
						sf::Vector2i mousePos = sf::Mouse::getPosition(window);
						if (selectToken(window, mousePos))
							break;
					}
				}
				m_currentPlayer->consumeTokenSelectionRight();
			}
			std::swap(m_currentPlayer, m_otherPlayer);

		}
		else
		{
			std::cout << "You don't have enough resources/coins to build: " << m_selectedBuilding->getId() << ", retry\n";
		}
		break;
	case 1:
		m_currentPlayer->addCoin(sellProfit);
		removeCardFromDeck(m_selectedBuilding->getId(), true);
		turnCards();
		std::swap(m_currentPlayer, m_otherPlayer);
		break;
	case 2:
		// construct wonder stage
		if (Game::m_constructedWonders == 7)
		{
			std::cout << "Nu se mai pot construi minuni";
			break;
		}
		window.draw(m_backgroundSprite);
		drawWondersSelection(window);
		window.display();
		while (const std::optional event = window.waitEvent())
		{
			if (event->is<sf::Event::MouseButtonPressed>())
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				int index = wonderIndexAtPosition(mousePos, window);
				if (index >= 0 && index < static_cast<int>(m_wondersDisplay.size())
					&& m_wondersDisplay[index].has_value()) {
					auto selectedWonder = m_wondersDisplay[index].value();
					if (m_currentPlayer->canBuildWonder(*(selectedWonder))) {
						m_currentPlayer->buildWonder(selectedWonder->getId(), m_selectedBuilding);
						Game::m_constructedWonders++;
						removeCardFromDeck(m_selectedBuilding->getId(), false);
						activateWonderEffects(selectedWonder);
						m_board.movePeon(m_selectedBuilding->getShields() * (m_currentPlayer->name() == "player1" ? -1 : 1));
						checkAndApplyZoneRewards();
						checkMilitaryVictory();
						if (m_gamestate == MILITARY)
						{
							PollEvents(window);
						}
						if (m_currentPlayer->hasScientificSupremacy())
						{
							m_gamestate = SCIENTIFIC;
							PollEvents(window);
						}

						if (m_waitingForTokenSelection)
						{
							takeProgressToken(window);
							m_waitingForTokenSelection = false;
						}
						if (m_waitingToDiscardBrown && m_otherPlayer->getBrownBuildings().size() > 0) {
							discardOpponentCard(window, Building::Color::BROWN);
							m_waitingToDiscardGrey = false;
						}
						else {
							m_waitingToDiscardBrown = false;
						}

						if (m_waitingToDiscardGrey && m_otherPlayer->getGreyBuildings().size() > 0) {
							discardOpponentCard(window, Building::Color::GREY);
							m_waitingToDiscardGrey = false;
						}
						else {
							m_waitingToDiscardGrey = false;
						}

						if (m_waitingForDiscardedChoice && m_discardedCards->size() > 0) {
							constructDiscardedCard(window);
							m_waitingForDiscardedChoice = false;
						}
						else {
							m_waitingForDiscardedChoice = false;
						}


						if (m_currentPlayer->hasSecondTurn() || m_currentPlayer->hasTheologyProgressToken())
							m_currentPlayer->setSecondTurn(false);
						else
							std::swap(m_currentPlayer, m_otherPlayer);

						break;
					}
					else {
						std::cout << "You cannot build this wonder now. Retry\n";
						break;
					}
				}
				else
					break;
			}
			if (event->is<sf::Event::Closed>())
			{
				window.close();
				break;
			}
		}
		m_selectedBuilding = nullptr;
		if (m_gamestate == MILITARY)
			return option;
		window.draw(m_backgroundSprite);
		redrawCurrentAgeCards(window);
		drawPlayerCards(window);
		drawClickAreaForPlayerDetails(window);
		drawMilitaryBoard(window);
		drawSelectedCard(window);
		window.display();
		return option;

	}
}

void Game::activateCardEffects(std::shared_ptr<Building> building)
{
	for (auto& effect : building->getEffects())
	{
		m_cardEffects[effect](*this);
	}
}

void Game::activateWonderEffects(std::shared_ptr<Card> card)
{
	//auto originalSelected = m_selectedBuilding;

	// creez o cladire temporara pentru a activa efectele wonder-ului
	m_selectedBuilding = std::make_shared<Building>(
		Building::Age::AGEI,
		Building::Color::PURPLE,
		std::vector<ResourceType>{},
		std::nullopt,
		* card
	);
	for (auto& effect : card->getEffects())
	{
		m_cardEffects[effect](*this);
	}
}

bool Game::findSelectedCard(const sf::Vector2i& mousePos, sf::RenderWindow& window) {
	bool found = false;
	//int counter = 0;
	for (int i = 0; i < m_cardDisplay.size(); i++)
		for (int j = 0; j < m_cardDisplay[i].size(); j++) {
			if (m_cardDisplay[i][j].has_value()) {
				if (m_cardDisplay[i][j].value().isFaceUp() == true && m_cardDisplay[i][j].value().containsPoint(mousePos, window))
				{
					if (m_currentAge == Building::Age::AGEI)
					{
						if (i == m_cardDisplay.size() - 1 || (m_cardDisplay[i + 1][j].has_value() == false && m_cardDisplay[i + 1][j + 1].has_value() == false))
						{
							m_selectedBuilding = m_cardDisplay[i][j].value().getBuilding();
							m_cardDisplay[i][j].value().setSelected(true);
							m_guiCardDisplay[m_selectedBuilding->getId()].value().setHighlighted(true);
							//window.draw(m_guiCardDisplay[m_selectedBuilding->getId()].value());
							found = true;
						}
						else {
							m_cardDisplay[i][j].value().setSelected(false);
							m_guiCardDisplay[m_cardDisplay[i][j].value().getBuilding()->getId()].value().setHighlighted(false);
						}
					}
					if (m_currentAge == Building::Age::AGEII)
					{
						if (i == m_cardDisplay.size() - 1)
						{
							m_selectedBuilding = m_cardDisplay[i][j].value().getBuilding();
							m_cardDisplay[i][j].value().setSelected(true);
							m_guiCardDisplay[m_selectedBuilding->getId()].value().setHighlighted(true);
							//window.draw(m_guiCardDisplay[m_selectedBuilding->getId()].value());
							found = true;
						}
						else {
							if ((j == 0 && m_cardDisplay[i + 1][j].has_value() == false) || (j == m_cardDisplay[i].size() - 1 && m_cardDisplay[i + 1][j - 1].has_value() == false) || (j > 0 && j < m_cardDisplay[i].size() && m_cardDisplay[i + 1][j].has_value() == false && m_cardDisplay[i + 1][j - 1].has_value() == false))
							{
								m_selectedBuilding = m_cardDisplay[i][j].value().getBuilding();
								m_cardDisplay[i][j].value().setSelected(true);
								m_guiCardDisplay[m_selectedBuilding->getId()].value().setHighlighted(true);
								//window.draw(m_guiCardDisplay[m_selectedBuilding->getId()].value());
								found = true;
							}
							else
							{
								m_cardDisplay[i][j].value().setSelected(false);
								m_guiCardDisplay[m_cardDisplay[i][j].value().getBuilding()->getId()].value().setHighlighted(false);
							}

						}
					}
					if (m_currentAge == Building::Age::AGEIII)
					{
						if (i == m_cardDisplay.size() - 1 ||
							(i < 2 && m_cardDisplay[i + 1][j].has_value() == false && m_cardDisplay[i + 1][j + 1].has_value() == false) ||
							(i == 2 && m_cardDisplay[i + 1][j / 2].has_value() == false) ||
							(i == 3 && m_cardDisplay[i + 1][j * 2].has_value() == false && m_cardDisplay[i + 1][j * 2 + 1].has_value() == false) ||
							(i > 3 && ((j == 0 && m_cardDisplay[i + 1][j].has_value() == false) || (j == m_cardDisplay[i].size() - 1 && m_cardDisplay[i + 1][j - 1].has_value() == false) || (j > 0 && j < m_cardDisplay[i].size() && m_cardDisplay[i + 1][j].has_value() == false && m_cardDisplay[i + 1][j - 1].has_value() == false)
								)))
						{
							m_selectedBuilding = m_cardDisplay[i][j].value().getBuilding();
							m_cardDisplay[i][j].value().setSelected(true);
							m_guiCardDisplay[m_selectedBuilding->getId()].value().setHighlighted(true);
							//window.draw(m_guiCardDisplay[m_selectedBuilding->getId()].value());
							found = true;
						}
						else {
							m_cardDisplay[i][j].value().setSelected(false);
							m_guiCardDisplay[m_cardDisplay[i][j].value().getBuilding()->getId()].value().setHighlighted(false);
						}
					}
				}
				else {
					m_cardDisplay[i][j].value().setSelected(false);
					m_guiCardDisplay[m_cardDisplay[i][j].value().getBuilding()->getId()].value().setHighlighted(false);
				}
			}
			//counter++;
		}
	if (found)
		return true;
	m_selectedBuilding = nullptr;
	return false;
}

std::uint8_t wasPlayerDetailBoxClicked(const sf::RenderWindow& window, const sf::Vector2i& mousePos)
{
	constexpr float boxWidth = 170.f;
	constexpr float boxHeight = 50.f;
	const float leftX = 175.f;
	const float rightX = static_cast<float>(window.getSize().x) - boxWidth - leftX;
	const float yPos = static_cast<float>(window.getSize().y) - boxHeight - 10.f;
	sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
	sf::FloatRect leftBoxRect(sf::Vector2f(leftX, yPos), sf::Vector2f(boxWidth, boxHeight));
	sf::FloatRect rightBoxRect(sf::Vector2f(rightX, yPos), sf::Vector2f(boxWidth, boxHeight));
	if (leftBoxRect.contains(worldPos))
		return 1; // Left player box clicked
	else if (rightBoxRect.contains(worldPos))
		return 2; // Right player box clicked
	else
		return 0; // No box clicked
}

bool wasExitPlayerBoxClicked(const sf::RenderWindow& window, const sf::Vector2i& mousePos)
{
	const float boxX = 840.f;
	const float boxY = 35.f;
	const float boxWidth = 100.f;
	const float boxHeight = 40.f;
	sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
	sf::FloatRect exitBoxRect(sf::Vector2f(boxX, boxY), sf::Vector2f(boxWidth, boxHeight));
	return exitBoxRect.contains(worldPos);
}

void Game::handleClick(sf::RenderWindow& window, sf::Vector2i&& mousePos)
{
	static bool alreadyDrawn = false;
	static bool constructionOptionDrawn = false;
	int option = -1;
	if (m_gamestate == GAMESTART)
		wondersSetup(window, mousePos);

	if (m_gamestate == ONGOING)
	{
		if (!m_isInPlayerBox)
		{
			if (wasPlayerDetailBoxClicked(window, mousePos))
			{
				window.draw(m_backgroundSprite);
				std::uint8_t boxClicked = wasPlayerDetailBoxClicked(window, mousePos);
				if (boxClicked == 1)
				{
					if (m_currentPlayer->name().compare("player1") == 0)
						drawPlayerBox(window, m_currentPlayer);
					else
						drawPlayerBox(window, m_otherPlayer);
				}
				else if (boxClicked == 2)
				{
					if (m_currentPlayer->name().compare("player2") == 0)
						drawPlayerBox(window, m_currentPlayer);
					else
						drawPlayerBox(window, m_otherPlayer);
				}
				window.display();
				m_isInPlayerBox = true;
				return;
			}
			if (constructionOptionDrawn)
			{
				option = chooseConstructionOption(window, sf::Mouse::getPosition(window));
				constructionOptionDrawn = false;
				//alreadyDrawn = false;
			}
			if (alreadyDrawn) {
				bool selected = selectCardEffect(window, sf::Mouse::getPosition(window));
				if (selected && !constructionOptionDrawn)
				{
					drawConstructionChoices(window);
					constructionOptionDrawn = true;
					//chooseConstructionOption(window, sf::Mouse::getPosition(window));
				}
				drawClickAreaForPlayerDetails(window);
			}

			if (!alreadyDrawn && m_gamestate == ONGOING) {
				window.draw(m_backgroundSprite);
				drawCurrentAgeCards(window);
				drawPlayerCards(window);
				drawClickAreaForPlayerDetails(window);
				alreadyDrawn = true;
			}
			drawPlayerTurn(window);
			drawMilitaryBoard(window);
			drawSelectedCard(window);
			window.display();
		}
		else
		{
			if (wasExitPlayerBoxClicked(window, mousePos))
			{
				m_isInPlayerBox = false;
				window.draw(m_backgroundSprite);
				redrawCurrentAgeCards(window);
				drawPlayerCards(window);
				drawClickAreaForPlayerDetails(window);
				drawMilitaryBoard(window);
				drawPlayerTurn(window);
				drawSelectedCard(window);
				window.display();
			}
		}
	}
}

void Game::drawPlayerBox(sf::RenderWindow& window, const std::shared_ptr<Player>& selectedPlayer)
{
	const sf::Font font = []() {
		sf::Font font("C:\\Windows\\Fonts\\cour.ttf");
		return font;
		}();
	sf::RectangleShape backgroundBox;
	backgroundBox.setSize({ 400.f, 850.f });
	backgroundBox.setFillColor(sf::Color::White);
	backgroundBox.setOutlineColor(sf::Color::Black);
	backgroundBox.setOutlineThickness(3.f);
	backgroundBox.setPosition({ static_cast<float>(window.getSize().x) / 2 - 200.f, static_cast<float>(window.getSize().y) / 2 - 425.f });

	sf::Texture coinTexture;
	coinTexture.loadFromFile("..\\..\\Images\\Miscellaneous\\coins.png");
	sf::Sprite coinSprite(coinTexture);
	coinSprite.setScale({ 0.1f, 0.1f });
	coinSprite.setPosition({ backgroundBox.getPosition().x + 20.f, backgroundBox.getPosition().y + 20.f });

	sf::Text coinsLabel(font, ": " + std::to_string(selectedPlayer->getCoins()), 20);
	coinsLabel.setPosition({ backgroundBox.getPosition().x + 75.f, backgroundBox.getPosition().y + 30.f });
	coinsLabel.setFillColor(sf::Color::Black);

	sf::Texture victoryPointTexture;
	victoryPointTexture.loadFromFile("..\\..\\Images\\Miscellaneous\\victory points.png");
	sf::Sprite victoryPointSprite(victoryPointTexture);
	victoryPointSprite.setScale({ 0.3f, 0.3f });
	victoryPointSprite.setPosition({ backgroundBox.getPosition().x + 20.f, backgroundBox.getPosition().y + 80.f });

	sf::Text victoryPointsLabel(font, ": " + std::to_string(selectedPlayer->getVictoryPoints()), 20);
	victoryPointsLabel.setPosition({ backgroundBox.getPosition().x + 75.f, backgroundBox.getPosition().y + 90.f });
	victoryPointsLabel.setFillColor(sf::Color::Black);

	sf::Texture woodTexture;
	woodTexture.loadFromFile("..\\..\\Images\\Miscellaneous\\wood.jpg");
	sf::Sprite woodSprite(woodTexture);
	woodSprite.setScale({ 0.3f, 0.3f });
	woodSprite.setPosition({ backgroundBox.getPosition().x + 20.f, backgroundBox.getPosition().y + 130.f });

	sf::Text woodLabel(font, ": " + std::to_string(selectedPlayer->getWood()), 20);
	woodLabel.setPosition({ backgroundBox.getPosition().x + 75.f, backgroundBox.getPosition().y + 135.f });
	woodLabel.setFillColor(sf::Color::Black);

	sf::Texture stoneTexture;
	stoneTexture.loadFromFile("..\\..\\Images\\Miscellaneous\\stone.jpg");
	sf::Sprite stoneSprite(stoneTexture);
	stoneSprite.setScale({ 0.3f, 0.3f });
	stoneSprite.setPosition({ backgroundBox.getPosition().x + 20.f, backgroundBox.getPosition().y + 180.f });

	sf::Text stoneLabel(font, ": " + std::to_string(selectedPlayer->getStone()), 20);
	stoneLabel.setPosition({ backgroundBox.getPosition().x + 75.f, backgroundBox.getPosition().y + 185.f });
	stoneLabel.setFillColor(sf::Color::Black);

	sf::Texture clayTexture;
	clayTexture.loadFromFile("..\\..\\Images\\Miscellaneous\\brick.jpg");
	sf::Sprite claySprite(clayTexture);
	claySprite.setScale({ 0.3f, 0.3f });
	claySprite.setPosition({ backgroundBox.getPosition().x + 20.f, backgroundBox.getPosition().y + 230.f });

	sf::Text clayLabel(font, ": " + std::to_string(selectedPlayer->getClay()), 20);
	clayLabel.setPosition({ backgroundBox.getPosition().x + 75.f, backgroundBox.getPosition().y + 235.f });
	clayLabel.setFillColor(sf::Color::Black);

	sf::Texture glassTexture;
	glassTexture.loadFromFile("..\\..\\Images\\Miscellaneous\\glass.jpg");
	sf::Sprite glassSprite(glassTexture);
	glassSprite.setScale({ 0.3f, 0.3f });
	glassSprite.setPosition({ backgroundBox.getPosition().x + 20.f, backgroundBox.getPosition().y + 280.f });

	sf::Text glassLabel(font, ": " + std::to_string(selectedPlayer->getGlass()), 20);
	glassLabel.setPosition({ backgroundBox.getPosition().x + 75.f, backgroundBox.getPosition().y + 285.f });
	glassLabel.setFillColor(sf::Color::Black);

	sf::Texture papyrusTexture;
	papyrusTexture.loadFromFile("..\\..\\Images\\Miscellaneous\\paper.jpg");
	sf::Sprite papyrusSprite(papyrusTexture);
	papyrusSprite.setScale({ 0.3f, 0.3f });
	papyrusSprite.setPosition({ backgroundBox.getPosition().x + 20.f, backgroundBox.getPosition().y + 330.f });

	sf::Text papyrusLabel(font, ": " + std::to_string(selectedPlayer->getPapyrus()), 20);
	papyrusLabel.setPosition({ backgroundBox.getPosition().x + 75.f, backgroundBox.getPosition().y + 335.f });
	papyrusLabel.setFillColor(sf::Color::Black);

	sf::Texture shieldTexture;
	shieldTexture.loadFromFile("..\\..\\Images\\Miscellaneous\\shield.jpg");
	sf::Sprite shieldSprite(shieldTexture);
	shieldSprite.setScale({ 0.3f, 0.3f });
	shieldSprite.setPosition({ backgroundBox.getPosition().x + 23.f, backgroundBox.getPosition().y + 380.f });

	sf::Text shieldLabel(font, ": " + std::to_string(selectedPlayer->getShields()), 20);
	shieldLabel.setPosition({ backgroundBox.getPosition().x + 75.f, backgroundBox.getPosition().y + 385.f });
	shieldLabel.setFillColor(sf::Color::Black);

	sf::Texture globeTexture;
	globeTexture.loadFromFile("..\\..\\Images\\Scientific Symbols\\ball.png");
	sf::Sprite globeSprite(globeTexture);
	globeSprite.setScale({ 0.3f, 0.3f });
	globeSprite.setPosition({ backgroundBox.getPosition().x + 23.f, backgroundBox.getPosition().y + 430.f });

	sf::Texture featherTexture;
	featherTexture.loadFromFile("..\\..\\Images\\Scientific Symbols\\feather.png");
	sf::Sprite featherSprite(featherTexture);
	featherSprite.setScale({ 0.3f, 0.3f });
	featherSprite.setPosition({ backgroundBox.getPosition().x + 20.f, backgroundBox.getPosition().y + 480.f });

	sf::Texture mortarTexture;
	mortarTexture.loadFromFile("..\\..\\Images\\Scientific Symbols\\pestil.png");
	sf::Sprite mortarSprite(mortarTexture);
	mortarSprite.setScale({ 0.3f, 0.3f });
	mortarSprite.setPosition({ backgroundBox.getPosition().x + 20.f, backgroundBox.getPosition().y + 530.f });

	sf::Texture sundialTexture;
	sundialTexture.loadFromFile("..\\..\\Images\\Scientific Symbols\\sundial.png");
	sf::Sprite sundialSprite(sundialTexture);
	sundialSprite.setScale({ 0.3f, 0.3f });
	sundialSprite.setPosition({ backgroundBox.getPosition().x + 20.f, backgroundBox.getPosition().y + 580.f });

	sf::Texture triangleTexture;
	triangleTexture.loadFromFile("..\\..\\Images\\Scientific Symbols\\triangle.png");
	sf::Sprite triangleSprite(triangleTexture);
	triangleSprite.setScale({ 0.3f, 0.3f });
	triangleSprite.setPosition({ backgroundBox.getPosition().x + 20.f, backgroundBox.getPosition().y + 630.f });

	sf::Texture scaleTexture;
	scaleTexture.loadFromFile("..\\..\\Images\\Scientific Symbols\\scale.png");
	sf::Sprite scaleSprite(scaleTexture);
	scaleSprite.setScale({ 0.3f, 0.3f });
	scaleSprite.setPosition({ backgroundBox.getPosition().x + 17.f, backgroundBox.getPosition().y + 680.f });

	sf::Texture wheelTexture;
	wheelTexture.loadFromFile("..\\..\\Images\\Scientific Symbols\\wheel.png");
	sf::Sprite wheelSprite(wheelTexture);
	wheelSprite.setScale({ 0.3f, 0.3f });
	wheelSprite.setPosition({ backgroundBox.getPosition().x + 20.f, backgroundBox.getPosition().y + 735.f });

	sf::Text globeLabel(font, ": " + std::to_string(selectedPlayer->getScientificPoints()[0]), 20);
	globeLabel.setPosition({ backgroundBox.getPosition().x + 75.f, backgroundBox.getPosition().y + 435.f });
	globeLabel.setFillColor(sf::Color::Black);

	sf::Text featherLabel(font, ": " + std::to_string(selectedPlayer->getScientificPoints()[5]), 20);
	featherLabel.setPosition({ backgroundBox.getPosition().x + 75.f, backgroundBox.getPosition().y + 485.f });
	featherLabel.setFillColor(sf::Color::Black);

	sf::Text mortarLabel(font, ": " + std::to_string(selectedPlayer->getScientificPoints()[3]), 20);
	mortarLabel.setPosition({ backgroundBox.getPosition().x + 75.f, backgroundBox.getPosition().y + 535.f });
	mortarLabel.setFillColor(sf::Color::Black);

	sf::Text sundialLabel(font, ": " + std::to_string(selectedPlayer->getScientificPoints()[2]), 20);
	sundialLabel.setPosition({ backgroundBox.getPosition().x + 75.f, backgroundBox.getPosition().y + 585.f });
	sundialLabel.setFillColor(sf::Color::Black);

	sf::Text triangleLabel(font, ": " + std::to_string(selectedPlayer->getScientificPoints()[4]), 20);
	triangleLabel.setPosition({ backgroundBox.getPosition().x + 75.f, backgroundBox.getPosition().y + 635.f });
	triangleLabel.setFillColor(sf::Color::Black);

	sf::Text scaleLabel(font, ": " + std::to_string(selectedPlayer->hasLawProgressToken()), 20);
	scaleLabel.setPosition({ backgroundBox.getPosition().x + 75.f, backgroundBox.getPosition().y + 690.f });
	scaleLabel.setFillColor(sf::Color::Black);

	sf::Text wheelLabel(font, ": " + std::to_string(selectedPlayer->getScientificPoints()[6]), 20);
	wheelLabel.setPosition({ backgroundBox.getPosition().x + 75.f, backgroundBox.getPosition().y + 740.f });
	wheelLabel.setFillColor(sf::Color::Black);

	sf::RectangleShape exitBox;
	exitBox.setSize({ 100.f, 40.f });
	exitBox.setFillColor(sf::Color(200, 0, 0));
	exitBox.setPosition({ backgroundBox.getPosition().x + backgroundBox.getSize().x - exitBox.getSize().x - 10.f,
		backgroundBox.getPosition().y + 10.f });

	sf::Text exitLabel(font, "X", 30);
	exitLabel.setPosition({ exitBox.getPosition().x + 30.f, exitBox.getPosition().y + 5.f });
	exitLabel.setFillColor(sf::Color::White);


	window.draw(backgroundBox);

	window.draw(coinSprite);
	window.draw(coinsLabel);

	window.draw(victoryPointSprite);
	window.draw(victoryPointsLabel);

	window.draw(woodSprite);
	window.draw(woodLabel);

	window.draw(stoneSprite);
	window.draw(stoneLabel);

	window.draw(claySprite);
	window.draw(clayLabel);

	window.draw(glassSprite);
	window.draw(glassLabel);

	window.draw(papyrusSprite);
	window.draw(papyrusLabel);

	window.draw(shieldSprite);
	window.draw(shieldLabel);

	window.draw(globeSprite);
	window.draw(globeLabel);

	window.draw(featherSprite);
	window.draw(featherLabel);

	window.draw(mortarSprite);
	window.draw(mortarLabel);

	window.draw(sundialSprite);
	window.draw(sundialLabel);

	window.draw(triangleSprite);
	window.draw(triangleLabel);

	window.draw(wheelSprite);
	window.draw(wheelLabel);

	window.draw(scaleSprite);
	window.draw(scaleLabel);

	window.draw(exitBox);
	window.draw(exitLabel);
}

void Game::drawMilitaryBoard(sf::RenderWindow& window)
{
	sf::Texture militaryTexture;
	militaryTexture.loadFromFile("..\\..\\Images\\Board\\board.png");
	sf::Sprite militarySprite(militaryTexture);
	militarySprite.setScale({ 0.15f, 0.15f });
	militarySprite.setPosition({ static_cast<float>(window.getSize().x) / 2.f - 225, 720.f });
	window.draw(militarySprite);


	sf::Texture tokenTexture;
	int i = 0;
	for (float x = static_cast<float>(window.getSize().x) / 2.f - 115; i < m_progressTokensDeck.size(); x = x + 45, i++)
	{
		tokenTexture.loadFromFile("..\\..\\Images\\Progress tokens\\" + std::to_string(m_progressTokensDeck[i]->getId()) + ".png");
		sf::Sprite tokenSprite(tokenTexture);
		tokenSprite.setScale({ 0.15f, 0.15f });
		tokenSprite.setPosition({ x, 730.f });
		window.draw(tokenSprite);
	}

	sf::Texture peonTexture;
	peonTexture.loadFromFile("..\\..\\Images\\Board\\peon.png");
	sf::Sprite peonSprite(peonTexture);
	peonSprite.setScale({ 0.6f, 0.6f });
	float pos = (m_board.getPos()) * (21) + 8;
	peonSprite.setPosition({ static_cast<float>(window.getSize().x) / 2.f - pos, 770.f });
	window.draw(peonSprite);

	if (!m_board.getZoneTriggers()[1])
	{
		sf::Texture war1Texture;
		war1Texture.loadFromFile("..\\..\\Images\\Board\\military token 2.png");
		sf::Sprite warSprite(war1Texture);
		warSprite.setScale({ 0.05f, 0.05f });
		warSprite.rotate(sf::degrees(270.f));
		warSprite.setPosition({ static_cast<float>(window.getSize().x) / 2.f + 61.f, 840.f });
		window.draw(warSprite);
	}
	if (!m_board.getZoneTriggers()[4])
	{
		sf::Texture war1Texture;
		war1Texture.loadFromFile("..\\..\\Images\\Board\\military token 2.png");
		sf::Sprite warSprite(war1Texture);
		warSprite.setScale({ 0.05f, 0.05f });
		warSprite.rotate(sf::degrees(270.f));
		warSprite.setPosition({ static_cast<float>(window.getSize().x) / 2.f - 112.f, 840.f });
		window.draw(warSprite);
	}
	if (!m_board.getZoneTriggers()[0])
	{
		sf::Texture war1Texture;
		war1Texture.loadFromFile("..\\..\\Images\\Board\\military token 5.png");
		sf::Sprite warSprite(war1Texture);
		warSprite.setScale({ 0.05f, 0.05f });
		warSprite.rotate(sf::degrees(270.f));
		warSprite.setPosition({ static_cast<float>(window.getSize().x) / 2.f + 121.f, 840.f });
		window.draw(warSprite);
	}
	if (!m_board.getZoneTriggers()[5])
	{
		sf::Texture war1Texture;
		war1Texture.loadFromFile("..\\..\\Images\\Board\\military token 5.png");
		sf::Sprite warSprite(war1Texture);
		warSprite.setScale({ 0.05f, 0.05f });
		warSprite.rotate(sf::degrees(270.f));
		warSprite.setPosition({ static_cast<float>(window.getSize().x) / 2.f - 172.f, 840.f });
		window.draw(warSprite);
	}

}

void Game::drawPlayerTurn(sf::RenderWindow& window)
{
	const sf::Font font = []() {
		sf::Font font("C:\\Windows\\Fonts\\cour.ttf");
		return font;
		}();
	sf::Text turnText(font, "", 24);
	turnText.setFillColor(m_currentPlayer->name() == "player1" ? sf::Color::Blue : sf::Color::Red);
	turnText.setPosition({ static_cast<float>(window.getSize().x) - 325.f, 200.f });
	turnText.setString("Current turn: " + m_currentPlayer->name());
	window.draw(turnText);
}

void Game::drawDiscardedCards(sf::RenderWindow& window)
{
	const float cardWidth = static_cast<float>(BoxSizes::boxWidth);
	const float cardHeight = static_cast<float>(BoxSizes::boxHeight);
	const float spacing = 10.f;
	const float totalWidth = m_discardedCards->size() * cardWidth + (m_discardedCards->size() - 1) * spacing;
	float x = static_cast<float>(window.getSize().x) / 2.f - totalWidth / 2.f;
	float y = static_cast<float>(window.getSize().y) / 2.f - cardHeight / 2.f;

	float currentX = x;
	for (const auto& card : *m_discardedCards)
	{
		sf::Texture cardTexture;
		cardTexture.loadFromFile("..\\..\\Images\\" + std::to_string(card->getId()) + ".jpg");
		sf::Sprite cardSprite(cardTexture);
		cardSprite.setScale(sf::Vector2f{ cardWidth / cardTexture.getSize().x, cardHeight / cardTexture.getSize().y });
		cardSprite.setPosition({ currentX, y });
		window.draw(cardSprite);

		currentX += cardWidth + spacing;

	}
}

bool Game::selectDiscardedCard(sf::RenderWindow& window, const sf::Vector2i& mousePos)
{
	sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

	const float cardWidth = static_cast<float>(BoxSizes::boxWidth);
	const float cardHeight = static_cast<float>(BoxSizes::boxHeight);
	const float spacing = 10.f;
	const float totalWidth = m_discardedCards->size() * cardWidth + (m_discardedCards->size() - 1) * spacing;

	const float startX = static_cast<float>(window.getSize().x) / 2.f - totalWidth / 2.f;
	const float startY = static_cast<float>(window.getSize().y) / 2.f - cardHeight / 2.f;

	for (int i = 0; i < m_discardedCards->size(); ++i)
	{
		sf::FloatRect cardRect(
			sf::Vector2f(startX + i * (cardWidth + spacing), startY),
			sf::Vector2f(cardWidth, cardHeight)
		);

		if (cardRect.contains(worldPos))
		{
			m_selectedBuilding = m_discardedCards->at(i);

			m_currentPlayer->addBuildingDirectly(*(m_discardedCards->at(i)));
			activateCardEffects(m_discardedCards->at(i));
			m_board.movePeon(m_discardedCards->at(i)->getShields() * (m_currentPlayer->name() == "player1" ? -1 : 1));
			m_discardedCards->erase(m_discardedCards->begin() + i);
			return true;
		}
	}
	return false;
}

void Game::constructDiscardedCard(sf::RenderWindow& window)
{
	window.draw(m_backgroundSprite);
	drawDiscardedCards(window);
	window.display();
	while (const std::optional event = window.waitEvent())
	{
		if (event->is<sf::Event::MouseButtonPressed>())
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			if (selectDiscardedCard(window, mousePos))
				break;
		}
	}

}

void Game::checkAndApplyZoneRewards()
{
	std::vector<bool> zoneTriggers = m_board.getZoneTriggers();
	int currentPos = m_board.getPos();

	struct ZoneReward {
		int vpGain;
		int opponentCoinLoss;
		int minPos;
		int maxPos;
	};

	std::array<ZoneReward, 6> rewards = { {
		{10, 5, -9, -6},
		{5, 2, -6, -3},
		{2, 0, -3, -1},
		{2, 0, 1, 3},
		{5, 2, 3, 6},
		{10, 5, 6, 9}
	} };

	for (int i = 0; i < 6; i++) {
		bool isInZone = (currentPos >= rewards[i].minPos && currentPos <= rewards[i].maxPos);

		if (zoneTriggers[i] && isInZone && !m_zoneRewardsGiven[i]) {
			std::shared_ptr<Player> rewardPlayer;
			std::shared_ptr<Player> penaltyPlayer;

			if (i < 3) {
				if (m_currentPlayer->name() == "player1") {
					rewardPlayer = m_currentPlayer;
					penaltyPlayer = m_otherPlayer;
				}
				else {
					rewardPlayer = m_otherPlayer;
					penaltyPlayer = m_currentPlayer;
				}
			}
			else {
				if (m_currentPlayer->name() == "player2") {
					rewardPlayer = m_currentPlayer;
					penaltyPlayer = m_otherPlayer;
				}
				else {
					rewardPlayer = m_otherPlayer;
					penaltyPlayer = m_currentPlayer;
				}
			}

			if (rewards[i].opponentCoinLoss > 0) {
				int currentCoins = penaltyPlayer->getCoins();
				int coinsToLose = std::min(currentCoins, rewards[i].opponentCoinLoss);
				penaltyPlayer->payCoin(coinsToLose);
			}

			m_pendingZoneVictoryPoints[i] = rewards[i].vpGain;

			std::cout << rewardPlayer->name() << " entered zone ";

			int visualZoneNumber = 6 - i;

			std::cout << visualZoneNumber << " (will gain " << rewards[i].vpGain << " VP at game end)";
			if (rewards[i].opponentCoinLoss > 0) {
				std::cout << ". " << penaltyPlayer->name()
					<< " lost " << rewards[i].opponentCoinLoss << " coins now";
			}
			std::cout << "!\n";

			m_zoneRewardsGiven[i] = true;
		}
	}
}

void Game::awardPendingZoneVictoryPoints()
{
	std::vector<bool> zoneTriggers = m_board.getZoneTriggers();
	int currentPos = m_board.getPos();

	struct ZoneReward {
		int vpGain;
		int opponentCoinLoss;
		int minPos;
		int maxPos;
	};

	std::array<ZoneReward, 6> rewards = { {
		{10, 5, -9, -6},
		{5, 2, -6, -3},
		{2, 0, -3, -1},
		{2, 0, 1, 3},
		{5, 2, 3, 6},
		{10, 5, 6, 9}
	} };

	std::cout << "\n=== Awarding Military Zone Victory Points ===\n";

	for (int i = 0; i < 6; i++) {
		if (m_pendingZoneVictoryPoints[i] > 0) {
			std::shared_ptr<Player> rewardPlayer;

			if (i < 3) {
				if (m_currentPlayer->name() == "player1") {
					rewardPlayer = m_currentPlayer;
				}
				else {
					rewardPlayer = m_otherPlayer;
				}
			}
			else {
				if (m_currentPlayer->name() == "player2") {
					rewardPlayer = m_currentPlayer;
				}
				else {
					rewardPlayer = m_otherPlayer;
				}
			}

			rewardPlayer->addVictoryPoints(m_pendingZoneVictoryPoints[i]);

			int visualZoneNumber = 6 - i;
			std::cout << rewardPlayer->name() << " gains "
				<< m_pendingZoneVictoryPoints[i]
				<< " VP from zone " << visualZoneNumber << "\n";
		}
	}

	std::cout << "==========================================\n\n";
}

void Game::draw3ProgressTokens(sf::RenderWindow& window)
{
	

	std::random_device rd;
	std::mt19937 gen(rd());
	for (int i = 0; i < 3; ++i)
	{
		std::uniform_int_distribution<> dist(0, m_remainingProgressTokens.size() - 1);
		int randomIndex = dist(gen);
		m_current3TokenChoices.emplace_back(std::move(m_remainingProgressTokens[randomIndex]));
		m_remainingProgressTokens.erase(m_remainingProgressTokens.begin() + randomIndex);
	}
	float x = static_cast<float>(window.getSize().x) / 2.f - (m_current3TokenChoices.size() * 148.f) / 2.f;
	float y = static_cast<float>(window.getSize().y) / 2.f - 75.f;
	for (int i = 0; i < m_current3TokenChoices.size(); ++i)
	{
		sf::Texture tokenTexture;
		tokenTexture.loadFromFile("..\\..\\Images\\Progress tokens\\" + std::to_string(m_current3TokenChoices[i]->getId()) + ".png");
		sf::Sprite tokenSprite(tokenTexture);
		tokenSprite.setScale({ 0.4f, 0.4f });
		tokenSprite.setPosition({ x, y });
		x += 154;
		window.draw(tokenSprite);
	}
}

bool Game::selectFrom3ProgressTokens(sf::RenderWindow& window, const sf::Vector2i& mousePos)
{
	sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
	const float xPosStart = static_cast<float>(window.getSize().x) / 2.f - (m_current3TokenChoices.size() * 148.f) / 2.f;
	const float yPos = static_cast<float>(window.getSize().y) / 2.f - 75.f;
	const float tokenBoxWidth = 100.f;
	const float tokenBoxHeight = 80.f;
	for (int i = 0; i < m_current3TokenChoices.size(); ++i) {
		sf::FloatRect tokenRect(
			sf::Vector2f(xPosStart + i * 154, yPos),
			sf::Vector2f(tokenBoxWidth, tokenBoxHeight)
		);
		if (tokenRect.contains(worldPos)) {
			m_currentPlayer->addProgressToken(*(m_current3TokenChoices[i]));
			m_current3TokenChoices[i]->applyEffect(m_currentPlayer);
			m_current3TokenChoices.erase(m_current3TokenChoices.begin() + i);
			return true;
		}
	}
	return false;
}

void Game::takeProgressToken(sf::RenderWindow& window)
{
	window.draw(m_backgroundSprite);
	draw3ProgressTokens(window);
	window.display();
	while (const std::optional event = window.waitEvent())
	{
		if (event->is<sf::Event::MouseButtonPressed>())
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			if (selectFrom3ProgressTokens(window, mousePos))
				break;
		}
	}
}

void Game::drawOpponentGreyOrBrownBuildings(sf::RenderWindow& window, Building::Color color)
{
	const float cardWidth = static_cast<float>(BoxSizes::boxWidth);
	const float cardHeight = static_cast<float>(BoxSizes::boxHeight);
	const float spacing = 10.f;
	float totalWidth;
	if (color == Building::Color::BROWN) {
		totalWidth = m_otherPlayer->getBrownBuildings().size() * cardWidth + (m_otherPlayer->getBrownBuildings().size() - 1) * spacing;
	}
	else {
		totalWidth = m_otherPlayer->getGreyBuildings().size() * cardWidth + (m_otherPlayer->getGreyBuildings().size() - 1) * spacing;
	}
	float x = static_cast<float>(window.getSize().x) / 2.f - totalWidth / 2.f;
	float y = static_cast<float>(window.getSize().y) / 2.f - cardHeight / 2.f;

	float currentX = x;
	if (color == Building::Color::BROWN)
		for (const auto& card : m_otherPlayer->getBrownBuildings())
		{
			sf::Texture cardTexture;
			cardTexture.loadFromFile("..\\..\\Images\\" + std::to_string(card.getId()) + ".jpg");
			sf::Sprite cardSprite(cardTexture);
			cardSprite.setScale(sf::Vector2f{ cardWidth / cardTexture.getSize().x, cardHeight / cardTexture.getSize().y });
			cardSprite.setPosition({ currentX, y });
			window.draw(cardSprite);
			currentX += cardWidth + spacing;
		}
	else
		for (const auto& card : m_otherPlayer->getGreyBuildings())
		{
			sf::Texture cardTexture;
			cardTexture.loadFromFile("..\\..\\Images\\" + std::to_string(card.getId()) + ".jpg");
			sf::Sprite cardSprite(cardTexture);
			cardSprite.setScale(sf::Vector2f{ cardWidth / cardTexture.getSize().x, cardHeight / cardTexture.getSize().y });
			cardSprite.setPosition({ currentX, y });
			window.draw(cardSprite);

			currentX += cardWidth + spacing;
		}
}

bool Game::selectGreyOrBrownCard(sf::RenderWindow& window, const sf::Vector2i& mousePos, Building::Color color)
{
	sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

	const float cardWidth = static_cast<float>(BoxSizes::boxWidth);
	const float cardHeight = static_cast<float>(BoxSizes::boxHeight);
	const float spacing = 10.f;
	float totalWidth;
	if (color == Building::Color::BROWN) {
		totalWidth = m_otherPlayer->getBrownBuildings().size() * cardWidth + (m_otherPlayer->getBrownBuildings().size() - 1) * spacing;
	}
	else {
		totalWidth = m_otherPlayer->getGreyBuildings().size() * cardWidth + (m_otherPlayer->getGreyBuildings().size() - 1) * spacing;
	}

	const float startX = static_cast<float>(window.getSize().x) / 2.f - totalWidth / 2.f;
	const float startY = static_cast<float>(window.getSize().y) / 2.f - cardHeight / 2.f;
	if (color == Building::Color::BROWN)
		for (int i = 0; i < m_otherPlayer->getBrownBuildings().size(); ++i)
		{
			sf::FloatRect cardRect(
				sf::Vector2f(startX + i * (cardWidth + spacing), startY),
				sf::Vector2f(cardWidth, cardHeight)
			);

			if (cardRect.contains(worldPos))
			{
				m_otherPlayer->discardBuilding(Building::Color::BROWN, i);
				return true;
			}
		}
	else
		for (int i = 0; i < m_otherPlayer->getGreyBuildings().size(); ++i)
		{
			sf::FloatRect cardRect(
				sf::Vector2f(startX + i * (cardWidth + spacing), startY),
				sf::Vector2f(cardWidth, cardHeight)
			);
			if (cardRect.contains(worldPos))
			{
				m_otherPlayer->discardBuilding(Building::Color::GREY, i);
				return true;
			}
		}
	return false;
}

void Game::discardOpponentCard(sf::RenderWindow& window, Building::Color color)
{
	window.draw(m_backgroundSprite);
	if (color == Building::Color::BROWN)
		drawOpponentGreyOrBrownBuildings(window, Building::Color::BROWN);
	else
		drawOpponentGreyOrBrownBuildings(window, Building::Color::GREY);
	window.display();
	while (const std::optional event = window.waitEvent())
	{
		if (event->is<sf::Event::MouseButtonPressed>())
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			if (color == Building::Color::BROWN) {
				if (selectGreyOrBrownCard(window, mousePos, Building::Color::BROWN))
					break;
			}
			else {
				if (selectGreyOrBrownCard(window, mousePos, Building::Color::GREY))
					break;
			}
		}
	}
}

void Game::drawTokenSelection(sf::RenderWindow& window)
{
	float x = static_cast<float>(window.getSize().x) / 2.f - (m_progressTokensDeck.size() * 148.f) / 2.f;
	float y = static_cast<float>(window.getSize().y) / 2.f - 75.f;
	for (auto& token : m_progressTokensDeck)
	{
		sf::Texture tokenTexture;
		tokenTexture.loadFromFile("..\\..\\Images\\Progress tokens\\" + std::to_string(token->getId()) + ".png");
		sf::Sprite tokenSprite(tokenTexture);
		tokenSprite.setScale({ 0.4f, 0.4f });
		tokenSprite.setPosition({ x, y });
		x += 154;
		window.draw(tokenSprite);
	}
}

void Game::PollEvents(sf::RenderWindow& window)
{
	while (const std::optional event = window.waitEvent())
	{

		if (event->is<sf::Event::Closed>())
			window.close();

		if (GameState::MILITARY == m_gamestate)
		{
			window.clear();
			drawMilitaryVictoryScreen(window);
			continue;
		}
		if (GameState::SCIENTIFIC == m_gamestate)
		{
			window.clear();
			drawScientificVictoryScreen(window);
			continue;
		}
		if (GameState::CIVILIAN == m_gamestate)
		{
			window.clear();
			drawCivilianVictoryScreen(window);
			continue;
		}

		if (event->is<sf::Event::MouseButtonPressed>())
		{
			handleClick(window, sf::Mouse::getPosition(window));

		}

		bool ok = 0;
		for (auto card : m_cardDisplay[0])
			if (card.has_value())
			{
				ok = 1;
				break;
			}
		if (!ok)
		{
			if (m_currentAge == Building::Age::AGEI)
			{
				m_currentAge = Building::Age::AGEII;
				m_cardDisplay.clear();
				initAgeIIBoard();
			}
			else if (m_currentAge == Building::Age::AGEII)
			{
				m_currentAge = Building::Age::AGEIII;
				m_cardDisplay.clear();
				initAgeIIIBoard();
			}
			else {
				m_gamestate = CIVILIAN;
				window.clear();
				drawCivilianVictoryScreen(window);
				continue;
			}
			drawCurrentAgeCards(window);
			window.display();
		}
	}
}

void Game::drawSelectedCard(sf::RenderWindow& window)
{
	if (m_selectedBuilding != nullptr)
	{
		sf::Texture bigCard;
		bigCard.loadFromFile("..\\..\\Images\\" + std::to_string(m_selectedBuilding->getId()) + ".jpg");
		sf::Sprite bigCardSprite(bigCard);
		bigCardSprite.setScale(sf::Vector2f{ 0.5,0.5 });
		bigCardSprite.setPosition({ 75.f,35.f });
		window.draw(bigCardSprite);
	}
}

//void Game::calculateFinalScores()
//{
//	std::shared_ptr<Player> player1 = m_currentPlayer->name() == "player1" ? m_currentPlayer : m_otherPlayer;
//	std::shared_ptr<Player> player2 = m_currentPlayer->name() == "player2" ? m_currentPlayer : m_otherPlayer;
//	std::uint16_t player1Score = player1->calculateFinalScore();
//	std::uint16_t player2Score = player2->calculateFinalScore();
//	for (auto& guild : player1->getPurpleBuildings())
//	{
//		activateCardEffects(std::make_shared<Building>(guild));
//	}
//	for (auto& guild : player2->getPurpleBuildings())
//	{
//		activateCardEffects(std::make_shared<Building>(guild));
//	}
//	if (m_board.getPos() > 0 && m_board.getPos() < 3) {
//		player2Score += 2;
//	}
//	else if(m_board.getPos() >= 3 && m_board.getPos() < 6) {
//		player2Score += 5;
//	}
//	else if (m_board.getPos() >= 6 && m_board.getPos() < 9) {
//		player2Score += 10;
//	}
//	else if(m_board.getPos() < 0 && m_board.getPos() > -3) {
//		player1Score += 2;
//	}
//	else if (m_board.getPos() <= -3 && m_board.getPos() > -6) {
//		player1Score += 5;
//	}
//	else if (m_board.getPos() <= -6 && m_board.getPos() > -9) {
//		player1Score += 10;
//	}
//
//	std::cout << "Final Scores:\n";
//	std::cout << player1->name() << ": " << player1Score << " points\n" << player2Score << " points\n";
//	if (player1Score > player2Score)
//		std::cout << player1->name() << " wins!\n";
//	else if (player2Score > player1Score)
//		std::cout << player2->name() << " wins!\n";
//	else
//		std::cout << "It's a tie!\n";
//}

void Game::checkMilitaryVictory()
{
	if (m_board.getPos() >= 9)
	{
		m_gamestate = MILITARY;
		std::cout << "player2 wins by military conquest!\n";
	}
	else if (m_board.getPos() <= -9)
	{
		m_gamestate = MILITARY;
		std::cout << "player1 wins by military conquest!\n";
	}
}

void Game::drawMilitaryVictoryScreen(sf::RenderWindow& window)
{
	window.draw(m_backgroundSprite);
	const sf::Font font = []() {
		sf::Font font("C:\\Windows\\Fonts\\cour.ttf");
		return font;
		}();
	sf::Text titleText(font, "Military Victory", 50);
	titleText.setFillColor(sf::Color::Red);
	titleText.setPosition({ static_cast<float>(window.getSize().x) / 2.f - 200.f, static_cast<float>(window.getSize().y) / 2.f - 150.f });

	sf::Text victoryText(font, "", 50);
	victoryText.setFillColor(sf::Color::Black);
	victoryText.setPosition({ static_cast<float>(window.getSize().x) / 2.f - 200.f, static_cast<float>(window.getSize().y) / 2.f - 50.f });
	if (m_board.getPos() >= 9)
		victoryText.setString("player2 wins by military conquest!");
	else
		victoryText.setString("player1 wins by military conquest!");

	sf::FloatRect textRect = victoryText.getLocalBounds();
	victoryText.setOrigin(sf::Vector2f{ textRect.position.x + textRect.size.x / 2.0f,
		textRect.position.y + textRect.size.y / 2.0f });
	victoryText.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));

	window.draw(titleText);
	window.draw(victoryText);
	window.display();
}

void Game::drawCivilianVictoryScreen(sf::RenderWindow& window)
{
	window.draw(m_backgroundSprite);
	const sf::Font font = []() {
		sf::Font font("C:\\Windows\\Fonts\\cour.ttf");
		return font;
		}();

	std::shared_ptr<Player> player1 = m_currentPlayer->name() == "player1" ? m_currentPlayer : m_otherPlayer;
	std::shared_ptr<Player> player2 = m_currentPlayer->name() == "player2" ? m_currentPlayer : m_otherPlayer;
	std::uint16_t player1Score = player1->calculateFinalScore();
	std::uint16_t player2Score = player2->calculateFinalScore();
	for (auto& guild : player1->getPurpleBuildings())
	{
		activateCardEffects(std::make_shared<Building>(guild));
	}
	for (auto& guild : player2->getPurpleBuildings())
	{
		activateCardEffects(std::make_shared<Building>(guild));
	}

	if (m_board.getPos() > 0 && m_board.getPos() < 3) {
		player2Score += 2;
	}
	else if (m_board.getPos() >= 3 && m_board.getPos() < 6) {
		player2Score += 5;
	}
	else if (m_board.getPos() >= 6 && m_board.getPos() < 9) {
		player2Score += 10;
	}
	else if (m_board.getPos() < 0 && m_board.getPos() > -3) {
		player1Score += 2;
	}
	else if (m_board.getPos() <= -3 && m_board.getPos() > -6) {
		player1Score += 5;
	}
	else if (m_board.getPos() <= -6 && m_board.getPos() > -9) {
		player1Score += 10;
	}

	std::string winnerText;
	if (player1Score > player2Score) winnerText = "Player 1 Wins!";
	else if (player2Score > player1Score) winnerText = "Player 2 Wins!";
	else winnerText = "It's a Tie!";

	sf::Text titleText(font, "Civilian Victory", 50);
	titleText.setFillColor(sf::Color::Blue);

	sf::Text p1Text(font, "Player 1: " + std::to_string(player1Score), 35);
	p1Text.setFillColor(sf::Color::Black);

	sf::Text p2Text(font, "Player 2: " + std::to_string(player2Score), 35);
	p2Text.setFillColor(sf::Color::Black);

	sf::Text resultText(font, winnerText, 45);
	resultText.setFillColor(sf::Color::Red);

	// Positioning
	float centerX = window.getSize().x / 2.0f;
	float centerY = window.getSize().y / 2.0f;

	auto centerOrigin = [](sf::Text& t) {
		sf::FloatRect r = t.getLocalBounds();
		t.setOrigin(sf::Vector2f{ r.position.x + r.size.x / 2.0f, r.position.y + r.size.y / 2.0f });
		};

	centerOrigin(titleText);
	centerOrigin(p1Text);
	centerOrigin(p2Text);
	centerOrigin(resultText);

	titleText.setPosition({ centerX, centerY - 150 });
	p1Text.setPosition({ centerX, centerY - 50 });
	p2Text.setPosition({ centerX, centerY + 50 });
	resultText.setPosition({ centerX, centerY + 150 });

	window.draw(titleText);
	window.draw(p1Text);
	window.draw(p2Text);
	window.draw(resultText);
	window.display();
}

void Game::drawScientificVictoryScreen(sf::RenderWindow& window)
{
	window.draw(m_backgroundSprite);
	const sf::Font font = []() {
		sf::Font font("C:\\Windows\\Fonts\\cour.ttf");
		return font;
		}();
	sf::Text titleText(font, "Scientific Victory", 50);
	titleText.setFillColor(sf::Color::Green);
	titleText.setPosition({ static_cast<float>(window.getSize().x) / 2.f - 200.f, static_cast<float>(window.getSize().y) / 2.f - 100.f });
	sf::Text victoryText(font, "", 50);
	victoryText.setFillColor(sf::Color::Black);
	victoryText.setPosition({ static_cast<float>(window.getSize().x) / 2.f - 200.f, static_cast<float>(window.getSize().y) / 2.f });

	victoryText.setString(m_currentPlayer->name() + " wins by scientific supremacy!");
	sf::FloatRect textRect = victoryText.getLocalBounds();
	victoryText.setOrigin(sf::Vector2f{ textRect.position.x + textRect.size.x / 2.0f,
		textRect.position.y + textRect.size.y / 2.0f });
	victoryText.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
	window.draw(titleText);
	window.draw(victoryText);
	window.display();
}

void Game::run()
{
	//loadGame();
	m_gamestate = GAMESTART;
	bool player1Turn = true;
	initAgeIBoard();
	m_currentAge = Building::Age::AGEI;
	std::uint8_t move;
	std::vector<std::optional<std::shared_ptr<Card>>> wonders;
	m_selectedBuilding = nullptr;

	sf::RenderWindow window(sf::VideoMode({ 1500, 900 }), "7Wonders", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	int step = 1;

	while (window.isOpen())
	{

		window.draw(m_backgroundSprite);
		if (m_gamestate == GAMESTART) {
			drawWondersSelection(window);
		}
		window.display();
		PollEvents(window);
	}
}

std::uint8_t Game::m_constructedWonders = 0;

sf::Texture Game::m_background = []() {
	sf::Texture texture;
	texture.loadFromFile("..\\..\\Images\\Board\\background_playmat.jpg");
	return texture;
	}();

sf::Sprite Game::m_backgroundSprite = []() {
	sf::Sprite sprite(Game::m_background);
	int dimX = Game::m_background.getSize().x;
	int dimY = Game::m_background.getSize().y;
	sprite.setScale({ (float)(1500.0 / dimX),(float)(900.0 / dimY) });
	return sprite;
	}();

bool Game::m_isInPlayerBox = false;