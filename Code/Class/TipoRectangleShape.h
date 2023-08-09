#ifndef Tipo_rect_h
#define Tipo_rect_h
#include "SFML/Graphics.hpp"
using namespace sf;
class TipoRectangleShape
{
public:
	FloatRect getGlobalBounds()
	{
		return FloatRect(Positiontipo, Sizetipo);
	}
	const Vector2f getPosition()
	{
		return Positiontipo;
	}
	const Vector2f getSize()
	{
		return Sizetipo;
	}
	void setPosition(Vector2f pos_nova)
	{
		Positiontipo = pos_nova;
	}
	void setSize(Vector2f size_nove)
	{
		Sizetipo = size_nove;
	}
	void setPosition(float nova_x, float nova_y)
	{
		Positiontipo = Vector2f(nova_x, nova_y);
	}
	void setSize(float nova_x, float nova_y)
	{
		Sizetipo = Vector2f(nova_x, nova_y);
	}
	void move(Vector2f ofset)
	{
		Positiontipo += ofset;
	}
	bool operator==(const TipoRectangleShape& other) const {
		return Sizetipo == other.Sizetipo && Positiontipo == other.Positiontipo;
	}
	Vector2f Sizetipo, Positiontipo;
};
#endif