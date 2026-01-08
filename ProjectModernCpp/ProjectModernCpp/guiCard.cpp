#include <SFML/Graphics.hpp>
module guiCard;




guiCard::guiCard(std::shared_ptr<Card> fromCard) :text(font, "", BoxSizes::fontSize)
{
	box.setSize(sf::Vector2f(BoxSizes::boxWidth, BoxSizes::boxHeight));
	box.setFillColor(sf::Color::White);
	box.setOutlineColor(sf::Color::Black);
	box.setOutlineThickness(2.f);
	text.setFillColor(sf::Color::Black);
}
guiCard::guiCard() :text(font, "", BoxSizes::fontSize)
{
	box.setSize(sf::Vector2f(BoxSizes::boxWidth, BoxSizes::boxHeight));
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


	sf::Vector2f textPosition(coords.first+((BoxSizes::boxWidth-text.getString().getSize()*BoxSizes::fontSize*0.6)/2), coords.second);
	text.setPosition(textPosition);
}

void guiCard::setText(const std::string_view& newText)
{
	text.setString(newText.data());
}
void guiCard::setSize(const sf::Vector2f& newSize)
{
	box.setSize(newSize);
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
void guiCard::setTexture(const sf::Texture& texture)
{
	box.setTexture(&texture);
}
const sf::Font guiCard::font = []() {
	sf::Font font("C:\\Windows\\Fonts\\cour.ttf");
	return font;
	}();
