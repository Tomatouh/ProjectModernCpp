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

void tradersGuild(Player& player1, Player& player2)
{
	player1.addCoins(std::max(player1.getYellowBuildings().size(), player2.getYellowBuildings().size()));

}

void loseThreeCoins(Player& player, Bank& bank)
{
	player.spendCoins(3);
}

void discardGrey(Player& player, std::uint8_t idCard)
{
	//player.discard(grey_cards, idCard);
}

//void addShields(bool player, Board& board)
//{
//	
//}
