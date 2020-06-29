#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>

#include "Setting.h"
#include "Resource.h"
#include "Game.h"

using namespace sfSnake;

std::map<std::string, std::string> Setting::Settings
{
	{"SnakeType", "Devil"},
	{"Background", "White"},
	{"Grid", "Black"},
	{"Music", "Cute"}
};


Setting::Setting(const std::string& name, const std::vector<std::string>& options, float y)
: option_num_{static_cast<int>(options.size())}
{
	name_ = sf::Text(name, Resource::getFont("Fonts/title_font.ttf"), 50);
	name_.setFillColor(sf::Color::Green);
	name_.setStyle(sf::Text::Bold);

	sf::FloatRect textBounds = name_.getLocalBounds();
	name_.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
	name_.setPosition(Game::Width / 4, y);

	button_pair_ = std::vector<Button>
	{
		Button("<"  , sf::Vector2f((float)Game::Width / 2     , y)),
		Button(">"  , sf::Vector2f((float)Game::Width * 9 / 10, y))
	};

	for(auto& option : options)
	{
		options_.push_back(sf::Text(option, Resource::getFont("Fonts/menu_font.ttf")));
		auto& cur = options_.back();
		sf::FloatRect textBounds = cur.getLocalBounds();
		cur.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
		cur.setPosition(Game::Width * 7 / 10, y);
	}

	cur_chosen_ = find(options.begin(), options.end(), Settings[name]) - options.begin();
}

void Setting::handleInput(sf::RenderWindow& window)
{
	name_.setFillColor(sf::Color::Green);
	for (auto& button : button_pair_) button.setFillColor(sf::Color::White);

	for (auto& button : button_pair_)
	{
		if (button.isHover(window))
		{
			button.setFillColor(sf::Color::Blue);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				auto& name = button.getString();
				if (name == "<") cur_chosen_ = (cur_chosen_ - 1 + option_num_) % option_num_;
				else if (name == ">") cur_chosen_ = (cur_chosen_ + 1) % option_num_;
			}
			break;
		}
	}
}

void Setting::render(sf::RenderWindow& window)
{
    window.draw(name_);
    for (auto& arrow : button_pair_) window.draw(arrow);
    window.draw(options_.at(cur_chosen_));
}

void Setting::commit()
{
	auto& name = name_.getString();
	auto& chosen = options_.at(cur_chosen_).getString();
	if (Settings.find(name) != Settings.end()) Settings[name] = chosen;

	// 音乐在确认后生效
	if (name == "Music") Resource::switchToMusic(Settings["Music"]);
}
