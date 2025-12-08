module displayCard;
bool displayCard::isFaceUp() const
{
	return m_isFaceUp;
}
void displayCard::flip()
{
	m_isFaceUp = !m_isFaceUp;
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