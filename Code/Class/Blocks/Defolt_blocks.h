#ifndef Defolt_Block_h
#define Defolt_Block_h
#include "../Block.h"

class Dirt_block : public Block
{
public:
	Dirt_block(v2f pos_id) : Block(pos_id, Block_id::DIRT){}
};


class Wood_block : public Block
{
public:
	Wood_block(v2f pos_id) : Block(pos_id, Block_id::WOOD) {}
};

class Stone_block : public Block
{
public:
	Stone_block(v2f pos_id) : Block(pos_id, Block_id::STONE) {}
};

class Grass_block : public Block
{
public:
	Grass_block(v2f pos_id) : Block(pos_id, Block_id::GRASS) {}
};

class Coal_block : public Block
{
public:
	Coal_block(v2f pos_id) : Block(pos_id, Block_id::COAL) {}
};

class Diamond_block : public Block
{
public:
	Diamond_block(v2f pos_id) : Block(pos_id, Block_id::DIAMOND) {}
};

class Gold_block : public Block
{
public:
	Gold_block(v2f pos_id) : Block(pos_id, Block_id::GOLD) {}
};

class Iron_block : public Block
{
public:
	Iron_block(v2f pos_id) : Block(pos_id, Block_id::IRON) {}
};

#endif