#ifndef Inventory_h
#define Inventory_h
#include "Item.h"

#include <chrono>


struct Item_in_inventory
{
	Item_in_inventory(int id_blocka_in)
	{
		count_item = 1;
		id_blocka_inv = id_blocka_in;
	}
	Item_in_inventory()
	{
		count_item = 0;
		id_blocka_inv = -1;
	}
	bool plus_item(Item_in_inventory& other_item)
	{
		if (other_item.id_blocka_inv == id_blocka_inv || id_blocka_inv == -1)
		{
			if (id_blocka_inv == -1)
			{
				id_blocka_inv = other_item.id_blocka_inv;
			}
			count_item += other_item.count_item;
			if (count_item > 64)
			{
				other_item.count_item = count_item - 64;
				count_item = 64;
				return false;
			}
			else return true;
		}
		else return false;
	}

	int id_blocka_inv;
	int count_item;
};


class Inventory_box
{
public:
	Inventory_box(FloatRect rect_box, Texture& txture, int tipes_item_hranit)
	{
		this->rect_box.setPosition(rect_box.left, rect_box.top);
		gde_stoat = this->rect_box.getPosition();
		this->rect_box.setSize(v2f(rect_box.width, rect_box.height));
		this->rect_box.setTexture(&txture);
		cofic_razmera = rect_box.height / 36.f;
		tipe_item = tipes_item_hranit;
	}
	void update_box()
	{

	}
	bool plus_item(Item_in_inventory& other_item)
	{
		return item.plus_item(other_item);
	}
	void draw_box(Vector2f smes)
	{
		rect_box.setPosition(gde_stoat + smes);
		window.draw(rect_box);
		if (item.count_item > 0) {
			RectangleShape bl_for_draw;
			bl_for_draw.setSize(Vector2f(24*cofic_razmera, 24*cofic_razmera));
			bl_for_draw.setPosition(rect_box.getPosition() + Vector2f(6*cofic_razmera, 6*cofic_razmera));
			bl_for_draw.setTexture(&index_and_texture[item.id_blocka_inv]);
			window.draw(bl_for_draw);

			Text_fast text_count_item(v2f(60, 10), " ", 12*cofic_razmera, Color::White, &window);
			if(item.count_item>=10)
				text_count_item.POSITION = bl_for_draw.getPosition() + Vector2f(14*cofic_razmera, 15*cofic_razmera);
			else
				text_count_item.POSITION = bl_for_draw.getPosition() + Vector2f(21 * cofic_razmera, 15 * cofic_razmera);
			text_count_item.text = to_string(item.count_item);
			text_count_item.draw();
		}
	}
	int tipe_item;
	float cofic_razmera;
	RectangleShape rect_box;
	Item_in_inventory item;
	Vector2f gde_stoat;
};

class Hot_bar_box
{
public:
	Hot_bar_box(Texture texture_box_hot, Texture vybron_texture, v2f Size_box_hot, v2f pos_hot_box,
		 int index_box)
	{
		this->vybron_texture = vybron_texture;
		defolt_texture = texture_box_hot;
		Bar_box_rect.setTexture(&texture_box_hot);
		Bar_box_rect.setSize(Size_box_hot);
		Bar_box_rect.setPosition(pos_hot_box);
		gde_stoat = pos_hot_box;
		cofic_razmera = Size_box_hot.y / 44.f;
		index_box_in_inventory = index_box;
	}
	void update_texure(v2f mouse_cord)
	{
		if (PointVsRect(mouse_cord, Bar_box_rect.getGlobalBounds()))
		{
			Bar_box_rect.setTexture(&vybron_texture);
		}
		else
		{
			Bar_box_rect.setTexture(&defolt_texture);
		}
	}
	void draw_hot_bar(vector<Inventory_box>& nash_vector)
	{
		Bar_box_rect.setPosition(gde_stoat + Vector2f(cameraOffsetX, cameraOffsetY));
		window.draw(Bar_box_rect);
		if (nash_vector[index_box_in_inventory].item.count_item > 0) {
			RectangleShape bl_for_draw;
			bl_for_draw.setSize(Vector2f(24 * cofic_razmera, 24 * cofic_razmera));
			bl_for_draw.setPosition(Bar_box_rect.getPosition() + Vector2f(10 * cofic_razmera, 10 * cofic_razmera));
			bl_for_draw.setTexture(&id_and_texture[nash_vector[index_box_in_inventory].item.id_blocka_inv]);
			window.draw(bl_for_draw);
			TEXT_BYSTRO text_count_item(v2f(60, 10), " ", 12 * cofic_razmera, Color::White, &window);
			if (nash_vector[index_box_in_inventory].item.count_item >= 10)
				text_count_item.POSITION = bl_for_draw.getPosition() + Vector2f(14 * cofic_razmera, 15 * cofic_razmera);
			else
				text_count_item.POSITION = bl_for_draw.getPosition() + Vector2f(21 * cofic_razmera, 15 * cofic_razmera);
			text_count_item.text = to_string(nash_vector[index_box_in_inventory].item.count_item);
			text_count_item.draw();
		}
	}
	void update(v2f mouse_cord, vector<Inventory_box>& nash_vector )
	{
		update_texure(mouse_cord);
		draw_hot_bar(nash_vector);
	}
	Texture vybron_texture, defolt_texture;
	RectangleShape Bar_box_rect;
	Vector2f gde_stoat;
	float cofic_razmera;
	int index_box_in_inventory;
};

class Inventory
{
public:
	Inventory(Texture& box_txure, int number_of_cells = 45)
	{
		float cofic_razmera = 2.0;
		float size_box_inv = 36 * cofic_razmera;

		this->number_of_cells = number_of_cells;
		InventoryRect.setSize(Vector2f(352*cofic_razmera , 332* cofic_razmera));
		InventoryRect.setPosition(v2f(cameraOffsetX + WIDTH / 2.f, cameraOffsetY + HEIGHT / 2.f) - InventoryRect.getSize() / 2.f);
		for (int i = 0; i < 27;i++)
		{
			FloatRect rectpos(Vector2f((i % 9) * size_box_inv, (i / 9) * size_box_inv)+Vector2f(14* cofic_razmera, 166* cofic_razmera), Vector2f(size_box_inv, size_box_inv));
			Inventar_vector.push_back(Inventory_box(rectpos, box_txure,Tipes_item::DEFOLT));
		}
		for (int i = 0; i < 9; i++)
		{
			int smes_x;
			if (i > 0)
				smes_x = 2*cofic_razmera;
			else
				smes_x = 0;
			int cofic_razm = 1.4;
			FloatRect rectpos(Vector2f((i % 9) * size_box_inv, 0) + Vector2f(14 * cofic_razmera, 282 * cofic_razmera), Vector2f(size_box_inv, size_box_inv));
			Inventar_vector.push_back(Inventory_box(rectpos, box_txure, Tipes_item::DEFOLT));
			HotBar_vector.push_back(Hot_bar_box(INVENTORY::Hot_bar_box, INVENTORY::Hot_bar_box_vybron,
				Vector2f(44* cofic_razm, 44 * cofic_razm),
				v2f( WIDTH/2.f - ((382 * cofic_razm) / 2.f),  HEIGHT - 44 * cofic_razm) + v2f((i % 9) * 44 * cofic_razm - 2 * cofic_razm, 0),
				Inventar_vector.size()-1));
			
		}
		for (int i = 0;i < 4;i++)
		{
			FloatRect rectpos(Vector2f(0, (i % 5) * size_box_inv) + Vector2f(14 * cofic_razmera, 14 * cofic_razmera), Vector2f(size_box_inv, size_box_inv));
			Inventar_vector.push_back(Inventory_box(rectpos, box_txure, Tipes_item::ARMOR));
		}
		for (int i = 0;i < 4;i++)
		{
			FloatRect rectpos(Vector2f((i % 2) * size_box_inv, (i / 2) * size_box_inv) + Vector2f(174 * cofic_razmera, 50 * cofic_razmera), Vector2f(size_box_inv, size_box_inv));
			Inventar_vector.push_back(Inventory_box(rectpos, box_txure,Tipes_item::DEFOLT));
		}
		FloatRect rectpos(Vector2f(286 * cofic_razmera, 70 * cofic_razmera), Vector2f(size_box_inv, size_box_inv));
		Inventar_vector.push_back(Inventory_box(rectpos, box_txure, Tipes_item::CRAFT_ITEM));
		
	}
	bool push_back_item(int id_blocka_to_inv)
	{
		Item_in_inventory item_inv(id_blocka_to_inv);
		int index_in_vector = 0;
		while (!false)
		{
			if (Inventar_vector[index_in_vector].tipe_item == Tipes_item::DEFOLT)
			{
				if (index_in_vector == number_of_cells)
				{
					return false;
				}
				if (Inventar_vector[index_in_vector].plus_item(item_inv))
				{
					return true;
				}
				else
					index_in_vector = index_in_vector + 1;
			}
			else return false;
		}
			
		
	}
	void draw_hot_bar()
	{
		for (auto& ht_br : HotBar_vector)
		{
			ht_br.update(Mouse::, Inventar_vector);
		}
	}
	void draw_Inventory()
	{
		window.draw(InventoryRect);
		for (int i = 0; i < Inventar_vector.size();i++)
		{
			Inventar_vector[i].draw_box(InventoryRect.getPosition());
		}


	}
	RectangleShape InventoryRect;
	int number_of_cells;
	vector<Inventory_box> Inventar_vector;
	vector<Hot_bar_box> HotBar_vector;
};


#endif