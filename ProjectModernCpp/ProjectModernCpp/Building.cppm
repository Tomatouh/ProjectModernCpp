export module Building;
import buildingResource;
import card;
import std;


export class Building : public Card {
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
	
	Building() = default;
	Building(const std::vector<Effect>& effects, const Cost& cost, std::string_view name, std::uint16_t id,
		std::uint16_t victoryPoints, std::uint16_t shields, std::uint16_t coins, Age age, Color color, const std::vector<ResourceType>& resources, const std::optional<ScientificSymbol>& scientificSymbol);
	Building(const Building& other);
	Building(const Age& m_age, const Color& m_color, const std::vector<ResourceType>& m_resources, const std::optional<ScientificSymbol>& m_scientificSymbol,const Card& card);
	Building(Building&& other) noexcept;
	Building& operator=(const Building& other);
	Building& operator=(Building&& other) noexcept;
	~Building() = default;

	void swap(Building& other) noexcept;

	Age getAge() const;
	Color getColor() const;
	std::vector<ResourceType> getResources() const;
	std::optional<ScientificSymbol> getScientificSymbol() const;


private:
	Age m_age;
	Color m_color;
	std::vector<ResourceType> m_resources;
	std::optional<ScientificSymbol> m_scientificSymbol;

};


