export module Building;
import card;

namespace SevenWonders {
	class Building : Card{
	public:
		enum class Age {
			ageI,
			ageII,
			ageIII,
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
	private:
		Age m_age;
		Color m_color;
		Building* m_link;
	};
}