#pragma once

#include "SFML/Graphics.hpp"

class BaseApplication : public sf::RenderWindow {
public:
    BaseApplication(const std::string& title, const sf::Vector2u& size)
        : sf::RenderWindow(sf::VideoMode(size.x, size.y), title)
    {

    }

    sf::RenderWindow& getWindow() {
        return *this;
    }
    virtual ~BaseApplication() {}

    virtual void handleEvents() {
        sf::Event event;
        while (pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                close();
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                 
            }
        }
    }

    virtual void update() {}

    virtual void render() {}

    void run() {
        while (isOpen())
        {
            handleEvents();
            update();
            clear(sf::Color::Black);
            render();
            display();
        }
    }
};


