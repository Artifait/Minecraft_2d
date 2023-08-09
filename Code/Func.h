#ifndef Func_h
#define Func_h
#include "Class/v2f.h"
#include "Class/Enums_maps.h"
#include "SFML/Graphics.hpp"
#include <map>
#include "App_parameters.h"
#include <iostream>
using namespace sf;
using namespace std;
float returnRadian(float angle)
{
    return angle * GAME::M_PI / 180.0;
}
void load_to_map(string name_file, int index_map, map<int , Texture>& map_for_txture, string extension = ".png")
{
    Texture ld_tx;
    ld_tx.loadFromFile("Images/" + name_file + extension);
    map_for_txture[index_map] = ld_tx;
}
    
void load_to_map(string name_file, int index_map, map<int, Texture>& map_for_txture, IntRect zone_txture, string extension = ".png")
{
    Texture ld_tx;
    ld_tx.loadFromFile("Images/" + name_file + extension, zone_txture);
    map_for_txture[index_map] = ld_tx;
}

void load_Texture()
{
    for (int i = 0; i < 256; i++) {
        float t = i / 255.0f;
        GAME::gradientMap[i] = t * t * (3 - 2 * t); // функция интерполяции
    }
}

void SETTUP_GAME()
{
    
}


void cout_v2f(v2f v2f)
{
    cout << "X = " << v2f.x << "   , Y = " << v2f.y << endl;
}
void fps_counter_update(float delta_t, RenderWindow& window)
{
    window.setTitle("FPS: " + to_string(static_cast<int>(1/(delta_t/1000))));
}
void drawShadow(sf::RenderTarget& target, sf::FloatRect rect, int lightLevel)
{
    // определяем цвет тени в зависимости от уровня освещения
    sf::Color startColor(0, 0, 0, 255); // начальный цвет тени
    sf::Color endColor(0, 0, 0, 0); // конечный цвет тени
    float t = static_cast<float>(lightLevel) / 8.f; // расстояние между цветами
    sf::Color shadowColor = lerp( startColor, endColor, t); // плавный переход между цветами

    // создаем фигуру для закрашивания тени
    sf::RectangleShape shadow;
    shadow.setPosition(rect.left, rect.top); // смещение тени на 10 пикселей вправо и вниз
    shadow.setSize(sf::Vector2f(rect.width, rect.height));
    shadow.setFillColor(shadowColor);

    // рисуем тень на заданном RenderTarget
    target.draw(shadow);
}


void DRAW_CAST_BLOCK(VertexArray& line_for_cast, int light_intensity, int SizeBlock)
{
    if (light_intensity <= 0)
        return;
    v2f vRayStart = v2f(line_for_cast[0].position) / SizeBlock;

    v2f vRayDir = line_for_cast[1].position - line_for_cast[0].position;
    vRayDir.normalize();
    // Lodev.org also explains this additional optimistaion (but it's beyond scope of video)
    v2f vRayUnitStepSize = { abs(1.0f / vRayDir.x), abs(1.0f / vRayDir.y) };

    //v2f vRayUnitStepSize = { sqrt(1 + (vRayDir.y / vRayDir.x) * (vRayDir.y / vRayDir.x)), sqrt(1 + (vRayDir.x / vRayDir.y) * (vRayDir.x / vRayDir.y)) };
    Vector2i vMapCheck = Vector2i( vRayStart.x, vRayStart.y);
    v2f vRayLength1D;
    Vector2i vStep;

    int ITERATION = 0;
    int GOOD_ITERATION = 0;
    // Establish Starting Conditions
    if (vRayDir.x < 0)
    {
        vStep.x = -1;
        vRayLength1D.x = (vRayStart.x - float(vMapCheck.x)) * vRayUnitStepSize.x;
    }
    else
    {
        vStep.x = 1;
        vRayLength1D.x = (float(vMapCheck.x + 1) - vRayStart.x) * vRayUnitStepSize.x;
    }

    if (vRayDir.y < 0)
    {
        vStep.y = -1;
        vRayLength1D.y = (vRayStart.y - float(vMapCheck.y)) * vRayUnitStepSize.y;
    }
    else
    {
        vStep.y = 1;
        vRayLength1D.y = (float(vMapCheck.y + 1) - vRayStart.y) * vRayUnitStepSize.y;
    }

    // Perform "Walk" until collision or range check
    bool bTileFound = false;
    float fMaxDistance = GAME::HALF_HEIGHT/SizeBlock+1;
    float fDistance = 0.0f;
    v2f vIntersection;
    ITERATION++;
    while ((!bTileFound && fDistance < fMaxDistance) && light_intensity > 0)
    {
        // Walk along shortest path
        if (vRayLength1D.x < vRayLength1D.y)
        {
            vMapCheck.x += vStep.x;
            fDistance = vRayLength1D.x;
            vRayLength1D.x += vRayUnitStepSize.x;
        }
        else
        {
            vMapCheck.y += vStep.y;
            fDistance = vRayLength1D.y;
            vRayLength1D.y += vRayUnitStepSize.y;
        }

        if (true)
        {
            //tanerovka_blocka += Color(255, 179, 0);
            if(light_intensity <= 0)
                bTileFound = true;
            GOOD_ITERATION++;
        }
        else
        {
            //tanerovka_blocka += Color(255*(1/ITERATION), 179 * (1 / ITERATION), 0);
        }
        light_intensity--;

       /* // Заполняем вершины квадрата
        block_vydel[0].color = tanerovka_blocka;
        block_vydel[1].color = tanerovka_blocka;
        block_vydel[2].color = tanerovka_blocka;
        block_vydel[3].color = tanerovka_blocka;
        window.draw(block_vydel);
        ITERATION++;*/
    }
}



#endif