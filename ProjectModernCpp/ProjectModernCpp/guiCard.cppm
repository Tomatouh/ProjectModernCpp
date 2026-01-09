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
	bool isHighlighted{ false };
	std::shared_ptr<sf::Texture> m_texture;
public:
	
	guiCard(std::shared_ptr<Card> fromCard);
	guiCard();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setPosition(std::pair<int,int> coords);
	void setText(const std::string_view& newText);
	
	void setSize(const sf::Vector2f& newSize);

	void setTexture(const sf::Texture& texture);

	void setHighlighted(bool highlight);
	bool getHighlighted() const;

};
export class BoxSizes {
public:
	static constexpr float boxWidth = 80.0f;
	static constexpr float boxHeight = 125.0f;
	static constexpr int fontSize = 15;
};