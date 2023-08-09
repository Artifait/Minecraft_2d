#pragma once
#include "Cell.h"
class Karta_Cell
{
public:
	Karta_Cell()
	{
		
	}
	void put_cell(v2f pos_put_cell, int type_cell , RenderWindow& window)
	{
		switch (type_cell)
		{
		case enums::type_block::block:
		{
			pole_cell[pos_put_cell] = new Block_cell(true, pos_put_cell);
			break;
		}
		case enums::type_block::Water:
		{
			pole_cell[pos_put_cell] = new Water_cell(7, true, pos_put_cell, true);
			break;
		}
		default:
		{
			pole_cell[pos_put_cell] = new Block_cell(true, pos_put_cell);
			break;
		}
		}
		window.setTitle(to_string(pole_cell.size()));//"\nx = " + to_string(pos_put_cell.x) + "\ny = " + to_string(pos_put_cell.y) + "\n\n");
	}
	void break_cell(v2f pos_break_cell)
	{
		pole_cell.erase(pos_break_cell);
	}
	void update_karta()
	{
		std::map<v2f, Cell*> pole_cell_new;
		for (auto& cl_dr : pole_cell)
		{
			(cl_dr.second)->update(pole_cell, pole_cell_new);
		}
		for (auto& bl_c : pole_cell)
		{
			delete bl_c.second;
		}
		for (auto& bl_c : pole_cell_new)
		{
			pole_cell[bl_c.first] = bl_c.second;
		}
	}
	void draw_karta(RenderWindow& window)
	{
		for (auto& cl_now : pole_cell)
		{
			cl_now.second->draw(window);
		}
	}
	std::map<v2f, Cell*> pole_cell;
};
