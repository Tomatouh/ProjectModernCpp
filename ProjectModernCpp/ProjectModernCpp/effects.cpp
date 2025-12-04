import effects;
import card;
import Player;
import board;
import bank;

void addCoins(Player& player, const Card& card, Bank& bank)
{
	bank.take(card.getCoins(), player);

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

void chooseRawResource(Player& player)
{
	std::cout << "Choose between WOOD, CLAY or STONE (type the initial lowercase letter of the desired resource): ";
	char chosenRes;
	while (true)
	{
		std::cin >> chosenRes;

		switch (chosenRes)
		{
		case 'w':
			player.addWood();
			break;
		case 'c':
			player.addClay();
			break;
		case 's':
			player.addStone();
			break;
		default:
			std::cout << "Invalid input. Try again.";
		}
	}
}

void chooseManufacturedGood(Player& player)
{
	std::cout << "Choose between GLASS or PAPYRUS (type the initial lowercase letter of the desired resource): ";
	char chosenRes;
	while (true)
	{
		std::cin >> chosenRes;

		switch (chosenRes)
		{
		case 'g':
			player.addGlass();
			break;
		case 'p':
			player.addPapyrus();
			break;
		default:
			std::cout << "Invalid input. Try again.";
		}
	}
}



void addScientificSymbol(Player& player, const Building& card)
{
	player.addBuilding(card);
}

void threeCoinsPerGray(Player& player, Bank& bank)
{
	bank.take(player.getGreyBuildings().size() * 3, player);

}

void twoCoinsPerBrown(Player& player, Bank& bank)
{
	bank.take(player.getBrownBuildings().size() * 2, player);
}

void oneCoinPerYellow(Player& player, Bank& bank)
{
	bank.take(player.getYellowBuildings().size(), player);
}

void oneCoinPerRed(Player& player, Bank& bank)
{
	bank.take(player.getRedBuildings().size(), player);
}

void buildersGuild(Player& player1, const Player& player2, bool endGame)
{
	if (endGame) player1.addVictoryPoints(2 * std::max(player1.getWonders().size(), player2.getWonders().size()));
}

void tradersGuild(Player& player1, const Player& player2, bool endGame, Bank& bank)
{
	if (!endGame) {
		bank.take(std::max(player1.getYellowBuildings().size(), player2.getYellowBuildings().size()), player1);
	}
	else {
		player1.addVictoryPoints(std::max(player1.getYellowBuildings().size(), player2.getYellowBuildings().size()));
	}

}

void moneylendersGuild(Player& player1, const Player& player2, bool endGame, Bank& bank)
{
	if (endGame) player1.addVictoryPoints(std::max(player1.getVictoryPoints(), player2.getVictoryPoints()));
}

void magistratesGuild(Player& player1, const Player& player2, bool endGame, Bank& bank)
{
	if (!endGame) {
		bank.take(std::max(player1.getBlueBuildings().size(), player2.getBlueBuildings().size()), player1);
	}
	else {
		player1.addVictoryPoints(std::max(player1.getBlueBuildings().size(), player2.getBlueBuildings().size()));
	}
}

void scientistsGuild(Player& player1, const Player& player2, bool endGame, Bank& bank)
{
	if (!endGame) {
		bank.take(std::max(player1.getGreenBuildings().size(), player2.getGreenBuildings().size()), player1);
	}
	else {
		player1.addVictoryPoints(std::max(player1.getGreenBuildings().size(), player2.getGreenBuildings().size()));
	}
}

void tacticiansGuild(Player& player1, const Player& player2, bool endGame, Bank& bank)
{
	if (!endGame) {
		bank.take(std::max(player1.getRedBuildings().size(), player2.getRedBuildings().size()), player1);
	}
	else {
		player1.addVictoryPoints(std::max(player1.getRedBuildings().size(), player2.getRedBuildings().size()));
	}
}

void shipownersGuild(Player& player1, const Player& player2, bool endGame, Bank& bank)
{
	if (!endGame) {
		bank.take(std::max(player1.getBrownBuildings().size() + player1.getGreyBuildings().size(),
			player2.getBrownBuildings().size() + player2.getGreyBuildings().size()), player1);
	}
	else {
		player1.addVictoryPoints(std::max(player1.getBrownBuildings().size() + player1.getGreyBuildings().size(),
			player2.getBrownBuildings().size() + player2.getGreyBuildings().size()));
	}
}

void loseThreeCoins(Player& player, Bank& bank)
{
	bank.take(3, player);
}

void discardGrey(Player& player, std::uint8_t idCard, std::vector<std::shared_ptr<Card>>& discardedCards)
{	
	std::shared_ptr<Card> discarded = std::make_shared<Card>(player.discardBuilding(Building::Color::GREY, idCard));
	discardedCards.push_back(discarded);
}

void discardBrown(Player& player, std::uint8_t idCard, std::vector<std::shared_ptr<Card>>& discardedCards)
{
	std::shared_ptr<Card> discarded = std::make_shared<Card>(player.discardBuilding(Building::Color::BROWN, idCard));
	discardedCards.push_back(discarded);
}

void twoCoinsPerWonder(Player& player, Bank& bank)
{
	bank.take(player.getWonders().size() * 2, player);
}

void addShields(bool player, Board& board, const Card& card)
{
	board.move(card.getShields(), player);
}
