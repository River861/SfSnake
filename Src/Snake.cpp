#include <SFML/Graphics.hpp>

#include <memory>
#include <cmath>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"
#include "Resource.h"

using namespace sfSnake;

const int Snake::InitialSize = 4;
const float Snake::MoveScale = 0.8f;


Snake::Snake() : hitSelf_(false), direction_(Direction(0.f, -1.f))
{
	initNodes();

	pickupSound_.setBuffer(Resource::getSoundBuffer("Sounds/pickup.wav"));
	pickupSound_.setVolume(30);

	dieSound_.setBuffer(Resource::getSoundBuffer("Sounds/die.wav"));
	dieSound_.setVolume(50);
}

void Snake::initNodes()
{
	float center_X = (float) Game::Width / 2 - SnakeBodyNode::Radius;
	float center_Y = (float) Game::Height / 2 - SnakeBodyNode::Radius;
	head_.setPosition(center_X, center_Y);
	for (int i = 1; i <= Snake::InitialSize; ++ i)
	{
		nodes_.push_back(SnakeBodyNode(sf::Vector2f(
			center_X,
			center_Y + (SnakeBodyNode::Radius * 2 * i * Snake::MoveScale))));
	}
}

void Snake::handleInput(sf::RenderWindow& window)  // 蛇移动
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
		sf::Vector2f curWinSize = static_cast<sf::Vector2f>(window.getSize());
		
		mousePosition.x /= curWinSize.x / Game::Width;  // 修复窗口放大鼠标定位与蛇不匹配的bug
		mousePosition.y /= curWinSize.y / Game::Height;

		direction_ = mousePosition - head_.getPosition();
		direction_ /= hypotf(direction_.x, direction_.y);
	}
}

void Snake::update(sf::Time delta)
{
	move();  // 控制移动
	checkEdgeCollisions();  // 碰墙处理
	checkSelfCollisions();  // 碰身体处理
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
	decltype(fruits.begin()) toRemove = fruits.end();

	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
		if (it->getBounds().intersects(head_.getBounds()))
			toRemove = it;
	}

	if (toRemove != fruits.end())
	{
		pickupSound_.play();
		grow(toRemove->getPoint());
		fruits.erase(toRemove);
	}
}

void Snake::grow(int num)
{
	SnakeBodyNode& tailNode = nodes_[nodes_.size() - 1];
	while(num --)
	{
		nodes_.push_back(SnakeBodyNode(tailNode.getPosition(), tailNode.getRotation()));
	}
}

unsigned Snake::getSize() const
{
	return nodes_.size();
}

bool Snake::hitSelf() const
{
	return hitSelf_;
}

void Snake::checkSelfCollisions()
{
	for (decltype(nodes_.size()) i = 0; i < nodes_.size(); ++i)
	{
		if (nodeIntersect(head_.getPosition(), nodes_[i].getPosition()))
		{
			dieSound_.play();
			sf::sleep(sf::seconds(Resource::getSoundBuffer("Sounds/die.wav").getDuration().asSeconds()));  // 先暂停让音乐播完
			hitSelf_ = true;
			break;
		}
	}
}

void Snake::checkEdgeCollisions()  // 实现穿墙
{
	if (head_.getPosition().x <= 0)
		head_.setPosition(Game::Width, head_.getPosition().y);
	else if (head_.getPosition().x >= Game::Width)
		head_.setPosition(0, head_.getPosition().y);
	else if (head_.getPosition().y <= 0)
		head_.setPosition(head_.getPosition().x, Game::Height);
	else if (head_.getPosition().y >= Game::Height)
		head_.setPosition(head_.getPosition().x, 0);
}

void Snake::move()
{
	static const float PI = acosf(-1.f);

	for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
	{
		nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
		nodes_[i].setRotation(nodes_.at(i - 1).getRotation());
	}
	nodes_[0].setPosition(head_.getPosition());
	nodes_[0].setRotation(head_.getRotation());

	head_.move(direction_.x * SnakeBodyNode::Radius * 2 * Snake::MoveScale,
				   direction_.y * SnakeBodyNode::Radius * 2 * Snake::MoveScale);
	head_.setRotation(fmodf(atan2f(direction_.x, -direction_.y) / PI * 180.f + 360.f, 360.f));
}

void Snake::render(sf::RenderWindow& window)
{
	for (auto& node : nodes_)
		node.render(window);
	head_.render(window);
}

bool sfSnake::nodeIntersect(const sf::Vector2f& a, const sf::Vector2f& b)
{
	auto position_diff = a - b;
	auto dist = hypotf(position_diff.x, position_diff.y);
	return dist < SnakeBodyNode::Radius;
}
