#pragma once

#include "App_defolt.h"
#include "../Func.h"
#include "Text_fast.h"
#include "World.h"
#include "Player.h"

class Game_App : public BaseApplication {
public:
    Game_App(const std::string& title, const sf::Vector2u& size, int FPS_limit)
        : BaseApplication(title, size)
    {
        SizeBlock = Block::Size_block;
        srand(static_cast<unsigned int>(time(NULL)));
        SETTUP_GAME();
        load_Texture();

        camera_mine = new View(FloatRect(-400, -400, GAME::WIDTH, GAME::HEIGHT));
        worl_demo = new World_MineCraft(-1, 0);
        pl_one = new Player(Game_mode::SURVIVAL, worl_demo);
        setView(*camera_mine);
        setFramerateLimit(FPS_limit);

    }
    ~Game_App()
    {
        delete camera_mine;
        delete worl_demo;
        delete pl_one;
    }
    void handleEvents() override {
        pixelPos = Mouse::getPosition(getWindow());
        worldPos = getWindow().mapPixelToCoords(pixelPos);
        worldPos.x = floor(worldPos.x / (16.0 * Block::Size_block));
        worldPos.y = floor(worldPos.y / (16.0 * Block::Size_block));
        sf::Event event;
        while (pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                close();
            }

        }
    }

    void update() override {
        Delta_time = static_cast<float>(clock.getElapsedTime().asMilliseconds());
        clock.restart();
        fps_counter_update(Delta_time, getWindow());

    }

    void render() override {
        Draw_line_Cast(*worl_demo, GAME::LIGHT_INTENSITY_CAMERA, getWindow());

        (*pl_one).draw(getWindow());
        (*pl_one).Collision_update(Delta_time, *worl_demo, getWindow(), *camera_mine);
    }
    int SizeBlock;
    View* camera_mine;
    World_MineCraft* worl_demo;
    Player* pl_one;
    float Delta_time;
    Clock clock;
    Vector2i pixelPos;
    Vector2f worldPos;
};
