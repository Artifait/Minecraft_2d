#ifndef Rect_h
#define Rect_h
#include <map>
#include "TipoRectangleShape.h"
#include "SFML/Graphics.hpp"
#include "v2f.h"
#include <vector>

using namespace sf;
struct rect
{
	TipoRectangleShape body_rect;
	v2f vel;
	std::vector<rect*> contact;
	void init(v2f size_rect, v2f pos_rect)
	{
		setsize(size_rect);
		setpos(pos_rect);
	}
	void setpos(v2f pos = v2f())
	{
		body_rect.setPosition(pos);
	}
	void move(v2f offset_vec)
	{
		setpos(offset_vec + body_rect.getPosition());
	}
	void move(float offset_x, float offset_y)
	{
		v2f offset_vec(offset_x, offset_y);
		setpos(offset_vec + body_rect.getPosition());
	}
	void setsize(v2f size)
	{
		body_rect.setSize(size);
	}
	bool operator==(const rect& other) const {
		return body_rect == other.body_rect && vel == vel;
	}
};
#endif