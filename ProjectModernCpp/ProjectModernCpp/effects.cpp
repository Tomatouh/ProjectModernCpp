import effects;
import card;
import Player;
import board;

void addCoins(Player& player, const Card& card)
{

	player.addCoins(card.getCoins());

}
void addVictorypoints(Player& player, const Card& card) {
	player.addVictoryPoints(card.getVictoryPoints());
}

void addResources(Player& player, const Building& building)
{
	for (const auto& resource : building.getResources())
	{
		switch (resource)
		{
		case ResourceType::WOOD:
			player.addWood();
			break;
		case ResourceType::CLAY:
			player.addClay();
			break;
		case ResourceType::STONE:
			player.addStone();
			break;
		case ResourceType::GLASS:
			player.addGlass();
			break;
		case ResourceType::PAPYRUS:
			player.addPapyrus();
			break;
		default:
			break;
		}
	}
}

//void addEveryResource(Player& player, const Building& card)
//{
//	for (auto& res : card.getResources())
//	{
//		switch (res)
//		{
//			case ResourceType::WOOD
//		}
//	}
//}

void addScientificSymbol(Player& player, const Building& card)
{
	player.addBuilding(card);
}

void threeCoinsPerGray(Player& player)
{
	player.addCoins(player.getGreyBuildings().size() * 3);
}

void twoCoinsPerBrown(Player& player)
{
	player.addCoins(player.getBrownBuildings().size() * 2);
}

void oneCoinPerYellow(Player& player)
{
	player.addCoins(player.getYellowBuildings().size());
}

void oneCoinPerRed(Player& player)
{
	player.addCoins(player.getRedBuildings().size());
}

void buildersGuild(Player& player1, const Player& player2, bool endGame)
{
	if (endGame) player.addVictoryPoints(2 * std::max(player1.getWonders().size(), player2.getWonders().size()));
}

void tradersGuild(Player& player1, const Player& player2, bool endGame)
{
	if (!endGame) {
		player1.addCoins(std::max(player1.getYellowBuildings().size(), player2.getYellowBuildings().size()));
	}
	else {
		player1.addVictoryPoints(std::max(player1.getYellowBuildings().size(), player2.getYellowBuildings().size()));
	}

}

void moneylendersGuild(Player& player1, const Player& player2, bool endGame)
{
	if (endGame) player1.addVictoryPoints(std::max(player1.getVictoryPoints(), player2.getVictoryPoints()));
}

void magistratesGuild(Player& player1, const Player& player2, bool endGame)
{
	if (!endGame) {
		player1.addCoins(std::max(player1.getBlueBuildings().size(), player2.getBlueBuildings().size()));
	}
	else {
		player1.addVictoryPoints(std::max(player1.getBlueBuildings().size(), player2.getBlueBuildings().size()));
	}
}

void scientistsGuild(Player& player1, const Player& player2, bool endGame)
{
	if (!endGame) {
		player1.addCoins(std::max(player1.getGreenBuildings().size(), player2.getGreenBuildings().size()));
	}
	else {
		player1.addVictoryPoints(std::max(player1.getGreenBuildings().size(), player2.getGreenBuildings().size()));
	}
}

void tacticiansGuild(Player& player1, const Player& player2, bool endGame)
{
	if (!endGame) {
		player1.addCoins(std::max(player1.getRedBuildings().size(), player2.getRedBuildings().size()));
	}
	else {
		player1.addVictoryPoints(std::max(player1.getRedBuildings().size(), player2.getRedBuildings().size()));
	}
}

void shipownersGuild(Player& player1, const Player& player2, bool endGame)
{
	if (!endGame) {
		player1.addCoins(std::max(player1.getBrownBuildings().size()+player1.getGreyBuildings().size(), 
			player2.getBrownBuildings().size() + player2.getGreyBuildings().size()));
	}
	else {
		player1.addVictoryPoints(std::max(player1.getBrownBuildings().size() + player1.getGreyBuildings().size(),
			player2.getBrownBuildings().size() + player2.getGreyBuildings().size()));
	}
}

void loseThreeCoins(Player& player, Bank& bank)
{
	player.spendCoins(3);
}

void discardGrey(Player& player, std::uint8_t idCard, std::vector<Card> discardedCards)
{
	discardedCards.push_back(player.discard(player.getGreyBuildings(), idCard));
}

void discardBrown(Player& player, std::uint8_t idCard, std::vector<Card> discardedCards)
{
	discardedCards.push_back(player.discard(player.getGreyBuildings(), idCard));
}

//void addShields(bool player, Board& board)
//{
//	
//}
