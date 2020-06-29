#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{

class SnakeBodyNode : public sf::CircleShape  // 用继承方式简化代码
{
public:
	SnakeBodyNode(sf::Vector2f position = sf::Vector2f(), float angle = 0.f);

	sf::FloatRect getBounds() const;

	void render(sf::RenderWindow& window);
	static const float Radius;
};

class SnakeHeadNode : public sf::Sprite
{
public:
	SnakeHeadNode(sf::Vector2f position = sf::Vector2f(), float angle = 0.f);

	sf::FloatRect getBounds() const;

	void render(sf::RenderWindow& window);

private:
	static const float Scale;
};

}

#endif