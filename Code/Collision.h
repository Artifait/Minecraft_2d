#ifndef Collision_h
#define Collision_h


#include "SFML/Graphics.hpp"
#include "Class/TipoRectangleShape.h"
#include "Class/Rect.h"
#include <vector>
#include "Class/Block.h"
using namespace sf;
using namespace std;
#undef min
#undef max

using namespace std;

bool RayVsRect(const v2f& ray_origin, const v2f& ray_dir, const rect* target, v2f& contact_point, v2f& contact_normal, float& t_hit_near)
{
	contact_normal = v2f(0, 0);
	contact_point = v2f(0, 0);

	// Разделение кэша
	v2f invdir;
	invdir.x = 1.0f / ray_dir.x;
	invdir.y = 1.0f / ray_dir.y;

	// Вычислить пересечения с осями границ прямоугольника			
	v2f t_near = (v2f(target->body_rect.Positiontipo) - ray_origin) * invdir;
	v2f t_far = (v2f(target->body_rect.Positiontipo + target->body_rect.Sizetipo) - ray_origin) * invdir;

	if (std::isnan(t_far.y) || std::isnan(t_far.x)) return false;
	if (std::isnan(t_near.y) || std::isnan(t_near.x)) return false;

	// Сортировка расстояний
	if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
	if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

	// Ранний отказ		
	if (t_near.x > t_far.y || t_near.y > t_far.x) return false;

	// Ближайшее "время" будет первым контактом
	t_hit_near = std::max(t_near.x, t_near.y);

	// Самое дальнее "время" - контакт на противоположной стороне цели
	float t_hit_far = std::min(t_far.x, t_far.y);

	// Отклонить, если направление луча направлено в сторону от объекта

	if (t_hit_far < 0)
		return false;

	// Контактная точка столкновения из уравнения параметрической линии
	contact_point = ray_origin + ray_dir * t_hit_near;

	if (t_near.x > t_near.y)
		if (invdir.x < 0)
			contact_normal = v2f(1, 0);
		else
			contact_normal = v2f(-1, 0);
	else if (t_near.x < t_near.y)
		if (invdir.y < 0)
			contact_normal = v2f(0, 1);
		else
			contact_normal = v2f(0, -1);

	// Обратите внимание, если t_near == t_far, столкновение принципиально происходит по диагонали.
	// поэтому разрешать его бессмысленно. Возвращая CN={0,0}, несмотря на то, что столкновение
	// считается столкновением, разрешитель ничего не изменит.
	return true;
}
void max_to_max_min_to_min(v2f& top_left_v, v2f& niz_right_v)
{
	if (niz_right_v.x < top_left_v.x)
	{
		int x_top_left = top_left_v.x;
		top_left_v.x = niz_right_v.x;
		niz_right_v.x = x_top_left;
	}
	if (niz_right_v.y > top_left_v.y)
	{
		int y_top_left = top_left_v.y;
		top_left_v.y = niz_right_v.y;
		niz_right_v.y = y_top_left;
	}
}
void cout_v2f(v2f v2f);
void searching_min_max(v2f& start_vec, v2f& end_vec, vector<v2f> searching_place)//Для поиска границ квадрата с блоками для проверки колизий
{
	float min_x, max_x, min_y, max_y;
	min_x = max_x = searching_place[0].x;
	min_y = max_y = searching_place[0].y;
	for (auto vect : searching_place)
	{
		if (min_x > vect.x)
		{
			min_x = vect.x;
		}
		if (max_x < vect.x)
		{
			max_x = vect.x;
		}
		if (min_y > vect.y)
		{
			min_y = vect.y;
		}
		if (max_y < vect.y)
		{
			max_y = vect.y;
		}
	}
	start_vec = v2f(min_x, max_y);
	end_vec = v2f(max_x, min_y);

}

bool checkIntersection(sf::FloatRect rect1, sf::FloatRect rect2) {
	return (rect1.left < rect2.left + rect2.width) && (rect2.left < rect1.left + rect1.width) && (rect1.top < rect2.top + rect2.height) && (rect2.top < rect1.top + rect1.height);
}



bool PointVsRect(const v2f& p, const rect* r)
{
	return (p.x >= r->body_rect.Positiontipo.x &&
		p.y >= r->body_rect.Positiontipo.y &&
		p.x < r->body_rect.Positiontipo.x + r->body_rect.Sizetipo.x &&
		p.y < r->body_rect.Positiontipo.y + r->body_rect.Sizetipo.y);
}
bool PointVsRect(const v2f& p, const FloatRect r)
{
	return (p.x >= r.left &&
		p.y >= r.top &&
		p.x < r.left + r.width &&
		p.y < r.top + r.height);
}

bool RectVsRect(const rect* r1, const rect* r2)
{
	return checkIntersection(FloatRect(r1->body_rect.Positiontipo, r1->body_rect.Sizetipo),
		FloatRect(r2->body_rect.Positiontipo, r2->body_rect.Sizetipo));
}
bool RectVsRect(const FloatRect r1, const FloatRect r2)
{
	return checkIntersection(r1, r2);
}
bool DynamicRectVsRect(const rect* r_dynamic, const float fTimeStep, const rect& r_static,
	v2f& contact_point, v2f& contact_normal, float& contact_time)
{
	// Проверьте, действительно ли динамический прямоугольник движется - мы предполагаем,
	//что прямоугольники НЕ сталкиваются друг с другом для начала
	if (r_dynamic->vel.x == 0 && r_dynamic->vel.y == 0)
		return false;

	// Расширяем целевой прямоугольник по размерам исходного
	rect expanded_target;
	expanded_target.body_rect.setPosition(v2f(r_static.body_rect.Positiontipo - r_dynamic->body_rect.Sizetipo) / 2);
	expanded_target.body_rect.setSize(r_static.body_rect.Sizetipo + r_dynamic->body_rect.Sizetipo);
	expanded_target.body_rect.setPosition(expanded_target.body_rect.getPosition() + r_static.body_rect.Positiontipo / 2.f);
	//window.draw(expanded_target.body_rect);
	if (RayVsRect(v2f(r_dynamic->body_rect.Positiontipo) + v2f(r_dynamic->body_rect.Sizetipo) / 2, r_dynamic->vel * fTimeStep, &expanded_target, contact_point, contact_normal, contact_time))
	{
		return (contact_time >= 0.0f && contact_time <= 1.0f);
	}

	else
		return false;
}


void conflict_resolution(vector<rect>& rect_for_testing, rect& DynamicRect, bool& on_graynd)
{
	v2f point_colis, ray_direct, normal_colis;
	float ti = 0;
	vector<pair<int, float>> z;
	int i = 0;
	// Work out collision point, add it to vector along with rect ID
	for (auto& bl : rect_for_testing)
	{
		if (DynamicRectVsRect(&DynamicRect, 1, bl, point_colis, normal_colis, ti))
		{
			z.push_back({ i , ti });
		}
		i = i + 1;
	}

	// Do the sort
	sort(z.begin(), z.end(),
		[](const std::pair<int, float>& a, const std::pair<int, float>& b)
		{return a.second < b.second;});

	// Теперь разрешите столкновение в правильном порядке 		
	for (auto& j : z)
	{

		if (DynamicRectVsRect(&DynamicRect, 1, rect_for_testing[j.first], point_colis, normal_colis, ti))
		{
			DynamicRect.vel += normal_colis * v2f(abs(DynamicRect.vel.x), abs(DynamicRect.vel.y)) * (1 - ti);
			if (normal_colis == v2f(0, -1)) { on_graynd = 1; }

		}
	}

	if (DynamicRect.vel.y != 0) { on_graynd = 0; }
	DynamicRect.move(DynamicRect.vel);
}





rect* mergeRects(vector<rect*>& rects) {
	// Находим самый левый rect
	float x_min = rects[0]->body_rect.getPosition().x;
	for (int i = 1; i < rects.size(); i++) {
		x_min = min(x_min, rects[i]->body_rect.getPosition().x);
	}

	// Находим самый верхний rect
	float y_min = rects[0]->body_rect.getPosition().y;
	for (int i = 1; i < rects.size(); i++) {
		y_min = min(y_min, rects[i]->body_rect.getPosition().y);
	}

	// Находим самый правый rect
	float x_max = rects[0]->body_rect.getPosition().x + rects[0]->body_rect.getSize().x;
	for (int i = 1; i < rects.size(); i++) {
		x_max = max(x_max, rects[i]->body_rect.getPosition().x + rects[i]->body_rect.getSize().x);
	}

	// Находим самый нижний rect
	float y_max = rects[0]->body_rect.getPosition().y + rects[0]->body_rect.getSize().y;
	for (int i = 1; i < rects.size(); i++) {
		y_max = max(y_max, rects[i]->body_rect.getPosition().y + rects[i]->body_rect.getSize().y);
	}

	// Создаем новый rect
	rect* merged_rect = new rect();
	merged_rect->init({ x_max - x_min, y_max - y_min }, { x_min, y_min });

	// Добавляем в новый rect все rect
	for (int i = 0; i < rects.size(); i++) {
		merged_rect->contact.push_back(rects[i]);
	}

	return merged_rect;
}


void mergeOverlappingRects(vector<rect>& rects) {//оно обьединяет блоки в big блоки для fast проверки на коллизии
	//vector<v2f> good_rect_id;
	map<v2f, rect> mapa_rects;
	for (auto& rect_now : rects)
	{
		mapa_rects[v2f(rect_now.body_rect.getPosition()) / Block::Size_block] = rect_now;
	}
	rects.clear();

	int GOOD_ITERATION = 0;
	while (mapa_rects.size() > GOOD_ITERATION)
	{
		v2f offset_searching(-1, -1);
		rect* r_now = &(*mapa_rects.begin()).second;
		v2f id_rect((*mapa_rects.begin()).first);
		bool smena_searcing = false;
		bool GOOD_SEARHING = true;
		while (GOOD_SEARHING) {
			if (mapa_rects.find(id_rect + offset_searching) != mapa_rects.end())
			{
				mapa_rects.erase(mapa_rects.find(id_rect + offset_searching));
				r_now->setsize(offset_searching * Block::Size_block + r_now->body_rect.getSize());
				offset_searching += offset_searching;
			}
			else if (!smena_searcing)
			{
				smena_searcing = true;
				offset_searching = offset_searching / offset_searching;
				offset_searching = v2f(-offset_searching.x, -offset_searching.y);
			}
			else
			{
				GOOD_SEARHING = false;
			}
		}
		GOOD_ITERATION++;
		rects.push_back((*mapa_rects.find(id_rect)).second);
		mapa_rects.erase(mapa_rects.find(id_rect));
	}
	for (auto block_rect : mapa_rects)
	{
		rects.push_back(block_rect.second);
	}
	/*
	// Удаляем элементы из rects, которых нет в mapa_rects
	rects.erase(remove_if(rects.begin(), rects.end(), [&](rect r)
	{
		for (auto& pair : mapa_rects) {
			if (pair.second == r) {
				return false;
			}
		}
		return true;
	}), rects.end());
	*/
}













#endif //Header
