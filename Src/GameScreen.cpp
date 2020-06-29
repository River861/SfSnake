#include <SFML/Graphics.hpp>

#include <random>
#include <memory>
#include <algorithm>
#include <vector>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"
#include "Snake.h"
#include "Resource.h"
#include "Grid.h"
#include "Setting.h"

using namespace sfSnake;

const int GameScreen::FruitNum = 5;

GameScreen::GameScreen() : snake_()
{
	Grid::setColor(Resource::getColor(Setting::Settings["Grid"]));
}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	snake_.handleInput(window);
}

void GameScreen::update(sf::Time delta)
{
	if (fruit_.size() < FruitNum)
		generateFruit();

	snake_.update(delta);  // 蛇移动+冲突检测
	snake_.checkFruitCollisions(fruit_);  // 吃水果检查

	if (snake_.hitSelf())
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize() - Snake::InitialSize);
}

void GameScreen::render(sf::RenderWindow& window)
{
	window.clear(Resource::getColor(Setting::Settings["Background"]));  // 在这里清屏 改背景颜色
	window.draw(Grid::getInstance());
	snake_.render(window);

	for (auto& fruit : fruit_)
		fruit.render(window);
}

void GameScreen::generateFruit()
{
	static std::default_random_engine engine(time(NULL));

	static std::uniform_real_distribution<float> xDistribution(0.f + Fruit::Radius, Game::Width - Fruit::Radius);
	static std::uniform_real_distribution<float> yDistribution(0.f + Fruit::Radius, Game::Height - Fruit::Radius);
	static std::uniform_real_distribution<float> colorDistribution(0.f, 1.f);
	static std::uniform_real_distribution<float> angleDistribution(0.f, 360.f);

	fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)),
						   colorDistribution(engine),
						   angleDistribution(engine)));
}

