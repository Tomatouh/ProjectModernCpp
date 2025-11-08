export module Building;
import card;
import std;

namespace SevenWonders {
	class Building : Card{
	public:
		enum class Age {
			AGEI,
			AGEII,
			AGEII,
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



	private:
		Age m_age;
		Color m_color;
		std::optional<Card> m_link;
		std::uint8_t m_wood;
		std::uint8_t m_clay;
		std::uint8_t m_stone;
		std::uint8_t m_glass;
		std::uint8_t m_papyrus;
		std::uint8_t m_victoryPoints;
		std::uint8_t m_shields;
		std::uint8_t m_coins;
		ScientificSymbol m_scientificSymbol;
		
	};
}