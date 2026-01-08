#include <SFML/Graphics.hpp>
module drawableGroup;

void DrawableGroup::addDrawable(std::shared_ptr<sf::Drawable> drawable)
{
	m_drawables.push_back(drawable);
}
void DrawableGroup::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& drawable : m_drawables)
	{
		target.draw(*drawable, states);
	}
}