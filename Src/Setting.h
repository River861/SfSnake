#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>

#include "Button.h"

namespace sfSnake
{

class Setting
{
public:
	Setting(const std::string& name, const std::vector<std::string>& options, float y);

	void handleInput(sf::RenderWindow& window);
	void render(sf::RenderWindow& window);

	void commit();

	// 当前设定表
	static std::map<std::string, std::string> Settings;

private:
	sf::Text name_;
	std::vector<Button> button_pair_;
	std::vector<sf::Text> options_;

	int cur_chosen_{};
	int option_num_;
};

}