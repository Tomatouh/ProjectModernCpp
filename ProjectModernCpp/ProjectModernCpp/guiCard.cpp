#include <SFML/Graphics.hpp>
module guiCard;
guiCard::guiCard(std::shared_ptr<Card> fromCard):text(font, fromCard->getName(),20)
{
	box.setSize(sf::Vector2f(100.0f, 150.0f));
	box.setFillColor(sf::Color::White);
	box.setOutlineColor(sf::Color::Black);
	box.setOutlineThickness(2.f);
	text.setFillColor(sf::Color::Green);
}
guiCard::guiCard() :text(font, "", 20)
{
	box.setSize(sf::Vector2f(100.0f, 150.0f));
	box.setFillColor(sf::Color::White);
	box.setOutlineColor(sf::Color::Black);
	box.setOutlineThickness(2.f);
	text.setFillColor(sf::Color::Green);
}
void guiCard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(box, states);
	target.draw(text, states);
}

void guiCard::setPosition(std::pair<int, int> coords)
{
	sf::Vector2f position(static_cast<float>(coords.first), static_cast<float>(coords.second));
	box.setPosition(position);
	text.setPosition(position);
}
const sf::Font guiCard::font = []() {
	sf::Font font("C:\\Windows\\Fonts\\arial.ttf");
	return font;
	}();