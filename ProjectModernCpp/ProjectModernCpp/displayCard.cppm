export module displayCard;
import std;
import Building;
export class displayCard {
private:
	std::shared_ptr<Building> m_building;
	bool m_isFaceUp;
public:
	displayCard() {};
	bool isFaceUp() const;
	std::shared_ptr<Building> getBuilding() const;
	void setFaceUp(bool isFaceUp);
	void setBuilding(const std::shared_ptr<Building>& building);
};