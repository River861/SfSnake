#include <SFML/Graphics.hpp>

#include "Button.h"
#include "Resource.h"

using namespace sfSnake;

Button::Button() {}

Button::Button(const std::string& text, const sf::Vector2f& position)
{
	setFont(Resource::getFont("Fonts/menu_font.ttf"));
	setString(text);
	sf::FloatRect textBounds = getLocalBounds();
	setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
	setPosition(position);
}

bool Button::isHover(sf::RenderWindow& window)
{
	sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Vector2f curWinSize = static_cast<sf::Vector2f>(window.getSize());
	mousePosition.x /= curWinSize.x / Game::Width;
	mousePosition.y /= curWinSize.y / Game::Height;

	return getGlobalBounds().contains(mousePosition);
}