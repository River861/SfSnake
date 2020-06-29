#include <SFML/Graphics.hpp>

#include "SnakeNode.h"
#include "Resource.h"
#include "Setting.h"

using namespace sfSnake;

const float SnakeBodyNode::Radius = 12.f;
const float SnakeHeadNode::Scale = 0.57f;

SnakeBodyNode::SnakeBodyNode(sf::Vector2f position, float angle)
{
	setTexture(&Resource::getSnakeBody(Setting::Settings["SnakeType"]));
	setOrigin(Radius, Radius);

	setRadius(Radius);
	setPosition(position);
	setRotation(angle);
}

sf::FloatRect SnakeBodyNode::getBounds() const
{
	return getGlobalBounds();
}

void SnakeBodyNode::render(sf::RenderWindow& window)
{
	window.draw(*this);
}


SnakeHeadNode::SnakeHeadNode(sf::Vector2f position, float angle)
{
	setTexture(Resource::getTexture("Images/Snake/" + Setting::Settings["SnakeType"] + ".png"));
	sf::FloatRect bbox = getGlobalBounds();
	setOrigin(bbox.width / 2, bbox.height / 2);

	setScale(Scale, Scale);
	setPosition(position);
	setRotation(angle);
}

sf::FloatRect SnakeHeadNode::getBounds() const
{
	return getGlobalBounds();
}

void SnakeHeadNode::render(sf::RenderWindow& window)
{
	window.draw(*this);
}
