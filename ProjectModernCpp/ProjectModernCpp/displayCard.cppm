#include <SFML/Graphics.hpp>
export module displayCard;
import std;
import Building;
import guiCard;
export class displayCard {
private:
	std::shared_ptr<Building> m_building;
	bool m_isFaceUp;
	std::pair<int, int> m_position{ 0,0 };
	bool m_isSelected{ false };

public:
	displayCard() {};
	bool isFaceUp() const;
	std::shared_ptr<Building> getBuilding() const;
	void setFaceUp(bool isFaceUp);
	void setBuilding(const std::shared_ptr<Building>& building);
	guiCard getGuiCard() const;

	void setPosition(std::pair<int, int> pos);
	const std::pair<int, int>& getPosition() const;
	void setSelected(bool isSelected);
	bool isSelected() const;
	bool containsPoint(const sf::Vector2i& point, const sf::RenderWindow& window) const;
};