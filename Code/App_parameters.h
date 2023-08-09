#ifndef Parameters_h
#define Parameters_h
#include "SFML/Graphics.hpp"
#include <vector>
#include "Class/v2f.h"
#include "Class/Enums_maps.h"
using namespace sf;
using namespace std;


namespace GAME
{
	std::vector<float> gradientMap(256);
	vector<v2f> vbr_vicinity = enums::mura_vicinity;
 	const int SizeBlock = 16;
	v2f bl_2d = v2f(GAME::SizeBlock, GAME::SizeBlock);
	const float M_PI = 3.141592653f;
	const int WIDTH = SizeBlock * 48;
	const int HEIGHT = SizeBlock * 27;
	const int HALF_WIDTH = WIDTH / 2.f;
	const int HALF_HEIGHT = HEIGHT / 2.f;
	const float max_Speed_camera = 2.5;
	View camera_mine(FloatRect(0, 0, WIDTH, HEIGHT));
	map<int, Texture> index_texture;
	float smoothing_factor = 0.1f;
	float Delta_time = 0;
	Font defolt_font;
	v2f vel_camera(0, 0);

}
namespace sf
{
	// функция для создания плавного перехода между двумя цветами
	Color lerp(Color start, Color end, float t)
	{
		t = std::max(0.f, std::min(1.f, t)); // ограничиваем t в диапазоне от 0 до 1
		float r = start.r + t * (end.r - start.r);
		float g = start.g + t * (end.g - start.g);
		float b = start.b + t * (end.b - start.b);
		float a = start.a + t * (end.a - start.a);
		return Color(static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b), static_cast<Uint8>(a));
	}
}
#endif