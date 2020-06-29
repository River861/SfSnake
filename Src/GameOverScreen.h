#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Screen.h"
#include "Button.h"

namespace sfSnake
{
class GameOverScreen : public Screen
{
public:
	GameOverScreen(int score);

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

private:
	int score_;

	sf::Text text_;
	std::vector<Button> buttons_;
};
}

#endif