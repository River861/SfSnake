#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "SnakeNode.h"
#include "Fruit.h"

namespace sfSnake
{

using Direction = sf::Vector2f;

class Snake
{
public:
	Snake();

	void handleInput(sf::RenderWindow& window);
	void update(sf::Time delta);
	void render(sf::RenderWindow& window);

	void checkFruitCollisions(std::vector<Fruit>& fruits);

	bool hitSelf() const;
	unsigned getSize() const;

	static const int InitialSize;

private:
	void move();
	void grow(int num);
	void checkEdgeCollisions();
	void checkSelfCollisions();
	void initNodes();

	bool hitSelf_;

	sf::Vector2f position_;
	Direction direction_;

	sf::Sound pickupSound_;
	sf::Sound dieSound_;

	SnakeHeadNode head_;
	std::vector<SnakeBodyNode> nodes_;

	static const float MoveScale;  // 移动的距离占直径的比例
};

bool nodeIntersect(const sf::Vector2f& a, const sf::Vector2f& b);

}

#endif