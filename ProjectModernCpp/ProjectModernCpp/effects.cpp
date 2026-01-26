module effects;
import card;
import Player;
import board;





std::uint16_t maxConstructedWonders(std::shared_ptr<Player> player)
{
	std::uint16_t constructedWonders1 = 0, constructedWonders2 = 0;
	for (int i = 0; i < player->getWonders().size(); ++i)
	{
		if (player->getWonders()[i].second.has_value())
			constructedWonders1++;
		if (player->getOtherPlayer()->getWonders()[i].second.has_value())
			constructedWonders2++;
	}
	return std::max(constructedWonders1, constructedWonders2);
}



