#ifndef Parameters_h
#define Parameters_h

#include "SFML/Graphics.hpp"
#include <vector>
#include "Class/v2f.h"
using namespace sf;
using namespace std;

namespace GAME
{

	
	const int SizeBlock = 64;
	const float M_PI = 3.141592653f;
	const int WIDTH = SizeBlock * 14;
	const int HEIGHT = SizeBlock * 10;
	const int HALF_WIDTH = WIDTH / 2.f;
	const int HALF_HEIGHT = HEIGHT / 2.f;

	std::vector<float> gradientMap(256);
	map<int, Texture> index_texture;
	map<int, Texture> index_texture_player;
	float smoothing_factor = 0.1f;
	int id_height_grand = 0;
	int id_height_space = -3;
	int LEN_CAST_LINE = 630;
	float Delta_time = 0;
	Font defolt_font;
	float Speed_camera = 0.8;
	int deep_cast_blocks = 4;
	int LIGHT_INTENSITY_CAMERA = 9;
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