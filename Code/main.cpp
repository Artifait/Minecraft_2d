


#pragma once
#include "Class/App_work.h"
int main()
{
    Game_App Game("GAME", Vector2u(GAME::WIDTH, GAME::HEIGHT), 60);
    Game.run();
    return 0;
}