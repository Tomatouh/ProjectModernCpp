module card;



	Card::Cost::Cost(std::uint16_t link, const std::vector<ResourceType>& resources, std::uint16_t coins) : m_link(link), m_resources(resources), m_coins(coins)
	{
	}
	std::uint16_t Card::Cost::getLink() const
	{
		return m_link;
	}
	std::vector<ResourceType> Card::Cost::getCostResources() const
	{
		return m_resources;
	}
	/*std::vector<ResourceType> Card::Cost::getResources() const
	{
		return m_resources;
	}*/

	std::uint16_t Card::Cost::getCostCoins() const
	{
		return m_coins;
	}
	
	std::uint16_t Card::getCoins() const
	{
		return m_coins;
	}

	Card::Card(const std::vector<Effect>& effects, const Card::Cost& cost, std::string_view name, std::uint16_t id, 
		std::uint16_t victoryPoints, std::uint16_t shields, std::uint16_t coins) : m_effects(effects),
		m_cost(cost), m_name(name), m_id(id), m_victoryPoints(victoryPoints), m_shields(shields), m_coins(coins)
	{
	}
	Card::Card(const Card & other) : m_effects(other.m_effects), m_cost(other.m_cost), m_name(other.m_name), m_id(other.m_id), 
		m_victoryPoints(other.m_victoryPoints), m_shields(other.m_shields), m_coins(other.m_coins)
	{
	}
	Card::Card(Card&& other) noexcept
	{
		this->swap(other);
	}
	Card& Card::operator=(const Card& other)
	{
		Card tempCard{ other };
		this->swap(tempCard);
		return *this;
	}
	Card& Card::operator=(Card&& other) noexcept
	{
		this->swap(other);
		return *this;
	}

	void Card::swap(Card& other) noexcept
	{
		std::swap(m_effects, other.m_effects);
		std::swap(m_cost, other.m_cost);
		std::swap(m_name, other.m_name);
		std::swap(m_id, other.m_id);
		std::swap(m_victoryPoints, other.m_victoryPoints);
		std::swap(m_shields, other.m_shields);
		std::swap(m_coins, other.m_coins);
	}

	std::vector<Card::Effect> Card::getEffects() const
	{
		return m_effects;
	}

	Card::Cost Card::getCost() const
	{
		return m_cost;
	}

	std::string Card::getName() const
	{
		return m_name;
	}

	std::uint16_t Card::getId() const
	{
		return m_id;
	}

	std::uint16_t Card::getVictoryPoints() const
	{
		return m_victoryPoints;
	}

	std::uint16_t Card::getShields() const
	{
		return m_shields;
	}

	
