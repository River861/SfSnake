#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>

namespace sfSnake
{

class Resource
{
public:
    static Resource& getInstance();  // 单例模式

    static sf::Texture& getTexture(const std::string& fileName);
    static sf::Font& getFont(const std::string& fileName);
    static sf::SoundBuffer& getSoundBuffer(const std::string& fileName);

    static const sf::Color& getColor(const std::string& objectName);
    static sf::Texture& getSnakeBody(const std::string& snakeName);
    static void switchToMusic(const std::string& fileName);

private:
    Resource();
    static sf::Texture drawSnakeBody(const sf::Color& topColor, const sf::Color& bottomColor);
    static sf::Music::TimeSpan& getMusicLoopPoints(const std::string& fileName);

    std::map<std::string, sf::Texture> textures_;
    std::map<std::string, sf::Font> fonts_;
    std::map<std::string, sf::SoundBuffer> soundBuffers_;
    
    sf::Music bgMusic_;
};

}