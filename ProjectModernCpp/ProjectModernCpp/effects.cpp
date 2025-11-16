import effects;
import card;
import Building;
import Player;

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
