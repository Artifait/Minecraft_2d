
#ifndef World_h
#define World_h
#include "../App_parameters.h"
#include "../Collision.h"
#include "Chunk.h"
#include <iostream>
using namespace std;
using namespace sf;
class World_MineCraft
{
public:
	Chunk_mine& GIVE_PLAYER_CHUNK(v2f id_chunk);
	World_MineCraft(int seed_world = -1, int offset_z = 0);
	void GENERATE_chunk(v2f id_generate, int seed_gnrt)
	{
		if (!(Mine_World.count(id_generate) > 0))//проверка на существование чанка(если нету)
		{
			if (id_generate.y >= GAME::id_height_space) {
				Mine_World[id_generate] = generator.Сhunk_generation(id_generate, offset_z, seed_gnrt);
				if(id_generate.y <= GAME::id_height_grand)
				{
					generator.Genration_zone_ground(Mine_World, id_generate, seed_gnrt);
					generator.Create_caves(Mine_World[id_generate], seed_gnrt, offset_z, id_generate);
				}
			}
			else
			{
				std::map<v2f, Block> blocks_in_chunk;
				Mine_World[id_generate] = Chunk_mine(id_generate, blocks_in_chunk);
			}
			
			

			//cout << "Генерация чанка: " << id_generate.x << ", " << id_generate.y << ". Прошла успешна." << endl;
		}
	}
	void DRAW_CHUNK(RenderWindow& window);
	void DRAW_visible_chunks(RenderWindow& window);
	v2f defolt_spawn_point_world;
private:

	int offset_z;
	class Generator_mine_World
	{
	public:
		Generator_mine_World();
		float get_val_noise(float x_pos, float y_pos, FastNoiseLite& noise_gen)
		{
			float noiseValue = static_cast<float>(noise_gen.GetNoise(x_pos, y_pos)) + 0.5f;
			int index = static_cast<int>(std::round(noiseValue * 255));
			index = std::max(0, std::min(index, 255));
			float colorValue = GAME::gradientMap[index];
			return colorValue;
		}
		void Create_caves(Chunk_mine& chunk_for_create, int seed, int offset_z, v2f id_chunk)
		{
			for (int y = 0;y < 16;y++)
			{
				for (int x = 0; x < 16;x++)
				{
					v2f id_block_del(x + 16 * id_chunk.x, y + 16 * id_chunk.y);
					float total_gnrt_score = 0;
					total_gnrt_score = get_val_noise(id_block_del.x, id_block_del.y, caves_noise);
					if (total_gnrt_score <= 0.2)
					{
						auto it = chunk_for_create.blocks_in_chunk.find(id_block_del);
						if (it != chunk_for_create.blocks_in_chunk.end())
							chunk_for_create.blocks_in_chunk.erase(chunk_for_create.blocks_in_chunk.find(id_block_del));
					}
				}
			}
		}
		Chunk_mine Сhunk_generation(v2f id_chunk_generate, int offset_z, int seed_gnrt);
		void Genration_zone_ground(std::map<v2f, Chunk_mine>& Mine_World, v2f id_Chunk_generate, int seed_gnrt);
		FastNoiseLite mine_noise;
		FastNoiseLite caves_noise;
	};

	int seed_World;
	Generator_mine_World generator;
	std::map<v2f, Chunk_mine> Mine_World;

};
inline void World_MineCraft::DRAW_CHUNK(RenderWindow& window)
{
	DRAW_visible_chunks(window);
}
World_MineCraft::World_MineCraft(int seed_world, int offset_z)// удалили значение по умолчанию
{
	if (seed_world == -1)
		seed_world = rand() % 2147483646;
	this->seed_World = seed_world;
	this->offset_z = offset_z;
	
	generator.mine_noise.SetSeed(seed_World);
	generator.mine_noise.SetNoiseType(FastNoiseLite::NoiseType_ValueCubic);
	generator.mine_noise.SetFrequency(0.01f);

	generator.caves_noise.SetSeed(seed_World);
	generator.caves_noise.SetFrequency(0.09f);
	generator.caves_noise.SetFractalType(FastNoiseLite::FractalType_PingPong);
	generator.caves_noise.SetFractalGain(0.2);
	generator.caves_noise.SetNoiseType(FastNoiseLite::NoiseType_ValueCubic);
	defolt_spawn_point_world = v2f(0,  generator.get_val_noise(0, 0, generator.mine_noise) * 4 + 5);
}

Chunk_mine World_MineCraft::Generator_mine_World::Сhunk_generation(v2f id_chunk_generate, int offset_z, int seed_gnrt)
{
	srand(seed_gnrt);
	std::map<v2f, Block> blocks_in_chunk;
		for (int y = 0;y < 16;y++)
		{
			for (int x = 0; x < 16;x++)
			{
				v2f id_block_gnrt(x + 16 * id_chunk_generate.x, y + 16 * id_chunk_generate.y);
				float total_gnrt_score = 0;/*
				for (int d_y = -1; d_y < 2; d_y++)
				{
					for (int d_x = -1; d_x < 2; d_x++)
					{
						total_gnrt_score+=  get_val_noise(id_block_gnrt.x + d_x, id_block_gnrt.y + d_y, caves_noise);
					}
				}
				total_gnrt_score /= 9.f;
				*/
				total_gnrt_score = get_val_noise(id_block_gnrt.x, id_block_gnrt.y, caves_noise);
				if (total_gnrt_score > 0.2)
				{
					int val_gnrt_block_tipe = rand() % 1000;
					if(val_gnrt_block_tipe < 20)
						blocks_in_chunk[id_block_gnrt] = Coal_block(id_block_gnrt);
					else if(val_gnrt_block_tipe < 100)
						blocks_in_chunk[id_block_gnrt] = Stone_block(id_block_gnrt);
					else if(val_gnrt_block_tipe < 110)
						blocks_in_chunk[id_block_gnrt] = Gold_block(id_block_gnrt);
					else if (val_gnrt_block_tipe < 110)
						blocks_in_chunk[id_block_gnrt] = Gold_block(id_block_gnrt);
					else if (val_gnrt_block_tipe < 140)
						blocks_in_chunk[id_block_gnrt] = Iron_block(id_block_gnrt);
					else if (val_gnrt_block_tipe < 145)
						blocks_in_chunk[id_block_gnrt] = Diamond_block(id_block_gnrt);
					else
						blocks_in_chunk[id_block_gnrt] = Stone_block(id_block_gnrt);
				}
					
			}
		}
	


	return Chunk_mine(id_chunk_generate, blocks_in_chunk);
}
World_MineCraft::Generator_mine_World::Generator_mine_World()
{
}

inline void World_MineCraft::DRAW_visible_chunks(RenderWindow& window)
{
	v2f left_win = window.mapPixelToCoords(Vector2i(0,0));
	left_win.x = floor(left_win.x / (16.0 * Block::Size_block));
	left_win.y = floor(left_win.y / (16.0 * Block::Size_block));
	sf::Vector2f right_win = window.mapPixelToCoords(Vector2i(GAME::WIDTH, GAME::HEIGHT));
	right_win.x = floor(right_win.x / (16.0 * Block::Size_block));
	right_win.y = floor(right_win.y / (16.0 * Block::Size_block));
	FloatRect camera_vidno(window.mapPixelToCoords(Vector2i(0, 0)), Vector2f(GAME::WIDTH, GAME::HEIGHT));
	int total_draw_bl = 0;
	for (int y = left_win.y; y < right_win.y+1; y++) {
		for (int i = left_win.x;i < right_win.x+1; i++)
		{
			GENERATE_chunk(v2f(i, y), seed_World);
			Mine_World[v2f(i, y)].Draw_chunk(camera_vidno, offset_z, window);
			total_draw_bl += Mine_World[v2f(i, y)].get_count_block();
		}
	}
	
}


inline void World_MineCraft::Generator_mine_World::Genration_zone_ground(std::map<v2f, Chunk_mine>& Mine_World, v2f id_Chunk_generate, int seed_gnrt)
{
	srand(seed_gnrt);
	for (int x_chunk = id_Chunk_generate.x * 16; x_chunk < id_Chunk_generate.x * 16 + 16; x_chunk++)
	{
		int id_gnrt_block = (GAME::id_height_space - GAME::id_height_grand)* 16 * get_val_noise(x_chunk, 0, mine_noise);
		//cout << id_gnrt_block << endl;
		//cout << " id_gnrt = " << id_gnrt_block << endl;
		int height_grand = get_val_noise(x_chunk, 0, mine_noise)*4 + 4;
		for (int y_chunk = id_Chunk_generate.y * 16; y_chunk < id_Chunk_generate.y * 16+16; y_chunk++)
		{
			if (y_chunk == id_gnrt_block)
			{
				Mine_World[id_Chunk_generate].blocks_in_chunk[v2f(x_chunk, y_chunk)] = Grass_block(v2f(x_chunk, y_chunk));
			}
			if (y_chunk > id_gnrt_block && y_chunk < id_gnrt_block + height_grand)
			{
				Mine_World[id_Chunk_generate].blocks_in_chunk[v2f(x_chunk, y_chunk)] = Dirt_block(v2f(x_chunk, y_chunk));
			}
			if (y_chunk < id_gnrt_block)
			{
				if (Mine_World[id_Chunk_generate].blocks_in_chunk.count(v2f(x_chunk, y_chunk)) > 0)//проверка на существование блока
				{
					if(Mine_World[id_Chunk_generate].blocks_in_chunk.erase(v2f(x_chunk, y_chunk)))
					{	//cout << " kill: " << x_chunk << " и " << y_chunk << endl;
					}
				}
			}

		}
	}
	

}



inline Chunk_mine& World_MineCraft::GIVE_PLAYER_CHUNK(v2f id_chunk)
{
	GENERATE_chunk(id_chunk, seed_World);
	return Mine_World[id_chunk];
}


#endif