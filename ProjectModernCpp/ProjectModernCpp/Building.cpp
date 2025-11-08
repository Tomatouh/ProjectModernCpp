module Building;

Building::Building(Age age, Color color,std::uint8_t link, std::uint8_t wood, std::uint8_t clay, std::uint8_t stone,
	std::uint8_t glass, std::uint8_t papyrus, std::uint8_t victoryPoints,
	std::uint8_t shields, std::uint8_t coins, const std::optional<ScientificSymbol>& scientificSymbol) : m_age(age), m_color(color), m_link(link),
	m_wood(wood), m_clay(clay), m_stone(stone), m_glass(glass), m_papyrus(papyrus), m_victoryPoints(victoryPoints), m_shields(shields), 
	m_coins(coins), m_scientificSymbol(scientificSymbol)
{
}

Building::Building(const Building& other) : m_age(other.m_age), m_color(other.m_color), m_link(other.m_link),
m_wood(other.m_wood), m_clay(other.m_clay), m_stone(other.m_stone), m_glass(other.m_glass), m_papyrus(other.m_papyrus), m_victoryPoints(other.m_victoryPoints), m_shields(other.m_shields),
m_coins(other.m_coins), m_scientificSymbol(other.m_scientificSymbol)
{

}

void Building::swap(Building& other) noexcept
{
	std::swap(m_age, other.m_age);
	std::swap(m_color, other.m_color);
	std::swap(m_link, other.m_link);
	std::swap(m_wood, other.m_wood);
	std::swap(m_clay, other.m_clay);
	std::swap(m_stone, other.m_stone);
	std::swap(m_glass, other.m_glass);
	std::swap(m_papyrus, other.m_papyrus);
	std::swap(m_victoryPoints, other.m_victoryPoints);
	std::swap(m_shields, other.m_shields);
	std::swap(m_coins, other.m_coins);
	std::swap(m_scientificSymbol, other.m_scientificSymbol);
}
