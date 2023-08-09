#pragma once
#include "SFML/Graphics/VertexArray.hpp"
#include "v2f.h"

class Draw_rect
{
public:
	Draw_rect(v2f size_r = v2f(GAME::SizeBlock, GAME::SizeBlock), v2f pos_r = v2f())
	{
		init(size_r, pos_r);
	}
	void init(v2f size_r, v2f pos_r)
	{
		rect_dr.resize(4);
		rect_dr.setPrimitiveType(Quads);
		rect_dr[0].position = pos_r;
		rect_dr[1].position = v2f(pos_r.x + size_r.x, pos_r.y);
		rect_dr[3].position = v2f(pos_r.x, pos_r.y + size_r.y);
		rect_dr[2].position = pos_r + size_r;
	}
	void set_color_all(Color col)
	{
		rect_dr[0].color = col;
		rect_dr[1].color = col;
		rect_dr[2].color = col;
		rect_dr[3].color = col;
	}
	void draw(RenderWindow& window)
	{
		window.draw(rect_dr);
	}
	sf::VertexArray rect_dr;
};
