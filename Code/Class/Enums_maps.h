#ifndef Enums_h
#define Enums_h
#include <map>
#include "SFML/Graphics.hpp"
#include "v2f.h"
#include <vector>
#include <iostream>
using namespace std;

namespace enums
{
	enum button_press
	{
		A, W, S, D
	};


	enum vicinity
	{
		mura, von
	};

	enum type_block
	{
		Water, block
	};

	vector<v2f> mura_vicinity{ v2f(-1, 0), v2f(-1, 1), v2f(0, 1), v2f(1, 1), v2f(1, 0), v2f(1, -1), v2f(0, -1), v2f(-1, -1) };
	vector<v2f> von_vicinity{ v2f(-1, 0), v2f(1, 0), v2f(0, -1), v2f(0, 1) };
}

#endif