#include <SFML/Graphics.hpp>
module guiCard;
guiCard::guiCard(std::shared_ptr<Card> fromCard):text(font, fromCard->getName(),20)
{
	box.setSize(sf::Vector2f(160.0f, 170.0f));
	box.setFillColor(sf::Color::White);
	box.setOutlineColor(sf::Color::Black);
	box.setOutlineThickness(2.f);
	text.setFillColor(sf::Color::Black);
}
guiCard::guiCard() :text(font, "", 20)
{
	box.setSize(sf::Vector2f(160.0f, 170.0f));
	box.setFillColor(sf::Color::White);
	box.setOutlineColor(sf::Color::Black);
	box.setOutlineThickness(2.f);
	text.setFillColor(sf::Color::Black);
}
void guiCard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(box, states);
	target.draw(text, states);
}

void guiCard::setPosition(std::pair<int, int> coords)
{
	sf::Vector2f boxPosition(coords.first, coords.second);
	box.setPosition(boxPosition);


	sf::Vector2f textPosition(coords.first+((160-text.getString().getSize()*12)/2), coords.second);
	text.setPosition(textPosition);
}

void guiCard::setText(const std::string_view& newText)
{
	text.setString(newText.data());
}
void guiCard::setHighlighted(bool highlight)
{
	isHighlighted = highlight;
	if (isHighlighted)
	{
		box.setOutlineColor(sf::Color::Red);
		box.setOutlineThickness(4.f);
	}
	else
	{
		box.setOutlineColor(sf::Color::Black);
		box.setOutlineThickness(2.f);
	}
}
bool guiCard::getHighlighted() const
{
	return isHighlighted;
}
const sf::Font guiCard::font = []() {
	sf::Font font("C:\\Windows\\Fonts\\cour.ttf");
	return font;
	}();
