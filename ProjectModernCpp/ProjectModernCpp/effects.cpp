import effects;
import card;
import Player;

void addCoins(Player& player, const Card& card)
{
	player.addCoins(card.getCoins());
}
