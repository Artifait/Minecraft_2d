#ifndef Entity_h
#define Entity_h
#include "SFML/Graphics.hpp"
#include "Simple_timer.h"
class Entity
{
public:
	Entity();
	virtual void update() = 0;
	

private:
	bool Live;
	SimpleTimer time_live;
	bool on_graund;


};

Entity::Entity()
{

}

#endif