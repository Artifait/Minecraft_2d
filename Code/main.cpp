#pragma once

#include "Class/App_work.h"
int main()
{
    Game_App Game("GAME", Vector2u(1200, 800), 45);
    Game.run();
    return 0;
}