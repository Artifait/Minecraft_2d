#ifndef Block_h
#define Block_h
#include "../App_parameters.h"
#include "Enums_maps.h"
#include "SFML/Graphics.hpp"
#include "v2f.h"
#include "Rect.h"
using namespace sf;
void SETTUP_GAME();
class Block
{
public:
	Block(v2f pos_id = v2f(), int id_block = -1);
	rect* give_rect_block() { return &rect_block; }
	rect get_collider() { return rect_block; }
	void Draw_block(RenderWindow& window);
	virtual void update_block();
	static int Size_block;
	v2f Give_pos_id()
	{
		return pos_id;
	}
private:
	friend void SETTUP_GAME();
	
	rect rect_block;
	Vector2f pos_id;
	int id_block;
};

Block::Block(v2f pos_id, int id_block)
{
	rect_block.init(v2f(static_cast<float>(Size_block), static_cast<float>(Size_block)),pos_id * static_cast<float>(Size_block));
	this->pos_id = pos_id;
	this->id_block = id_block;
}
inline void Block::Draw_block(RenderWindow& window)
{
	RenderStates states;
	states.texture = &MAPS::index_and_texture[id_block];
	window.draw(rect_block.for_draw, states);
}
inline void Block::update_block()
{
}

int Block::Size_block = GAME::SizeBlock;
#endif