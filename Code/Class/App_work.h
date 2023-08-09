#pragma once
#include "App_defolt.h"
#include "../Func.h"
#include "Text_fast.h"
#include "Karta_cell.h"
class Game_App : public BaseApplication {
public:
    Game_App(const std::string& title, const sf::Vector2u& size, int FPS_limit)
        : BaseApplication(title, size)
    {
        srand(static_cast<unsigned int>(time(NULL)));
        SETTUP_GAME();
        load_Texture();
        setFramerateLimit(FPS_limit);
        vbr_type_cell_now = 0;
    }

    void handleEvents() override {
        pixelPos = Mouse::getPosition(getWindow());
        worldPos = getWindow().mapPixelToCoords(pixelPos);
        v2f coord_put = v2f(floor(worldPos.x / GAME::SizeBlock), floor(worldPos.y / GAME::SizeBlock));
        sf::Event event;
        while (pollEvent(event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                vbr_type_cell_now--;
                if (vbr_type_cell_now < 0)
                    vbr_type_cell_now = 1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                vbr_type_cell_now++;
                if (vbr_type_cell_now > 1)
                    vbr_type_cell_now = 0;
            }

            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                close();
            }
            if (Mouse::isButtonPressed(Mouse::Left)) 
            {
                cout << vbr_type_cell_now << endl;
                pole.put_cell(coord_put, vbr_type_cell_now, getWindow());
            }
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right)
            {
                pole.break_cell(coord_put);
            }
        }
    }

    void update() override {
        /*
        Delta_time = static_cast<float>(clock.getElapsedTime().asMilliseconds());
        fps_counter_update(Delta_time, getWindow());
        clock.restart();
        */
        pole.update_karta();
    }

    void render() override {
        Draw_rect rect(v2f(32, 32), v2f(2, 2));
        rect.set_color_all(Color(23, 213, 21));
        //rect.draw(getWindow());
        Block_cell bl_tupo(true, v2f(5, 5));
        //bl_tupo.rect_cell.init(v2f(32, 32), v2f(2, 2));
        bl_tupo.draw(getWindow());
        pole.draw_karta(getWindow());
    }
    float Delta_time;
    Clock clock;
    Karta_Cell pole;
    int vbr_type_cell_now;
    Vector2i pixelPos;
    Vector2f worldPos;
};
