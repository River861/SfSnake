#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace sfSnake
{

class Grid : public sf::Drawable, public sf::Transformable
{
public:
    static Grid& getInstance();  // 单例模式

    static void setColor(const sf::Color& color);

private:
    Grid();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(&vertices_[0], vertices_.size(), sf::Lines, states);
    }

    std::vector<sf::Vertex> vertices_;
    float distance_ = 30.f;
};

}
