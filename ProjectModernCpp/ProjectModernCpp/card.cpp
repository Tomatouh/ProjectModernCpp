module card;
//import <iostream>;

namespace SevenWonders {
	Card::Cost::Cost(const std::vector<ResourceType>& resources, std::uint16_t coins) : m_resources(resources), m_coins(coins)
	{
	}
	Card::Card(const std::vector<Effect>& effects, const Card::Cost& cost, std::string_view name) : m_effects(effects),
		m_cost(cost), m_name(name)
	{
	}
	Card::Card(const Card & other) : m_effects(other.m_effects), m_cost(other.m_cost), m_name(other.m_name)
	{
	}
}