#include <SFML/Graphics.hpp>
export module choiceBox;

export class ChoiceBox : public sf::Drawable {
private:
	const static sf::Font font;
	sf::RectangleShape box;
	sf::Text text;
	std::array<sf::RectangleShape, 3> optionBoxes;

public:
	ChoiceBox();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setPosition(std::pair<int, int> coords);
	void drawOptions(sf::RenderWindow& window);
		

};

export class ChoiceBoxSizes {
	public:
	static constexpr float boxWidth = 500.0f;
	static constexpr float boxHeight = 50.0f;
	static constexpr int fontSize = 20;
};


