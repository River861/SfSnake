#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "Game.h"

namespace sfSnake
{

class Button : public sf::Text
{
public:
	Button();
	Button(const std::string& text, const sf::Vector2f& position);
	bool isHover(sf::RenderWindow& window);
};

}