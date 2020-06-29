#include <iostream>

#include "Resource.h"
#include "SnakeNode.h"

using namespace sfSnake;

Resource& Resource::getInstance()
{
    static Resource instance_;
    return instance_;
}

Resource::Resource() {}

sf::Texture& Resource::getTexture(const std::string& fileName)
{
    auto& texMap = getInstance().textures_;

    auto iter = texMap.find(fileName);
    if (iter == texMap.end())  // 若缓存资源中没有该图片, 则load该图
    {
        auto& texture = texMap[fileName];
        if(!texture.loadFromFile(fileName))
        {
            std::cerr << "load " << fileName << " fail." << std::endl;
        }
        texture.setSmooth(true);
        return texture;
    }

    return iter -> second;
}

sf::Font& Resource::getFont(const std::string& fileName)
{
    auto& fontMap = getInstance().fonts_;

    auto iter = fontMap.find(fileName);
    if (iter == fontMap.end())  // 若缓存资源中没有该字体, 则load该图
    {
        auto& font = fontMap[fileName];
        if(!font.loadFromFile(fileName))
        {
            std::cerr << "load " << fileName << " fail." << std::endl;
        }
        return font;
    }

    return iter -> second;
}

sf::SoundBuffer& Resource::getSoundBuffer(const std::string& fileName)
{
    auto& soundMap = getInstance().soundBuffers_;

    auto iter = soundMap.find(fileName);
    if (iter == soundMap.end())  // 若缓存资源中没有该音效, 则load该音效
    {
        auto& soundBuffer = soundMap[fileName];
        if(!soundBuffer.loadFromFile(fileName))
        {
            std::cerr << "load " << fileName << " fail." << std::endl;
        }
        return soundBuffer;
    }

    return iter -> second;
}

const sf::Color& Resource::getColor(const std::string& objectName)
{
    static std::map<std::string, sf::Color> colMap_ = {  // 颜色管理
        {"White",     sf::Color(235, 237, 244)},
        {"Black",     sf::Color(43 , 43 , 43 )},
        {"Brown",     sf::Color(199, 132, 64 )},

        {"snake_yellow", sf::Color(251, 201, 62 )},
        {"snake_black",  sf::Color(80 , 80 , 69 )},
        {"snake_red",    sf::Color(244, 68 , 68 )},
        {"snake_white",  sf::Color(251, 251, 251)},
        {"snake_purple", sf::Color(167, 98 , 230)}
    };

    auto iter = colMap_.find(objectName);
    return iter == colMap_.end() ? sf::Color::White : iter -> second;
}

sf::Texture& Resource::getSnakeBody(const std::string& snakeName)
{
    static std::map<std::string, sf::Texture> bodyMap_ = {  // 蛇身管理
        {"Devil"  , drawSnakeBody(getColor("snake_black"), getColor("snake_red"   ))},
        {"Fool"   , drawSnakeBody(getColor("snake_black"), getColor("snake_yellow"))},
        {"Alien"  , drawSnakeBody(getColor("snake_white"), getColor("snake_purple"))},
        {"Penguin", drawSnakeBody(getColor("snake_white"), getColor("snake_black" ))}
    };
    static sf::Texture empty_ = sf::Texture();

    auto iter = bodyMap_.find(snakeName);
    return iter == bodyMap_.end() ? empty_ : iter -> second;
}

sf::Texture Resource::drawSnakeBody(const sf::Color& topColor, const sf::Color& bottomColor)
{
    sf::Image bg_img, front_img;
    bg_img.create(SnakeBodyNode::Radius * 2, SnakeBodyNode::Radius * 2, bottomColor);
    front_img.create(SnakeBodyNode::Radius * 2, SnakeBodyNode::Radius * 2 / 3, topColor);

    sf::Texture body;
    body.loadFromImage(bg_img);
    body.update(front_img, 0, SnakeBodyNode::Radius * 2 / 3);
    body.setSmooth(true);
    return body;
}

void Resource::switchToMusic(const std::string& fileName)
{
    static std::string curMusic = "";

    if (curMusic == fileName) return;
    auto& music = getInstance().bgMusic_;

    if (curMusic != "") music.stop();
    if (!music.openFromFile("Music/" + fileName + ".wav"))
    {
        std::cerr << "open " << fileName << " fail." << std::endl;
        return;
    }
    curMusic = fileName;

    music.setLoopPoints(getMusicLoopPoints(fileName));
    music.setLoop(true);
    music.play();
}

sf::Music::TimeSpan& Resource::getMusicLoopPoints(const std::string& fileName)
{
    static std::map<std::string, sf::Music::TimeSpan> loopMap_ = {  // 音乐截取时刻的存储
        {"Cute"   , sf::Music::TimeSpan(sf::seconds(0), sf::seconds(30))},
        {"Pretty" , sf::Music::TimeSpan(sf::seconds(0), sf::seconds(48))},
        {"Silent" , sf::Music::TimeSpan(sf::seconds(0), sf::seconds(55))},
        {"Default", sf::Music::TimeSpan(sf::seconds(0), sf::seconds(49))}
    };
    static sf::Music::TimeSpan empty_ = sf::Music::TimeSpan(sf::seconds(0), sf::seconds(0));

    auto iter = loopMap_.find(fileName);
    return iter == loopMap_.end() ? empty_ : iter -> second;
}
