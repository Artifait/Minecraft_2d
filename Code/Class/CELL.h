#pragma once
#include <map>
#include "Draw_rect.h"
#include "v2f.h"
#include "Enums_maps.h"
#include "Draw_rect.h"
#include "../App_parameters.h"
class Cell
{
public:
	Cell()
	{
		type_id = 1;
		is_live = false;
		rect_cell.init(v2f(), v2f(1, 1));
		pos_cell = v2f();
		rect_cell.set_color_all(Color(255 * is_live, 255 * is_live, 255 * is_live));
	}
	Cell(bool state, v2f pos_kl, v2f size_kl, int type_idd = enums::type_block::block)
	{
		type_id = type_idd;
		is_live = state;
		rect_cell.init(size_kl, pos_kl*GAME::SizeBlock);
		pos_cell = pos_kl;
		rect_cell.set_color_all(Color(255 * state, 255 * state, 255 * state));
	}
	virtual void update(std::map<v2f, Cell*>& pole_cell_from, std::map<v2f, Cell*>& pole_cell_to)
	{
		pole_cell_to[pos_cell] = new Cell(true, pos_cell, GAME::bl_2d);
		cout << "i" << endl;
	}
	virtual void draw(RenderWindow& window)
	{
		rect_cell.init(v2f(GAME::SizeBlock, GAME::SizeBlock), pos_cell * GAME::SizeBlock);
		rect_cell.set_color_all(Color(255 * is_live, 255 * is_live, 255 * is_live));
		rect_cell.draw(window);
	}
	int type_id;
	Draw_rect rect_cell;
	bool is_live;
	v2f pos_cell;

};

class Water_cell : public Cell
{
public:
	Water_cell(int sila_water = 7, bool state = true, v2f pos_kl = v2f(), bool istok = false) : Cell(state, pos_kl, v2f(GAME::SizeBlock, GAME::SizeBlock), 0)
	{
		this->sila_water = sila_water;
		istochnik = istok;
	}
	void update(std::map<v2f, Cell*>& pole_cell_from, std::map<v2f, Cell*>& pole_cell_to) override
	{
		pole_cell_to[pos_cell] = new Water_cell(sila_water, true, pos_cell, istochnik);
		for (auto& ch_v2f :enums::von_vicinity)
		{
			if (pole_cell_from.find(pos_cell + ch_v2f) == pole_cell_from.end())
			{
				auto bl_n = pole_cell_from.find(pos_cell + v2f(0, 1));
				if(istochnik)
				{
					if (ch_v2f == v2f(-1, 0))
					{
						pole_cell_to[pos_cell + ch_v2f] = new Water_cell(sila_water - 1, true, pos_cell + ch_v2f);
					}
					else if (ch_v2f == v2f(1, 0))
					{
						pole_cell_to[pos_cell + ch_v2f] = new Water_cell(sila_water - 1, true, pos_cell + ch_v2f);
					}
				}
				else if (bl_n != pole_cell_from.end() && bl_n->second->type_id == enums::type_block::block)
				{
					if (ch_v2f == v2f(-1, 0))
					{
						pole_cell_to[pos_cell + ch_v2f] = new Water_cell(sila_water - 1, true, pos_cell + ch_v2f);
					}
					else if (ch_v2f == v2f(1, 0))
					{
						pole_cell_to[pos_cell + ch_v2f] = new Water_cell(sila_water - 1, true, pos_cell + ch_v2f);
					}
				}
				if (ch_v2f == v2f(0, 1))
				{
					pole_cell_to[pos_cell + ch_v2f] = new Water_cell(7, true, pos_cell + ch_v2f, false);
				}



			}

		}
	}
	void draw(RenderWindow& window) override
	{
		rect_cell.init(v2f(GAME::SizeBlock, GAME::SizeBlock), pos_cell * GAME::SizeBlock);
		rect_cell.set_color_all(Color(20 * sila_water * is_live, 255 * is_live, 255 * is_live));
		rect_cell.draw(window);
	}
	bool istochnik;
	int sila_water;
};

class Block_cell : public Cell
{
public:
	Block_cell(bool state, v2f pos_kl) : Cell(state, pos_kl, v2f(GAME::SizeBlock, GAME::SizeBlock))
	{

	}
	void update(std::map<v2f, Cell*>& pole_cell_from, std::map<v2f, Cell*>& pole_cell_to) override
	{
		pole_cell_to[pos_cell] = new Block_cell(true, pos_cell);
	}

};
