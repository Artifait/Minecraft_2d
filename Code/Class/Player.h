#pragma once
#include "SFML/Graphics.hpp"
#include "World.h"
#include "../App_parameters.h"
#include "Rect.h"
#include <vector>
#include "../Collision.h"
using namespace std;
using namespace sf;

class Player
{
public:
	Player(int GAME_MOD, World_MineCraft* world);
	
	void update_world_player(World_MineCraft* world_new)
	{
		player_world = world_new;
	}
	void draw(RenderWindow& window)
	{
		window.draw(PLayre_body.for_draw);
	}
	void update_state(v2f world_pos_mouse, RenderWindow& window)
	{

		if (Mouse::isButtonPressed(Mouse::Left)) //&& !mouse_clicked)
		{

			// Код, который должен выполняться при клике мыши
			VertexArray line_poisk(Lines, 2);
			line_poisk[0].position = Give_center_player();
			line_poisk[1].position = world_pos_mouse;
			line_poisk[0].color = Color::Red;
			line_poisk[1].color = Color::Red;
			window.draw(line_poisk);
			v2f end_block_id;
			Block* bl_found = poisk_block(line_poisk, *player_world, end_block_id, window);
			if (bl_found != nullptr)
			{
				float chunk_id_cast_x = floor(bl_found->Give_pos_id().x / 16.f);
				float chunk_id_cast_y = floor(bl_found->Give_pos_id().y / 16.f);
				player_world->GIVE_PLAYER_CHUNK(v2f(chunk_id_cast_x, chunk_id_cast_y)).Break_block_in_chunk(bl_found->Give_pos_id());
			}
		}

		if (Mouse::isButtonPressed(Mouse::Right) && !mouse_clicked)
		{
			mouse_clicked = true;

			v2f end_block_id;
			VertexArray line_poisk(Lines, 2);
			line_poisk[0].position = Give_center_player();
			line_poisk[1].position = world_pos_mouse;
			line_poisk[0].color = Color::Red;
			line_poisk[1].color = Color::Red;
			Block* bl_found = poisk_block(line_poisk, *player_world, end_block_id, window);

			if(bl_found == nullptr)
			{
				if(check_CAN_put(*player_world, end_block_id))
				{
					float chunk_id_cast_x = floor(end_block_id.x / 16.f);
					float chunk_id_cast_y = floor(end_block_id.y / 16.f);
					player_world->GIVE_PLAYER_CHUNK(v2f(chunk_id_cast_x, chunk_id_cast_y)).put_block(end_block_id, Block_id::WOOD);
				}
			}
			else
			{
				v2f cnt_point, normal_point;
				rect rect_ch = (*bl_found).get_collider();
				float t;
				if (RayVsRect(v2f(line_poisk[0].position), v2f(line_poisk[1].position) - line_poisk[0].position, &rect_ch, cnt_point, normal_point, t))
				{
					if (check_CAN_put(*player_world, end_block_id + normal_point))
					{
						float chunk_id_cast_x = floor((end_block_id.x + normal_point.x) / 16.f);
						float chunk_id_cast_y = floor((end_block_id.y + normal_point.y) / 16.f);
						player_world->GIVE_PLAYER_CHUNK(v2f(chunk_id_cast_x, chunk_id_cast_y)).put_block(end_block_id + normal_point, Block_id::WOOD);
					}
				}
			}

		}
		else if (!Mouse::isButtonPressed(Mouse::Right))
		{
			mouse_clicked = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::A)) pressA = true; else pressA = false;
		if (Keyboard::isKeyPressed(Keyboard::D))  pressD = true; else  pressD = false;	
		if (Keyboard::isKeyPressed(Keyboard::W)) pressW = true; else pressW = false;
		if (Keyboard::isKeyPressed(Keyboard::S))  pressS = true; else  pressS = false;

	}
	void Collision_update(float Delta_t, World_MineCraft& world_mine, RenderWindow& window, View& camera_mine)
	{
		update_state(window.mapPixelToCoords(Mouse::getPosition(window)), window);
		update_vel(Delta_t);
		vector<v2f> testing_vect;
		v2f block_start;
		v2f block_end;
		rect PLayer_future;
		vector<rect> blocki_colis;

		PLayer_future.init(PLayre_body.body_rect.getSize(), PLayre_body.body_rect.getPosition());
		PLayer_future.move(PLayre_body.vel);//раздуваем данные для дальнейшего нахождения самой верхней левой и самой нижней правой границы блоков с которыми может колизиться игрок
		testing_vect.push_back(v2f(floor(PLayer_future.body_rect.getGlobalBounds().left / Block::Size_block), floor(PLayer_future.body_rect.getGlobalBounds().top / Block::Size_block)));
		testing_vect.push_back(v2f(floor((PLayer_future.body_rect.getGlobalBounds().left + PLayer_future.body_rect.getGlobalBounds().width) / Block::Size_block), floor((PLayer_future.body_rect.getGlobalBounds().top + PLayer_future.body_rect.getGlobalBounds().height) / Block::Size_block)));
		testing_vect.push_back(v2f(floor(PLayre_body.body_rect.getGlobalBounds().left / Block::Size_block), floor(PLayre_body.body_rect.getGlobalBounds().top / Block::Size_block)));
		testing_vect.push_back(v2f(floor((PLayre_body.body_rect.getGlobalBounds().left + PLayre_body.body_rect.getGlobalBounds().width) / Block::Size_block), floor((PLayre_body.body_rect.getGlobalBounds().top + PLayre_body.body_rect.getGlobalBounds().height) / Block::Size_block)));


		searching_min_max(block_start, block_end, testing_vect);
		for (int y_block = block_end.y - Zapac_collison.y; y_block - Zapac_collison.y <= block_start.y; y_block++)
		{
			for (int x_block = block_start.x - Zapac_collison.x; x_block - Zapac_collison.x <= block_end.x; x_block++)
			{
				float chunk_id_cast_x = floor(x_block / 16.f);
				float chunk_id_cast_y = floor(y_block / 16.f);
				rect collider_bl = world_mine.GIVE_PLAYER_CHUNK(v2f(chunk_id_cast_x, chunk_id_cast_y)).Give_block_collider(v2f(x_block, y_block));
				if(collider_bl.body_rect.Sizetipo.x > 0)
					blocki_colis.push_back(collider_bl);
			}
		}
		conflict_resolution(blocki_colis, PLayre_body, on_graynd);

		camera_mine.setCenter(v2f(PLayre_body.body_rect.getSize()) / 2 + offset_camera +
			GAME::vel_camera + PLayre_body.body_rect.getPosition());
		window.setView(camera_mine);
	}
	v2f Give_center_player()
	{
		return v2f(PLayre_body.body_rect.getSize()) / 2 + PLayre_body.body_rect.getPosition() + v2f(0, -Block::Size_block*0.5);
	}
	v2f spawn_point_now;
private:
	bool mouse_clicked;
	v2f Zapac_collison;
	v2f cameraMotionCoefficients;
	v2f offset_camera;
	World_MineCraft* player_world;
	float maks_speed_x;
	float maks_speed_y;
	rect PLayre_body;
	int gameplay_mode;
	float speed_player;
	bool pressA, pressS, pressD, pressW, pressSpace;
	bool on_graynd;
	void update_vel(float Delta_time)
	{

		if (pressD)
		{
			PLayre_body.vel.x += (maks_speed_x - PLayre_body.vel.x) * GAME::smoothing_factor;
			GAME::vel_camera.x += (maks_speed_x - GAME::vel_camera.x) * GAME::smoothing_factor;
		}
		if (pressA)
		{
			PLayre_body.vel.x += (-maks_speed_x - PLayre_body.vel.x) * GAME::smoothing_factor;
			GAME::vel_camera.x += (-maks_speed_x - GAME::vel_camera.x) * GAME::smoothing_factor;
		}
		if (!pressA && !pressD)
		{
			PLayre_body.vel.x += (0 - PLayre_body.vel.x) * GAME::smoothing_factor;
			GAME::vel_camera.x += (0 - GAME::vel_camera.x) * GAME::smoothing_factor;
		}
		if (gameplay_mode == Game_mode::CREATIVE)
		{
			if (pressS)
			{
				PLayre_body.vel.y = speed_player;
			}
			if (pressW)
			{
				PLayre_body.vel.y = -speed_player;
			}
			if (!pressW && !pressS)
				PLayre_body.vel.y = 0;
		}
		if (gameplay_mode == Game_mode::SURVIVAL)
		{
			if (pressW && on_graynd) PLayre_body.vel.y = -speed_player * 3; else PLayre_body.vel.y += speed_player * 0.23;
		}

		PLayre_body.vel.y = min(max(PLayre_body.vel.y, -maks_speed_y), maks_speed_y);
		//PLayre_body.vel.x = min(max(PLayre_body.vel.x, -maks_speed_x), maks_speed_x);

	}
};

Player::Player(int GAME_MOD, World_MineCraft* world)
{
	PLayre_body.init(v2f(Block::Size_block * 0.75f, Block::Size_block * 1.75f), (world->defolt_spawn_point_world + v2f(0, -43)) * Block::Size_block);
	speed_player = Block::Size_block * 0.15;
	gameplay_mode = GAME_MOD;
	maks_speed_x = speed_player * 1.5f;
	maks_speed_y = speed_player * 12;
	Zapac_collison = v2f(0, 0);
	player_world = world;
	offset_camera = v2f(0, 0);
	cameraMotionCoefficients = v2f(1, 0);
	mouse_clicked = false;
}