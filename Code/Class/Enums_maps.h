#ifndef Enums_h
#define Enums_h
#include <map>
#include "SFML/Graphics.hpp"

enum button_press
{
	A, W, S, D
};
enum count_item { Defolt = 64, Nodefolt = 16, Armor_Tool = 1 };

struct Item_info {
	Item_info(int id_item, int Durability, int tipe_item, int maks_item_count)
	{
		this->id_item = id_item;
		this->Durability = Durability;
		this->tipe_item = tipe_item;
		this->maks_item_count = maks_item_count;
	}
	int id_item;
	int Durability;
	int tipe_item;
	int maks_item_count;
};

enum Block_id
{
	BEDROCK, GRASS, DIRT, IRON, GOLD, DIAMOND, WOOD, COAL, STONE, SAND
};
enum Tipes_item{BLOCK, TOOL, ARMOR, FOOD};
enum Game_mode {
	SURVIVAL, CREATIVE, SPECTATOR, ADVENTURE
};
namespace MAPS
{
	std::map<int, sf::Texture> index_and_texture;
	std::map<int, Item_info> id_and_info = {
		{Block_id::BEDROCK, Item_info(Block_id::BEDROCK, -1, Tipes_item::BLOCK, count_item::Defolt)}, 
		{Block_id::GRASS, Item_info(Block_id::GRASS, 1, Tipes_item::BLOCK, count_item::Defolt)},
		{Block_id::DIRT, Item_info(Block_id::DIRT, 1, Tipes_item::BLOCK, count_item::Defolt)},
		{Block_id::IRON, Item_info(Block_id::IRON, 3, Tipes_item::BLOCK, count_item::Defolt)},
		{Block_id::GOLD, Item_info(Block_id::GOLD, 3, Tipes_item::BLOCK, count_item::Defolt)},
		{Block_id::DIAMOND, Item_info(Block_id::DIAMOND, 3, Tipes_item::BLOCK, count_item::Defolt)},
		{Block_id::WOOD, Item_info(Block_id::WOOD, 2, Tipes_item::BLOCK, count_item::Defolt)},
		{Block_id::COAL, Item_info(Block_id::COAL, 2, Tipes_item::BLOCK, count_item::Defolt)},
		{Block_id::STONE, Item_info(Block_id::STONE, 1, Tipes_item::BLOCK, count_item::Defolt)},
		{Block_id::SAND, Item_info(Block_id::SAND, 1, Tipes_item::BLOCK, count_item::Defolt)}
	};
}


#endif