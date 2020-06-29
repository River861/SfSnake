#include <SFML/Graphics.hpp>

#include "Fruit.h"
#include "Resource.h"

using namespace sfSnake;

FruitType::FruitType(const std::string& type, int point, float threshold)
: type(type), point{point}, threshold{threshold}
{
}


const float Fruit::Radius = 15.f;
std::vector<FruitType> Fruit::FruitTypes
{
	FruitType("stone"      , 0, 0.125f),
	FruitType("mushroom"   , 0, 0.25f ),
	FruitType("straw_berry", 3, 0.5f  ),
	FruitType("blue_berry" , 2, 0.75f ),
	FruitType("kiwi"       , 1, 1.f   )
};

Fruit::Fruit(sf::Vector2f position, float type_val, float angle)
{
	// 找落入分布的范围来决定水果颜色
	auto type_iter = std::lower_bound(FruitTypes.begin(), FruitTypes.end(), type_val,
		[](const FruitType& lhs, float rhs) {
			return lhs.threshold < rhs;
		}
	);

	point_ = type_iter -> point;
	setTexture(Resource::getTexture("Images/Fruit/" + type_iter -> type + ".png"));
	sf::FloatRect bbox = getGlobalBounds();
	setOrigin(bbox.width / 2, bbox.height / 2);

	float scale_ = Radius * 2 / std::max(bbox.width, bbox.height);
	setScale(scale_, scale_);
	setPosition(position);
	setRotation(angle);
}

void Fruit::render(sf::RenderWindow& window)
{
	window.draw(*this);
}

sf::FloatRect Fruit::getBounds() const
{
	return getGlobalBounds();
}

int Fruit::getPoint() const {
	return point_;
}