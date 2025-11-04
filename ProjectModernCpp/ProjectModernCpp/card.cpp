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
	Card::Card(const std::vector<Effect>& effects, const Card::Cost& cost, std::string_view name) : m_effects(effects),
		m_cost(cost), m_name(name)
	{
	}
	Card::Card(const Card & other) : m_effects(other.m_effects), m_cost(other.m_cost), m_name(other.m_name)
	{
	}
	Card::Card(Card&& other) : m_effects(other.m_effects), m_cost(other.m_cost), m_name(other.m_name)
	{
		other.m_effects.clear();
		other.m_cost.getResources().clear();
	}
	Card& Card::operator=(const Card& other)
	{
		m_effects = other.m_effects;
		m_cost = other.m_cost;
		m_name = other.m_name;
		return *this;
	}
	Card& Card::operator=(Card&& other)
	{
		m_effects.clear();
		m_cost.getResources().clear();
		m_effects = other.m_effects;
		m_cost = other.m_cost;
		other.m_effects.clear();
		other.m_cost.getResources().clear();
		return *this;
	}
