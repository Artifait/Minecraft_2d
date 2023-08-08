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
	sf::VertexArray for_draw;
	v2f vel;
	std::vector<rect*> contact;
	rect(v2f size_rect = v2f(-1, -1), v2f pos_rect = v2f(0,0))
	{
		init(size_rect, pos_rect);
	}
	void init(v2f size_rect, v2f pos_rect)
	{
		for_draw.setPrimitiveType(sf::Quads);
		for_draw.resize(4);
		setsize(size_rect);
		setpos(pos_rect);
		for_draw[0].texCoords = sf::Vector2f(0, 0);
		for_draw[1].texCoords = sf::Vector2f(16, 0);
		for_draw[2].texCoords = sf::Vector2f(16, 16);
		for_draw[3].texCoords = sf::Vector2f(0, 16);
	}
	void setpos(v2f pos = v2f())
	{
		body_rect.setPosition(pos);

		for_draw[0].position = pos;
		for_draw[1].position = pos + sf::Vector2f(body_rect.Sizetipo.x, 0);
		for_draw[2].position = pos + body_rect.Sizetipo;
		for_draw[3].position = pos + sf::Vector2f(0, body_rect.Sizetipo.y);
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
		setpos(body_rect.getPosition());
	}
	bool operator==(const rect& other) const {
		return body_rect == other.body_rect && vel == vel;
	}
};
#endif