module Building;

Building::Building(const std::vector<Effect>& effects, const Cost& cost, std::string_view name, std::uint8_t id,
	std::uint8_t victoryPoints, std::uint8_t shields, std::uint8_t coins, Age age, Color color, const std::vector<ResourceType>& resources, const std::optional<ScientificSymbol>& scientificSymbol) :
	Card(effects, cost, name, id, victoryPoints, shields, coins), m_age(age), m_color(color), m_resources(resources), m_scientificSymbol(scientificSymbol)
{
}

Building::Building(const Building& other) : Card(other), m_age(other.m_age), m_color(other.m_color), m_resources(other.m_resources),
m_scientificSymbol(other.m_scientificSymbol)
{
}

Building::Building(Building&& other) noexcept
{
	this->swap(other);
}

Building& Building::operator=(const Building& other)
{
	Building tempBuilding{ other };
	this->swap(tempBuilding);
	return *this;
}

Building& Building::operator=(Building&& other) noexcept
{
	this->swap(other);
	return *this;
}

void Building::swap(Building& other) noexcept
{
	Card::swap(other);
	std::swap(m_age, other.m_age);
	std::swap(m_color, other.m_color);
	std::swap(m_resources, other.m_resources);
	std::swap(m_scientificSymbol, other.m_scientificSymbol);
}

Building::Age Building::getAge() const
{
	return m_age;
}

Building::Color Building::getColor() const
{
	return m_color;
}
std::vector<ResourceType> Building::getResources() const
{
	return m_resources;
}
std::optional<Building::ScientificSymbol> Building::getScientificSymbol() const
{
	return m_scientificSymbol;
}
