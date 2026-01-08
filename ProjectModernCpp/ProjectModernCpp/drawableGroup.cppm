#include <SFML/Graphics.hpp>
export module drawableGroup;
export class DrawableGroup : public sf::Drawable {
private:
	std::vector<std::shared_ptr<sf::Drawable>> m_drawables;
public:
	void addDrawable(std::shared_ptr<sf::Drawable> drawable);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	DrawableGroup() = default;
};