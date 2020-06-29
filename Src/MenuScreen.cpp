#include <SFML/Graphics.hpp>

#include <memory>

#include "GameScreen.h"
#include "MenuScreen.h"
#include "SettingScreen.h"
#include "Game.h"
#include "Resource.h"

using namespace sfSnake;

Title::Title() {}

Title::Title(const std::string& text, const sf::Vector2f& position)
{
	setFont(Resource::getFont("Fonts/title_font.ttf"));
	setString(text);
	setFillColor(sf::Color::Green);
	setCharacterSize(160);
	setStyle(sf::Text::Bold);

	sf::FloatRect textBounds = getLocalBounds();
	setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
	setPosition(position);
}

MenuScreen::MenuScreen()
{
	title_ = Title("SNAKE!", sf::Vector2f((float)Game::Width / 2, (float)Game::Height / 4));

	buttons_ = std::vector<Button>
	{
		Button("Play"   , sf::Vector2f((float)Game::Width / 2, (float)Game::Height * 3  / 5 )),
		Button("Setting", sf::Vector2f((float)Game::Width / 2, (float)Game::Height * 11 / 15)),
		Button("Quit"   , sf::Vector2f((float)Game::Width / 2, (float)Game::Height * 13 / 15))
	};
}

void MenuScreen::handleInput(sf::RenderWindow& window)
{
	title_.setFillColor(sf::Color::Green);
	for (auto& button : buttons_) button.setFillColor(sf::Color::White);

	if (title_.isHover(window))
	{
		title_.setFillColor(sf::Color::Red);
	}
	else for (auto& button : buttons_)
	{
		if (button.isHover(window))
		{
			button.setFillColor(sf::Color::Blue);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				auto& name = button.getString();
				if (name == "Play") Game::Screen = std::make_shared<GameScreen>();
				else if (name == "Setting") Game::Screen = std::make_shared<SettingScreen>();
				else if (name == "Quit") window.close();
			}
			break;
		}
	}
}

void MenuScreen::update(sf::Time delta)
{
	static bool movingLeft = false;
	static bool movingRight = true;

	if (movingRight)
	{
		title_.rotate(delta.asSeconds());
		if (static_cast<int>(title_.getRotation()) == 10)
		{
			movingRight = false;
			movingLeft = true;
		}
	}
	if (movingLeft)
	{
		title_.rotate(-delta.asSeconds());
		if (static_cast<int>(title_.getRotation()) == (360 - 10))
		{
			movingLeft = false;
			movingRight = true;
		}
	}
}

void MenuScreen::render(sf::RenderWindow& window)
{
	window.draw(title_);
	for (auto& button : buttons_) window.draw(button);
}