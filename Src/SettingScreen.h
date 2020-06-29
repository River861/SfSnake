#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Screen.h"
#include "Setting.h"
#include "Button.h"

namespace sfSnake
{

class SettingScreen : public Screen
{
public:
	SettingScreen();

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

private:
	void commit();

	std::vector<Setting> settings_;
	std::vector<Button> buttons_;
};

}