module effects;
import card;
import Player;
import board;





void discardGrey(std::shared_ptr<Player> player)
{
	Player otherPlayer = *(player->getOtherPlayer());
	for (auto& greyCard : otherPlayer.getGreyBuildings())
	{
		std::cout << "[" << greyCard.getId() << "] ";
	}
	uint16_t idCard;
	std::shared_ptr<Building> discarded;
	std::cout << "\nCard id to discard: ";
	while (true)
	{
		std::cin >> idCard;
		auto it = std::find_if(otherPlayer.getGreyBuildings().begin(), otherPlayer.getGreyBuildings().end(),
			[idCard](const Building& b) { return b.getId() == idCard; });
		if (it != otherPlayer.getGreyBuildings().end()) {
			discarded = std::make_shared<Building>(*it);
			break;
		}
		std::cout << "Invalid input. Please enter a valid card id: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	otherPlayer.discardBuilding(Building::Color::GREY, idCard);
	otherPlayer.removeResources(discarded->getResources());
}

void discardBrown(std::shared_ptr<Player> player)
{
	Player otherPlayer = *(player->getOtherPlayer());
	for (auto& brownCard : otherPlayer.getBrownBuildings())
	{
		std::cout << "[" << brownCard.getId() << "] ";
	}
	uint16_t idCard;
	std::shared_ptr<Building> discarded;
	std::cout << "\nCard id to discard: ";
	while (true)
	{
		std::cin >> idCard;
		auto it = std::find_if(otherPlayer.getBrownBuildings().begin(), otherPlayer.getBrownBuildings().end(),
			[idCard](const Building& b) { return b.getId() == idCard; });
		if (it != otherPlayer.getBrownBuildings().end()) {
			discarded = std::make_shared<Building>(*it);
			break;
		}
		std::cout << "Invalid input. Please enter a valid card id: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	otherPlayer.discardBuilding(Building::Color::BROWN, idCard);
	otherPlayer.removeResources(discarded->getResources());
}

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

void drawProgress(std::shared_ptr<Player> player, std::vector<std::unique_ptr<Player::ProgressToken>>& m_progressTokensDeck)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	auto copyDeck = m_progressTokensDeck;
	for (int i = 0; i < 2; ++i)
	{
		std::uniform_int_distribution<> dist(0, m_progressTokensDeck.size() - 1);
		std::uint16_t index = dist(gen);
		std::cout << "[" << index << "] ";
		copyDeck.emplace_back(std::move(m_progressTokensDeck[index]));
	}

	std::cout << "\nProgress token id to choose: ";
	std::uint16_t idToken;
	while (!(std::cin >> idToken) || idToken >= copyDeck.size())
	{
		std::cout << "Invalid input. Please enter a valid progress token id: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	player->addProgressToken(*copyDeck[idToken]);
	copyDeck[idToken]->applyEffect(std::make_unique<Player>(player));
	copyDeck.erase(copyDeck.begin() + idToken);
	m_progressTokensDeck.insert(m_progressTokensDeck.end(), std::make_move_iterator(copyDeck.begin()), std::make_move_iterator(copyDeck.end()));
}

void constructCard(std::shared_ptr<Player> player)
{
	for (auto& pair : *(player->getDiscardPile()))
	{
		std::cout << "[" << pair.first << "] " << pair.second->getName() << "\n";
	}
	std::uint16_t idCard;
	std::cout << "\nCard id to construct: ";
	while (!(std::cin >> idCard) || player->getDiscardPile()->find(idCard) == player->getDiscardPile()->end())
	{
		std::cout << "Invalid input. Please enter a valid card id: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	player->addBuilding(*(player->getDiscardPile()->at(idCard)));
	player->removeCardFromDiscardPile(idCard);
}


