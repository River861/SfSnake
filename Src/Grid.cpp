#include <SFML/Graphics.hpp>

#include "Grid.h"
#include "Game.h"

using namespace sfSnake;

Grid& Grid::getInstance()
{
    static Grid instance_;
    return instance_;
}

Grid::Grid()
{
    for(float y = distance_; y < Game::Height; y += distance_)
    {
        vertices_.push_back(sf::Vertex(sf::Vector2f(0, y)));
        vertices_.push_back(sf::Vertex(sf::Vector2f(Game::Width, y)));
    }
    for(float x = distance_; x < Game::Width; x += distance_)
    {
        vertices_.push_back(sf::Vertex(sf::Vector2f(x, 0)));
        vertices_.push_back(sf::Vertex(sf::Vector2f(x, Game::Height)));
    }
}

void Grid::setColor(const sf::Color& color)
{
    auto& vertices = getInstance().vertices_;

    for(auto& vertex : vertices)
    {
        vertex.color = color;
    }
}
