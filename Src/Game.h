#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>

#include "Screen.h"

namespace sfSnake
{

class Game
{
public:
	Game();

	void run();

	void handleInput();
	void update(sf::Time delta);
	void render();

	static const int Width = 800;
	static const int Height = 500;

	static std::shared_ptr<Screen> Screen;  // 静态公共变量 改变==界面切换

private:
	sf::RenderWindow window_;
	
	static const sf::Time TimePerFrame;
};

}


#endif