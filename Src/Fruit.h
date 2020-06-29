#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

namespace sfSnake
{

class FruitType
{
public:
	FruitType(const std::string& type, int point, float threshold);

public:
	std::string type;
	int point;
	float threshold;  // 用于颜色抽样的分布阈值
};


class Fruit : sf::Sprite
{
public:
	Fruit(sf::Vector2f position, float type_val, float angle);

	sf::FloatRect getBounds() const;
	int getPoint() const;

	void render(sf::RenderWindow& window);
	static const float Radius;

private:
	int point_;

	static std::vector<FruitType> FruitTypes;
};

}

#endif