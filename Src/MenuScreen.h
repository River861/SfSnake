#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Screen.h"
#include "Button.h"

namespace sfSnake
{

class Title : public Button
{
public:
	Title();
	Title(const std::string& text, const sf::Vector2f& position);
};

class MenuScreen : public Screen
{
public:
	MenuScreen();

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

private:
	Title title_;
	std::vector<Button> buttons_;
};

}

#endif