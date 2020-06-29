#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>

#include "Game.h"
#include "GameScreen.h"
#include "MenuScreen.h"
#include "GameOverScreen.h"
#include "Resource.h"

using namespace sfSnake;

GameOverScreen::GameOverScreen(int score) : score_(score)
{
	text_ = sf::Text("Your score: " + std::to_string(score) + "!",
					 Resource::getFont("Fonts/menu_font.ttf"),
					 90);
	text_.setFillColor(sf::Color::Red);

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
	text_.setPosition((float) Game::Width / 2, (float) Game::Height * 2 / 5);

	buttons_ = std::vector<Button>
	{
		Button("Retry"  , sf::Vector2f((float)Game::Width / 4    , (float)Game::Height * 3 / 4)),
		Button("Go home", sf::Vector2f((float)Game::Width / 2    , (float)Game::Height * 3 / 4)),
		Button("Quit"   , sf::Vector2f((float)Game::Width * 3 / 4, (float)Game::Height * 3 / 4))
	};
}

void GameOverScreen::handleInput(sf::RenderWindow& window)
{
	for (auto& button : buttons_) button.setFillColor(sf::Color::White);

	for (auto& button : buttons_)
	{
		if (button.isHover(window))
		{
			button.setFillColor(sf::Color::Blue);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				auto& name = button.getString();
				if (name == "Retry") Game::Screen = std::make_shared<GameScreen>();
				else if (name == "Go home") Game::Screen = std::make_shared<MenuScreen>();
				else if (name == "Quit") window.close();
			}
			break;
		}
	}
}

void GameOverScreen::update(sf::Time delta) {}

void GameOverScreen::render(sf::RenderWindow& window)
{
	window.draw(text_);
	for (auto& button : buttons_) window.draw(button);
}