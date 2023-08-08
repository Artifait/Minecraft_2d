#ifndef Chunk_h
#define Chunk_h
#include "Blocks/Defolt_blocks.h"
#include "Enums_maps.h"
#include "SFML/Graphics.hpp"
#include <map>
#include "../Biblea/FastNoise.h"

void SETTUP_GAME();

class Chunk_mine
{
public:
	Chunk_mine()
	{
		this->POS_CHUNK = v2f(0,0);
	}
	Block* Give_block_in_chunk(v2f id_block)
	{
		if (blocks_in_chunk.find(id_block) != blocks_in_chunk.end())
			return &blocks_in_chunk[id_block];
		else
			return nullptr;
	}

	rect Give_block_collider(v2f id_block)
	{
		if (blocks_in_chunk.find(id_block) != blocks_in_chunk.end())
			return blocks_in_chunk[id_block].get_collider();
		else
			return rect();
	}

	bool DRAW_BLOCK_IN_CHUNK(v2f id_block_draw, RenderWindow& window)
	{
		if(blocks_in_chunk.count(id_block_draw) > 0)
		{
			blocks_in_chunk[id_block_draw].Draw_block(window);
			return true;
		}
		else
			return false;
	}
	int get_count_block()
	{
		return visible_block;
	}
	Chunk_mine(v2f POS_CHUNK, std::map<v2f, Block> blocks_from_generator);
	void Draw_chunk(FloatRect camera_vid, int offset_z, RenderWindow& window);

private:

	friend class Player;friend class World_MineCraft;
	void Break_block_in_chunk(v2f id_block)
	{
		if (blocks_in_chunk.find(id_block) != blocks_in_chunk.end())
			blocks_in_chunk.erase(id_block);
	}
	int visible_block = 0;
	std::map<v2f, Block> blocks_in_chunk;
	v2f POS_CHUNK;
};

Chunk_mine::Chunk_mine(v2f POS_CHUNK, std::map<v2f, Block> blocks_from_generator)
{
	this->POS_CHUNK = POS_CHUNK;
	this->blocks_in_chunk = blocks_from_generator;
}
inline void Chunk_mine::Draw_chunk(FloatRect camera_vid, int offset_z, RenderWindow& window)
{
	
	visible_block = 0;
	for (auto& bl : blocks_in_chunk)
	{
		v2f point_bl = bl.first * Block::Size_block;

		if (RectVsRect(FloatRect(point_bl, Vector2f(Block::Size_block, Block::Size_block)), camera_vid))
		{
			bl.second.Draw_block(window);
			visible_block++;
		}
		
	}
}
#endif