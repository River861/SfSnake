#include <SFML/Graphics.hpp>

#include <memory>

#include "MenuScreen.h"
#include "SettingScreen.h"
#include "Game.h"
#include "Resource.h"

using namespace sfSnake;

SettingScreen::SettingScreen()
{
    settings_ = std::vector<Setting>
    {
        Setting("SnakeType",
                std::vector<std::string>{"Devil", "Fool" , "Alien", "Penguin"},
                (float)Game::Height / 6),
        Setting("Background",
                std::vector<std::string>{"White", "Black", "Brown"},
                (float)Game::Height * 2 / 6),
        Setting("Grid",
                std::vector<std::string>{"Black", "White", "Brown"},
                (float)Game::Height * 3 / 6),
        Setting("Music",
                std::vector<std::string>{"Cute", "Pretty", "Silent", "Default"},
                (float)Game::Height * 4 / 6)
    };

    buttons_ = std::vector<Button>
    {
        Button("Okay"  , sf::Vector2f((float)Game::Width / 3    , (float)Game::Height * 5 / 5.8)),
        Button("Cancel", sf::Vector2f((float)Game::Width * 2 / 3, (float)Game::Height * 5 / 5.8)),
    };
}

void SettingScreen::handleInput(sf::RenderWindow& window)
{
    for (auto& button : buttons_) button.setFillColor(sf::Color::White);

    for (auto& button : buttons_)
    {
        if (button.isHover(window))
        {
            button.setFillColor(sf::Color::Blue);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                auto& name = button.getString();
                if (name == "Okay") commit();
                Game::Screen = std::make_shared<MenuScreen>();
            }
            return;
        }
    }
    for (auto& setting : settings_) setting.handleInput(window);
}

void SettingScreen::update(sf::Time delta) {}

void SettingScreen::render(sf::RenderWindow& window)
{
    for (auto& setting : settings_) setting.render(window);
    for (auto& button : buttons_) window.draw(button);
}

void SettingScreen::commit()
{
    for (auto& setting : settings_) setting.commit();
}
