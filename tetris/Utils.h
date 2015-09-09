#pragma once

#include <random>
#include "PieceType.h"

class Utils {
public:
	
	static float r(int a, float b = 0) {
		return static_cast<float>(std::rand() % (a * 1000) + b * 1000) / 1000.0;
	}

	static int clamp(int v, int l, int h)
	{
		return v < l ? l : v > h ? h : v;
	}
	
	static int RandomInt(int min, int max)
	{
		std::mt19937 gen(rd());

		std::uniform_int_distribution<> dis(min, max);

		return dis(gen);
	}

	static PieceType RandomPieceType()
	{
		return pieces[RandomInt(0, 6)];
	}

private:
	static std::random_device rd;
	const static PieceType pieces[7];
};