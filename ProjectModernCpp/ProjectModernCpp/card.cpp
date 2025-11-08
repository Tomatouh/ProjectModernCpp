module card;



	Card::Cost::Cost(const std::vector<ResourceType>& resources, std::uint16_t coins) : m_resources(resources), m_coins(coins)
	{
	}
	std::vector<ResourceType> Card::Cost::getResources() const
	{
		return m_resources;
	}
	std::uint16_t Card::Cost::getCoins() const
	{
		return m_coins;
	}

	Card::Card(const std::vector<Effect>& effects, const Card::Cost& cost, std::string_view name, std::uint8_t id) : m_effects(effects),
		m_cost(cost), m_name(name), m_id(id)
	{
	}
	Card::Card(const Card & other) : m_effects(other.m_effects), m_cost(other.m_cost), m_name(other.m_name), m_id(other.m_id)
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
	}
