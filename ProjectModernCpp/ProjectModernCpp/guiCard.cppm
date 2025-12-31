#include <SFML/Graphics.hpp>
export module guiCard;
import std;
import card;
import Building;
export class guiCard : public sf::Drawable {
private:
	const static sf::Font font;
	sf::RectangleShape box;
	sf::Text text;
public:
	guiCard(std::shared_ptr<Card> fromCard);
	guiCard();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setPosition(std::pair<int,int> coords);

};