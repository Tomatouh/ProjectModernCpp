#include <SFML/Graphics.hpp>
module displayCard;
bool displayCard::isFaceUp() const
{
	return m_isFaceUp;
}
void displayCard::setFaceUp(bool isFaceUp)
{
	m_isFaceUp = isFaceUp;
}
void displayCard::setBuilding(const std::shared_ptr<Building>& building)
{
	m_building = building;
}
std::shared_ptr<Building> displayCard::getBuilding() const
{
	return m_building;
}
guiCard displayCard::getGuiCard() const
{
	guiCard g(std::static_pointer_cast<Card>(m_building));
	g.setPosition(m_position);
	g.setHighlighted(m_isSelected);
	return guiCard(std::static_pointer_cast<Card>(m_building));
}
void displayCard::setPosition(std::pair<int, int> pos)
{
	m_position = pos;
}
const std::pair<int, int>& displayCard::getPosition() const
{
	return m_position;
}

void displayCard::setSelected(bool isSelected)
{
	m_isSelected = isSelected;
}

bool displayCard::isSelected() const
{
	return m_isSelected;
}

bool displayCard::containsPoint(const sf::Vector2i& point) const
{
	const int x = m_position.first;
	const int y = m_position.second;
	const int w = 160;
	const int h = 170;
	return (point.x >= x && point.x <= x + w && point.y >= y && point.y <= y + h);
}
