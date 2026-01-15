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
		f << it->first << " ";
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
void Game::removeCardFromDeck(std::uint8_t id)
{
	for (int i = 0; i < m_cardDisplay.size(); i++)
		for (int j = 0; j < m_cardDisplay[i].size(); j++) {
			if (m_cardDisplay[i][j].has_value())
			{
				if (m_cardDisplay[i][j].value().getBuilding()->getId() == id)
				{
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

	}if (m_currentAge == Building::Age::AGEII)
	{
		// Iterate from the second-to-last row up to the top
		for (int i = m_cardDisplay.size() - 2; i >= 0; i--)
		{
			for (int j = 0; j < m_cardDisplay[i].size(); j++)
			{
				if (m_cardDisplay[i][j].has_value())
				{
					auto& card = m_cardDisplay[i][j].value();

					// Only proceed if the card is currently face down
					if (!card.isFaceUp())
					{
						bool isCovered = false;

						// 1. Check dependency on the left below: (i+1, j-1)
						if (j > 0 && m_cardDisplay[i + 1][j - 1].has_value()) {
							isCovered = true;
						}

						// 2. Check dependency on the right below: (i+1, j)
						if (j < m_cardDisplay[i + 1].size() && m_cardDisplay[i + 1][j].has_value()) {
							isCovered = true;
						}

						// If no cards are covering it, flip it
						if (!isCovered)
						{
							card.setFaceUp(true);
							std::uint16_t faceUpCardIndex = card.getBuilding()->getId();

							// Note: See the warning below regarding SFML textures
							sf::Texture texture;
							texture.loadFromFile("..\\..\\Images\\" + std::to_string(faceUpCardIndex) + ".jpg");
							m_guiCardDisplay[faceUpCardIndex].value().setTexture(texture);
						}
					}
				}
			}
		}
	}
	if (m_currentAge == Building::Age::AGEIII)
	{
		for (int i = m_cardDisplay.size() - 2; i >= 0; i--)
			for (int j = 0; j < m_cardDisplay[i].size(); j++)
				if (m_cardDisplay[i][j].has_value())
				{
					if (i < 2)// ageI strategy
					{
						if (m_cardDisplay[i][j].value().isFaceUp() == false && m_cardDisplay[i + 1][j].has_value() == false && m_cardDisplay[i + 1][j + 1].has_value() == false)
						{
							m_cardDisplay[i][j].value().setFaceUp(true);
							std::uint16_t faceUpCardIndex = m_cardDisplay[i][j].value().getBuilding()->getId();
							sf::Texture texture;
							texture.loadFromFile("..\\..\\Images\\" + std::to_string(faceUpCardIndex) + ".jpg");
							m_guiCardDisplay[faceUpCardIndex].value().setTexture(texture);
						}
					}
					if (i == 2)
					{
						if (m_cardDisplay[i][j].value().isFaceUp() == false && m_cardDisplay[i+1][j / 2].has_value() == false)
						{
							m_cardDisplay[i][j].value().setFaceUp(true);
							std::uint16_t faceUpCardIndex = m_cardDisplay[i][j].value().getBuilding()->getId();
							sf::Texture texture;
							texture.loadFromFile("..\\..\\Images\\" + std::to_string(faceUpCardIndex) + ".jpg");
							m_guiCardDisplay[faceUpCardIndex].value().setTexture(texture);
						}
					}
					if (i == 3)
					{
						if (m_cardDisplay[i][j].value().isFaceUp() == false && m_cardDisplay[i+1][j * 2].has_value() == false && m_cardDisplay[i+1][j * 2 +1 ].has_value() == false)
						{
							m_cardDisplay[i][j].value().setFaceUp(true);
							std::uint16_t faceUpCardIndex = m_cardDisplay[i][j].value().getBuilding()->getId();
							sf::Texture texture;
							texture.loadFromFile("..\\..\\Images\\" + std::to_string(faceUpCardIndex) + ".jpg");
							m_guiCardDisplay[faceUpCardIndex].value().setTexture(texture);
						}
					}
					if (i > 3)// ageII strategy
					{
						if (j == 0)
						{
							if (m_cardDisplay[i][j].value().isFaceUp() == false && m_cardDisplay[i + 1][j].has_value() == false)
							{
								m_cardDisplay[i][j].value().setFaceUp(true);
								std::uint16_t faceUpCardIndex = m_cardDisplay[i][j].value().getBuilding()->getId();
								sf::Texture texture;
								texture.loadFromFile("..\\..\\Images\\" + std::to_string(faceUpCardIndex) + ".jpg");
								m_guiCardDisplay[faceUpCardIndex].value().setTexture(texture);
							}
						}

						if (j > 0 && j < m_cardDisplay[i].size())
						{
							if (m_cardDisplay[i][j].value().isFaceUp() == false && m_cardDisplay[i + 1][j].has_value() == false && m_cardDisplay[i + 1][j - 1].has_value() == false)
							{
								m_cardDisplay[i][j].value().setFaceUp(true);
								std::uint16_t faceUpCardIndex = m_cardDisplay[i][j].value().getBuilding()->getId();
								sf::Texture texture;
								texture.loadFromFile("..\\..\\Images\\" + std::to_string(faceUpCardIndex) + ".jpg");
								m_guiCardDisplay[faceUpCardIndex].value().setTexture(texture);
							}
						}

						if (j == m_cardDisplay[i].size() - 1)
						{
							if (m_cardDisplay[i][j].value().isFaceUp() == false && m_cardDisplay[i + 1][j - 1].has_value() == false)
							{
								m_cardDisplay[i][j].value().setFaceUp(true);
								std::uint16_t faceUpCardIndex = m_cardDisplay[i][j].value().getBuilding()->getId();
								sf::Texture texture;
								texture.loadFromFile("..\\..\\Images\\" + std::to_string(faceUpCardIndex) + ".jpg");
								m_guiCardDisplay[faceUpCardIndex].value().setTexture(texture);
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

	sf::Text leftText(font,"Player 1 Details", 16);
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
			if(currentRowCard == 0)
				x = 647 - BoxSizes::boxHeight/2;
			else
				x += BoxSizes::boxHeight*2;
			currentRowCard++;
			if(currentRowCard == 2)
			{
				secondSectionDone = true;
				currentRowCard = 0;
				maxRowCards = 4;
				centeringOffset = 1;
				auto auxX = x;
				auto auxY = y;
				y += BoxSizes::boxHeight * 0.75 + 5;
				x = 647 - BoxSizes::boxHeight ;
				return { auxX,auxY };

			}
			return { x,y };
		}
		if(!thirdSectionDone)
		{
			if (currentRowCard==0)
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
	}
	else {
		drawCardSet(player->getBrownBuildings(), xPos, yPos, window, false);
		drawCardSet(player->getGreyBuildings(), xPos, yPos, window, false);
		drawCardSet(player->getYellowBuildings(), xPos, yPos, window, false);
		drawCardSet(player->getRedBuildings(), xPos, yPos, window, false);
		drawCardSet(player->getGreenBuildings(), xPos, yPos, window, false);
		drawCardSet(player->getBlueBuildings(), xPos, yPos, window, false);
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
	if(m_gamestate == ONGOING)
	{
		m_wondersDisplay.clear();
		total = 0;
		for(auto& wonderPair : m_currentPlayer->getWonders())
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
						else if (m_currentPlayer.get()->name() == "player2" && iteration==3) {
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
						else if (m_currentPlayer.get()->name() == "player1" && iteration==3) {
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
		if (CheckPlayerResources(m_currentPlayer, m_selectedBuilding) && CheckPlayerCoins(m_currentPlayer, m_selectedBuilding)) {
			m_currentPlayer->addBuilding(*m_selectedBuilding);
			removeCardFromDeck(m_selectedBuilding->getId());
			activateCardEffects(m_selectedBuilding);
			m_board.movePeon(m_selectedBuilding->getShields() * (m_currentPlayer->name() == "player1" ? -1 : 1));
			turnCards();
			std::swap(m_currentPlayer, m_otherPlayer);

		}
		else
		{
			std::cout << "You don't have enough resources/coins to build" << m_selectedBuilding->getName() << "Retry\n";
		}
		break;
	case 1:
		m_currentPlayer->addCoin(sellProfit);
		removeCardFromDeck(m_selectedBuilding->getId());
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
						removeCardFromDeck(m_selectedBuilding->getId());
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
			if(event->is<sf::Event::Closed>())
			{
				window.close();
				break;
			}
			//return option;
			//while (true)
			//{
			//	//PollEvents(window);
			//	int index = wonderIndexAtPosition(sf::Mouse::getPosition(window), window);
			//	if (index >= 0 && index < static_cast<int>(m_wondersDisplay.size())
			//		&& m_wondersDisplay[index].has_value()) {
			//		auto selectedWonder = m_wondersDisplay[index].value();
			//		m_selectedBuilding = selectAcceptableCard();
			//		if (m_currentPlayer->canBuildWonder(*(selectedWonder))) {
			//			m_currentPlayer->buildWonder(selectedWonder->getId(), m_selectedBuilding);
			//			Game::m_constructedWonders++;
			//			removeCardFromDeck(m_selectedBuilding->getId());
			//		}
			//		else {
			//			/*system("cls");*/
			//			std::cout << "You cannot build this wonder now. Retry\n";
			//			continue;
			//		}
			//	}
			//	break;
			//}
			/*drawPlayerWonders(leftPlayer, leftX, bottomY, window, true);
			drawPlayerWonders(rightPlayer, rightX, bottomY, window, true);*/
			/*std::cout << "Your wonders:\n";
			for (auto wonder : m_currentPlayer->getWonders())
				std::cout << "[" << wonder.first->getId() << "] ";
			std::cout << "\n";
			auto selectedWonder = selectAcceptableWonder();
			m_selectedBuilding = selectAcceptableCard();
			if (m_currentPlayer->canBuildWonder(*(selectedWonder.first)))
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
			}*/
		}
		m_selectedBuilding = nullptr;
		window.draw(m_backgroundSprite);
		redrawCurrentAgeCards(window);
		drawPlayerCards(window);
		drawClickAreaForPlayerDetails(window);
		drawMilitaryBoard(window);
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
						if(i == m_cardDisplay.size() - 1)
						{
							m_selectedBuilding = m_cardDisplay[i][j].value().getBuilding();
							m_cardDisplay[i][j].value().setSelected(true);
							m_guiCardDisplay[m_selectedBuilding->getId()].value().setHighlighted(true);
							//window.draw(m_guiCardDisplay[m_selectedBuilding->getId()].value());
							found = true;
						}
						else {
							if((j == 0 && m_cardDisplay[i + 1][j].has_value() == false) || (j == m_cardDisplay[i].size() - 1 && m_cardDisplay[i + 1][j - 1].has_value() == false) || (j > 0 && j < m_cardDisplay[i].size() && m_cardDisplay[i + 1][j].has_value() == false && m_cardDisplay[i + 1][j - 1].has_value() == false))
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
					if(m_currentAge == Building::Age::AGEIII)
					{
						if (i == m_cardDisplay.size() - 1 ||
						   (i < 2 && m_cardDisplay[i + 1][j].has_value() == false && m_cardDisplay[i + 1][j + 1].has_value() == false) ||
						   (i==2 && m_cardDisplay[i+1][j / 2].has_value() == false) ||
						   (i==3 && m_cardDisplay[i+1][j * 2].has_value() == false && m_cardDisplay[i+1][j * 2 + 1].has_value() == false) ||
						   (i>3 && ((j == 0 && m_cardDisplay[i + 1][j].has_value() == false) || (j == m_cardDisplay[i].size() - 1 && m_cardDisplay[i + 1][j - 1].has_value() == false) || (j > 0 && j < m_cardDisplay[i].size() && m_cardDisplay[i + 1][j].has_value() == false && m_cardDisplay[i + 1][j - 1].has_value() == false)
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
	const float boxX = 840.0f;
	const float boxY = 160.0f;
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
				if (m_currentPlayer->name().compare("player1")==0)
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
		drawMilitaryBoard(window);
		window.display();
		}
		else
		{
			if(wasExitPlayerBoxClicked(window, mousePos))
			{
				m_isInPlayerBox = false;
				window.draw(m_backgroundSprite);
				redrawCurrentAgeCards(window);
				drawPlayerCards(window);
				drawClickAreaForPlayerDetails(window);
				drawMilitaryBoard(window);
				window.display();
			}
		}
	}
}

void Game::drawPlayerBox(sf::RenderWindow& window,const std::shared_ptr<Player>& selectedPlayer)
{
	const sf::Font font = []() {
		sf::Font font("C:\\Windows\\Fonts\\cour.ttf");
		return font;
		}();
	sf::RectangleShape backgroundBox;
	backgroundBox.setSize({ 400.f, 600.f });
	backgroundBox.setFillColor(sf::Color::White);
	backgroundBox.setOutlineColor(sf::Color::Black);
	backgroundBox.setOutlineThickness(3.f);
	backgroundBox.setPosition({ static_cast<float>(window.getSize().x) / 2 - 200.f, static_cast<float>(window.getSize().y) / 2 - 300.f });
	
	sf::Text coinsLabel(font, "Coins: " + std::to_string(selectedPlayer->getCoins()), 20);
	coinsLabel.setPosition({ backgroundBox.getPosition().x + 20.f, backgroundBox.getPosition().y + 20.f });
	coinsLabel.setFillColor(sf::Color::Black);

	sf::Text victoryPointsLabel(font, "Victory Points: " + std::to_string(selectedPlayer->getVictoryPoints()), 20);
	victoryPointsLabel.setPosition({ backgroundBox.getPosition().x + 20.f, backgroundBox.getPosition().y + 60.f });
	victoryPointsLabel.setFillColor(sf::Color::Black);

	sf::Text woodLabel(font, "Wood: " + std::to_string(selectedPlayer->getWood()), 20);
	woodLabel.setPosition({ backgroundBox.getPosition().x + 20.f, backgroundBox.getPosition().y + 100.f });
	woodLabel.setFillColor(sf::Color::Black);

	sf::Text stoneLabel(font, "Stone: " + std::to_string(selectedPlayer->getStone()), 20);
	stoneLabel.setPosition({ backgroundBox.getPosition().x + 20.f, backgroundBox.getPosition().y + 140.f });
	stoneLabel.setFillColor(sf::Color::Black);

	sf::Text clayLabel(font, "Clay: " + std::to_string(selectedPlayer->getClay()), 20);
	clayLabel.setPosition({ backgroundBox.getPosition().x + 20.f, backgroundBox.getPosition().y + 180.f });
	clayLabel.setFillColor(sf::Color::Black);

	sf::Text glassLabel(font, "Glass: " + std::to_string(selectedPlayer->getGlass()), 20);
	glassLabel.setPosition({ backgroundBox.getPosition().x + 20.f, backgroundBox.getPosition().y + 220.f });
	glassLabel.setFillColor(sf::Color::Black);

	sf::Text papyrusLabel(font, "Papyrus: " + std::to_string(selectedPlayer->getPapyrus()), 20);
	papyrusLabel.setPosition({ backgroundBox.getPosition().x + 20.f, backgroundBox.getPosition().y + 260.f });
	papyrusLabel.setFillColor(sf::Color::Black);

	sf::RectangleShape exitBox;
	exitBox.setSize({ 100.f, 40.f });
	exitBox.setFillColor(sf::Color(200, 0, 0));
	exitBox.setPosition({ backgroundBox.getPosition().x + backgroundBox.getSize().x - exitBox.getSize().x - 10.f,
		backgroundBox.getPosition().y + 10.f });
	sf::Text exitLabel(font, "X", 30);
	exitLabel.setPosition({ exitBox.getPosition().x + 30.f, exitBox.getPosition().y + 5.f });
	exitLabel.setFillColor(sf::Color::White);

	window.draw(backgroundBox);
	window.draw(coinsLabel);
	window.draw(victoryPointsLabel);
	window.draw(woodLabel);
	window.draw(stoneLabel);
	window.draw(clayLabel);
	window.draw(glassLabel);
	window.draw(papyrusLabel);
	window.draw(exitBox);
	window.draw(exitLabel);
}

void Game::drawMilitaryBoard(sf::RenderWindow& window)
{
	sf::Texture militaryTexture;
	militaryTexture.loadFromFile("..\\..\\Images\\Board\\board.png");
	sf::Sprite militarySprite(militaryTexture);
	militarySprite.setScale({ 0.15f, 0.15f });
	militarySprite.setPosition({ static_cast<float>(window.getSize().x) / 2.f-225, 720.f});
	window.draw(militarySprite);


	sf::Texture tokenTexture;
	int i = 0;
	for (float x= static_cast<float>(window.getSize().x) / 2.f - 115;i<m_progressTokensDeck.size();x=x+45,i++)
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

	if(!m_board.getZoneTriggers()[1])
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

void Game::PollEvents(sf::RenderWindow& window)
{
	while (const std::optional event = window.waitEvent())
	{
		if (event->is<sf::Event::Closed>())
			window.close();
		if (event->is<sf::Event::Resized>()) {
			window.setView(window.getDefaultView());
			window.draw(m_backgroundSprite);
			m_wonderRects.clear();
			if (m_gamestate == GAMESTART)
				drawWondersSelection(window);
			if (m_gamestate == ONGOING) {

				redrawCurrentAgeCards(window);
				drawPlayerCards(window);
				drawClickAreaForPlayerDetails(window);
				drawMilitaryBoard(window);
			}
			window.display();
		}
		if (event->is<sf::Event::MouseButtonPressed>())
		{
			handleClick(window, sf::Mouse::getPosition(window));
		}

		bool ok = 0;
		for (auto row : m_cardDisplay)
			for (auto card : row)
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
			else
			{
				m_currentAge = Building::Age::AGEIII;
				m_cardDisplay.clear();
				initAgeIIIBoard();
			}

			drawCurrentAgeCards(window);
		}
	}
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
	//std::uint16_t iteration = 0;

	sf::RenderWindow window(sf::VideoMode({ 1500, 900 }), "7Wonders", sf::Style::Close);
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
		//wondersSetup(window);






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