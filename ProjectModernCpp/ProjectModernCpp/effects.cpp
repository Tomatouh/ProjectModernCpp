import effects;
import card;
import Player;
import board;

void addCoins(Player& player, const Card& card)
{
	player.addCoin(card.getCoins());

}
void addVictorypoints(Player& player, const Card& card) {
	player.addVictoryPoints(card.getVictoryPoints());
}






void addScientificSymbol(Player& player, const Building& card)
{
	player.addBuilding(card);
}

void threeCoinsPerGray(Player& player)
{
	player.addCoin(player.getGreyBuildings().size() * 3);

}

void twoCoinsPerBrown(Player& player)
{
	player.addCoin(player.getBrownBuildings().size() * 2);
}

void oneCoinPerYellow(Player& player)
{
	player.addCoin(player.getYellowBuildings().size());
}

void oneCoinPerRed(Player& player)
{
	player.addCoin(player.getRedBuildings().size());
}

void buildersGuild(Player& player1, const Player& player2, bool endGame)
{
	if (endGame) player1.addVictoryPoints(2 * std::max(player1.getWonders().size(), player2.getWonders().size()));
}

void tradersGuild(Player& player1, const Player& player2, bool endGame)
{
	if (!endGame) {
		player1.addCoin(std::max(player1.getYellowBuildings().size(), player2.getYellowBuildings().size()));
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
		player1.addCoin(std::max(player1.getBlueBuildings().size(), player2.getBlueBuildings().size()));
	}
	else {
		player1.addVictoryPoints(std::max(player1.getBlueBuildings().size(), player2.getBlueBuildings().size()));
	}
}

void scientistsGuild(Player& player1, const Player& player2, bool endGame)
{
	if (!endGame) {
		player1.addCoin(std::max(player1.getGreenBuildings().size(), player2.getGreenBuildings().size()));
	}
	else {
		player1.addVictoryPoints(std::max(player1.getGreenBuildings().size(), player2.getGreenBuildings().size()));
	}
}

void tacticiansGuild(Player& player1, const Player& player2, bool endGame)
{
	if (!endGame) {
		player1.addCoin(std::max(player1.getRedBuildings().size(), player2.getRedBuildings().size()));
	}
	else {
		player1.addVictoryPoints(std::max(player1.getRedBuildings().size(), player2.getRedBuildings().size()));
	}
}

void shipownersGuild(Player& player1, const Player& player2, bool endGame)
{
	if (!endGame) {
		player1.addCoin(std::max(player1.getBrownBuildings().size() + player1.getGreyBuildings().size(),
			player2.getBrownBuildings().size() + player2.getGreyBuildings().size()));
	}
	else {
		player1.addVictoryPoints(std::max(player1.getBrownBuildings().size() + player1.getGreyBuildings().size(),
			player2.getBrownBuildings().size() + player2.getGreyBuildings().size()));
	}
}

void loseThreeCoins(Player& player)
{
	player.addCoin(3);
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

void twoCoinsPerWonder(Player& player)
{
	player.addCoin(player.getWonders().size() * 2);
}

void addShields( Board& board, const Card& card)
{
	board.move(card.getShields());
}
