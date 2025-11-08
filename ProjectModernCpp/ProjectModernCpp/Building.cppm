export module Building;
import card;
import std;

export class Building : Card {
public:
	enum class Age {
		AGEI,
		AGEII,
		AGEIII,
	};
	enum class Color {
		BROWN,
		GREY,
		BLUE,
		GREEN,
		YELLOW,
		RED,
		PURPLE
	};
	enum class ScientificSymbol {
		GLOBE,
		SCALE,
		SUNDIAL,
		BOWL,
		SETSQUARE,
		FEATHER,
		WHEEL
	};
	

	Building(Age age, Color color, const std::uint8_t link, std::uint8_t wood, std::uint8_t clay, std::uint8_t stone,
		std::uint8_t glass, std::uint8_t papyrus, std::uint8_t victoryPoints,
		std::uint8_t shields, std::uint8_t coins, const std::optional<ScientificSymbol>& scientificSymbol);
	Building(const Building& other);
	Building(Building&& other) noexcept;
	Building& operator=(const Building& other);
	Building& operator=(Building&& other) noexcept;
	~Building() = default;

	void swap(Building& other) noexcept;


private:
	Age m_age;
	Color m_color;
	std::uint8_t m_link;
	std::uint8_t m_wood;
	std::uint8_t m_clay;
	std::uint8_t m_stone;
	std::uint8_t m_glass;
	std::uint8_t m_papyrus;
	std::optional<ScientificSymbol> m_scientificSymbol;

};


