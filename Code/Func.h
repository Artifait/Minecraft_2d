#ifndef Func_h
#define Func_h

#include "Class/Enums_maps.h"
#include "SFML/Graphics.hpp"
#include "App_parameters.h"
#include "Class/World.h"
#include <map>
using namespace sf;
using namespace std;
float returnRadian(float angle)
{
    return angle * GAME::M_PI / 180.0;;
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
    load_to_map("blocks", Block_id::BEDROCK, MAPS::index_and_texture, IntRect(16, 16, 16, 16));
    load_to_map("blocks", Block_id::IRON, MAPS::index_and_texture, IntRect(32, 16, 16, 16));
    load_to_map("blocks", Block_id::WOOD, MAPS::index_and_texture, IntRect(48, 0, 16, 16));
    load_to_map("blocks", Block_id::SAND, MAPS::index_and_texture, IntRect(16, 0, 16, 16));
    load_to_map("blocks", Block_id::DIRT, MAPS::index_and_texture, IntRect(0, 16, 16, 16));
    load_to_map("blocks", Block_id::COAL, MAPS::index_and_texture, IntRect(32, 32, 16, 16));
    load_to_map("blocks", Block_id::GOLD, MAPS::index_and_texture, IntRect(0, 32, 16, 16));
    load_to_map("blocks", Block_id::STONE, MAPS::index_and_texture, IntRect(32, 0, 16, 16));
    load_to_map("blocks", Block_id::GRASS, MAPS::index_and_texture, IntRect(0, 0, 16, 16));
    load_to_map("blocks", Block_id::DIAMOND, MAPS::index_and_texture, IntRect(16, 32, 16, 16));
    for (int i = 0; i < 256; i++) {
        float t = i / 255.0f;
        GAME::gradientMap[i] = t * t * (3 - 2 * t); // функция интерполяции
    }
    if (!GAME::defolt_font.loadFromFile("Fonts/shrift_norm.ttf")) { cout << "NOLOAD"; }

}

void SETTUP_GAME()
{
    
}

void Update_camera(float Delta_time, View camera_mine)
{

    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        camera_mine.move(-GAME::Speed_camera * Delta_time, 0);
    }
    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        camera_mine.move(GAME::Speed_camera * Delta_time, 0);
    }
    if (Keyboard::isKeyPressed(Keyboard::W))
    {
        camera_mine.move(0, -GAME::Speed_camera * Delta_time);
    }
    if (Keyboard::isKeyPressed(Keyboard::S))
    {
        camera_mine.move(0, GAME::Speed_camera * Delta_time);
    }
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
void Draw_setka(RenderWindow& window)
{
    Color col_setka = Color::White;
    int x_win_start = window.mapPixelToCoords(Vector2i(0, 0)).x;
    x_win_start = (x_win_start / Block::Size_block) * Block::Size_block;
    for (int i = 0;i < GAME::WIDTH / Block::Size_block;i++)
    {
        VertexArray setka_line(Lines, 2);
        setka_line[0].position = Vector2f(x_win_start + Block::Size_block * i, window.mapPixelToCoords(Vector2i(0, 0)).y);
        setka_line[1].position = Vector2f(x_win_start + Block::Size_block * i, window.mapPixelToCoords(Vector2i(0, GAME::HEIGHT)).y);
        setka_line[0].color = col_setka;
        setka_line[1].color = col_setka;
        window.draw(setka_line);
    }
    x_win_start = window.mapPixelToCoords(Vector2i(0, 0)).y;
    x_win_start = (x_win_start / Block::Size_block) * Block::Size_block;
    for (int i = 0;i < GAME::HEIGHT / Block::Size_block;i++)
    {
        VertexArray setka_line(Lines, 2);
        setka_line[0].position = Vector2f(window.mapPixelToCoords(Vector2i(0, 0)).x, x_win_start + Block::Size_block * i);
        setka_line[1].position = Vector2f(window.mapPixelToCoords(Vector2i(GAME::WIDTH, 0)).x, x_win_start + Block::Size_block * i);
        setka_line[0].color = col_setka;
        setka_line[1].color = col_setka;
        window.draw(setka_line);
    }
}
Block* poisk_block(VertexArray& line_for_cast, World_MineCraft& mine_world, v2f& block_id_end, RenderWindow& window)
{
    Block* Block_return;
    v2f vRayStart = v2f(line_for_cast[0].position) / Block::Size_block;
    float fMaxDistance = v2f(line_for_cast[1].position - line_for_cast[0].position).getLength() / Block::Size_block;
    //window.setTitle(to_string(fMaxDistance));
    v2f vRayDir = line_for_cast[1].position - line_for_cast[0].position;
    vRayDir.normalize();
    // Lodev.org also explains this additional optimistaion (but it's beyond scope of video)
    v2f vRayUnitStepSize = { abs(1.0f / vRayDir.x), abs(1.0f / vRayDir.y) };

    //v2f vRayUnitStepSize = { sqrt(1 + (vRayDir.y / vRayDir.x) * (vRayDir.y / vRayDir.x)), sqrt(1 + (vRayDir.x / vRayDir.y) * (vRayDir.x / vRayDir.y)) };
    Vector2i vMapCheck = Vector2i(vRayStart.x, vRayStart.y);
    if (vMapCheck.x < 0)
        vMapCheck.x--;
    if (vMapCheck.y < 0)
        vMapCheck.y--;
    v2f vRayLength1D;
    Vector2i vStep;
    float chunk_id_cast_x = floor(vMapCheck.x / 16.f);
    float chunk_id_cast_y = floor(vMapCheck.y / 16.f);
    Block_return = mine_world.GIVE_PLAYER_CHUNK(v2f(chunk_id_cast_x, chunk_id_cast_y)).Give_block_in_chunk(vMapCheck);
    if (Block_return != nullptr)
        return Block_return;
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
    float fDistance = 0.0f;
    v2f vIntersection;
    while (fDistance < fMaxDistance)
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
        chunk_id_cast_x = floor(vMapCheck.x / 16.f);
        chunk_id_cast_y = floor(vMapCheck.y / 16.f);
        Block_return = mine_world.GIVE_PLAYER_CHUNK(v2f(chunk_id_cast_x, chunk_id_cast_y)).Give_block_in_chunk(vMapCheck);
        block_id_end = vMapCheck;
        window.setTitle(to_string(fDistance));
        if (Block_return != nullptr && fDistance <= fMaxDistance)
        {
            return Block_return;
        }

    }
    return nullptr;
}

bool check_CAN_put(World_MineCraft& mine_world, v2f id_check_block)
{
    vector<v2f> directions_v = { v2f(1, 0), v2f(-1, 0), v2f(0, 1), v2f(0, -1) };
    bool est_nety = false;
    for(auto& puth : directions_v)
    {
        v2f chunk_id = v2f(floor((id_check_block.x + puth.x) / 16.f), floor((id_check_block.y + puth.y) / 16.f));
        if (mine_world.GIVE_PLAYER_CHUNK(chunk_id).Give_block_in_chunk(id_check_block + puth) == nullptr)
        {
            est_nety = max(est_nety, false);
        }
        else
        {
            est_nety = true;
        }
    }
    return est_nety;
}
void DRAW_CAST_BLOCK(VertexArray& line_for_cast, World_MineCraft& mine_world, int light_intensity, RenderWindow& window)
{
    if (light_intensity <= 0)
        return;
    v2f vRayStart = v2f(line_for_cast[0].position) / Block::Size_block;

    v2f vRayDir = line_for_cast[1].position - line_for_cast[0].position;
    vRayDir.normalize();
    // Lodev.org also explains this additional optimistaion (but it's beyond scope of video)
    v2f vRayUnitStepSize = { abs(1.0f / vRayDir.x), abs(1.0f / vRayDir.y) };

    //v2f vRayUnitStepSize = { sqrt(1 + (vRayDir.y / vRayDir.x) * (vRayDir.y / vRayDir.x)), sqrt(1 + (vRayDir.x / vRayDir.y) * (vRayDir.x / vRayDir.y)) };
    Vector2i vMapCheck = Vector2i( vRayStart.x, vRayStart.y);
    v2f vRayLength1D;
    Vector2i vStep;
    float chunk_id_cast_x = floor(vMapCheck.x / 16.f);
    float chunk_id_cast_y = floor(vMapCheck.y / 16.f);
    mine_world.GIVE_PLAYER_CHUNK(v2f(chunk_id_cast_x, chunk_id_cast_y)).DRAW_BLOCK_IN_CHUNK(vMapCheck, window);
    drawShadow(window, FloatRect(v2f(vMapCheck) * Block::Size_block, Vector2f(Block::Size_block, Block::Size_block)), light_intensity);

    sf::VertexArray block_vydel(Quads, 4);
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
    float fMaxDistance = GAME::HALF_HEIGHT/ Block::Size_block +1;
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
        chunk_id_cast_x = floor(vMapCheck.x / 16.f);
        chunk_id_cast_y = floor(vMapCheck.y / 16.f);
        if (mine_world.GIVE_PLAYER_CHUNK(v2f(chunk_id_cast_x, chunk_id_cast_y)).DRAW_BLOCK_IN_CHUNK(vMapCheck, window))
        {
            drawShadow(window, FloatRect(v2f(vMapCheck) * Block::Size_block, Vector2f(Block::Size_block, Block::Size_block)), light_intensity);
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


void Draw_line_Cast(World_MineCraft& mine_world, int Streng_lite, RenderWindow& window)
{
    int LIGHT_INTENSITY_ON_LINE = Streng_lite;
    int len_now, start_len;
    if ((GAME::WIDTH / Block::Size_block) % 2 == 1)
    {
        start_len = len_now = -(static_cast<int>((GAME::WIDTH / Block::Size_block) / 2) + 1);
    }
    else
    {
        start_len = len_now = -(static_cast<int>((GAME::WIDTH / Block::Size_block) / 2));
    }
    v2f delta_risovka;
    if (window.mapPixelToCoords(Vector2i(0, 0)).x < 0)
        delta_risovka.x = -Block::Size_block;
    if (window.mapPixelToCoords(Vector2i(0, 0)).y < 0)
        delta_risovka.y = -Block::Size_block;
    v2f i = window.mapPixelToCoords(Vector2i(0, GAME::HALF_HEIGHT));
    i += delta_risovka;
    Color col_setka = Color::White;
    for (;i.x <= window.mapPixelToCoords(Vector2i(GAME::WIDTH, 0)).x + Block::Size_block;i.x += Block::Size_block)
    {
        VertexArray setka_line(Lines, 2);
        setka_line[0].position = i;
        setka_line[1].position = setka_line[0].position + Vector2f(0, GAME::HALF_HEIGHT);
        setka_line[0].color = col_setka;
        setka_line[1].color = col_setka;
        //window.draw(setka_line);
        DRAW_CAST_BLOCK(setka_line, mine_world, LIGHT_INTENSITY_ON_LINE - abs(len_now), window);
        len_now++;
    }
    i = window.mapPixelToCoords(Vector2i(0, GAME::HALF_HEIGHT));
    i += delta_risovka;
    len_now = start_len;
    for (;i.x <= window.mapPixelToCoords(Vector2i(GAME::WIDTH, 0)).x + Block::Size_block;i.x += Block::Size_block)
    {
        VertexArray setka_line(Lines, 2);
        setka_line[0].position = i;
        setka_line[1].position = setka_line[0].position - Vector2f(0, GAME::HALF_HEIGHT);
        setka_line[0].color = col_setka;
        setka_line[1].color = col_setka;
        //window.draw(setka_line);
        DRAW_CAST_BLOCK(setka_line, mine_world, LIGHT_INTENSITY_ON_LINE - abs(len_now), window);
        len_now++;
    }
}

#endif