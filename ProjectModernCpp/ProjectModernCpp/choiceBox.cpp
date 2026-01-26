#include <SFML/Graphics.hpp>
module choiceBox;

ChoiceBox::ChoiceBox() :text(font, "", ChoiceBoxSizes::fontSize)
{
	box.setSize(sf::Vector2f(ChoiceBoxSizes::boxWidth, ChoiceBoxSizes::boxHeight));
	box.setFillColor(sf::Color(200, 200, 200, 220));
	box.setOutlineColor(sf::Color::Black);
	box.setOutlineThickness(2.f);

	for(auto & optionBox : optionBoxes)
	{
		optionBox.setSize(sf::Vector2f(ChoiceBoxSizes::optionBoxWidth, ChoiceBoxSizes::optionBoxHeight));
		optionBox.setOutlineColor(sf::Color::Black);
		optionBox.setOutlineThickness(2.f);
	}
	optionBoxes[0].setFillColor(sf::Color(150, 75, 0));
	optionBoxes[1].setFillColor(sf::Color(200, 200, 0));
	optionBoxes[2].setFillColor(sf::Color::Magenta);

	text.setFillColor(sf::Color::Black);
}

void ChoiceBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(box, states);
	target.draw(text, states);
}

void ChoiceBox::setPosition(std::pair<int, int> coords)
{
	sf::Vector2f boxPosition(coords.first, coords.second);
	box.setPosition(boxPosition);
}
void ChoiceBox::drawOptions(sf::RenderWindow& window)
{
	float startX = box.getPosition().x + 5.f;
	float startY = box.getPosition().y + 5.f;

	for (size_t i = 0; i < optionBoxes.size(); ++i)
	{
		const std::string label(i == 0 ? "Build" : (i == 1 ? "Sell" : "Wonder"));
		sf::Vector2f optionPosition(startX + i * (ChoiceBoxSizes::boxWidth/3), startY);
		optionBoxes[i].setPosition(optionPosition);
		window.draw(optionBoxes[i]);

		text.setString(label);
		const sf::FloatRect tb = text.getLocalBounds();
		const float textX = optionPosition.x + (ChoiceBoxSizes::optionBoxWidth - tb.size.x) / 2.f - tb.position.x;
		const float textY = optionPosition.y + (ChoiceBoxSizes::optionBoxHeight - tb.size.y) / 2.f - tb.position.y;
		text.setPosition(sf::Vector2f(textX, textY));
		window.draw(text);
	}
}
const sf::Font ChoiceBox::font = []() {
	sf::Font font("C:\\Windows\\Fonts\\cour.ttf");
	return font;
	}();
