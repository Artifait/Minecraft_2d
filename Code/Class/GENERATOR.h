#pragma once
#include "../Biblea/FastNoise.h"
#include <iostream>
#include "../App_parameters.h"
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
	
	FastNoiseLite caves_noise;
};