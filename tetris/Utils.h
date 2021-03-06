#pragma once

#include <assert.h>
#include <random>
#include "PieceType.h"
#include "Resource.h"

class Utils {
public:
	
	static int clamp(int v, int l, int h)
	{
		return v < l ? l : v > h ? h : v;
	}

	static double clampd(double v, double l, double h)
	{
		return v < l ? l : v > h ? h : v;
	}

	static int randomInt(int min, int max)
	{
		std::mt19937 gen(rd());

		std::uniform_int_distribution<> dis(min, max);

		return dis(gen);
	}

	static PieceType randomPieceType()
	{
		return pieces[randomInt(0, 6)];
	}

	static Resource getResourceForPieceType(int type)
	{
		switch (type)
		{
		case 0:
			return Resource::BlackBlock;
		case 1:
			return Resource::BlueBlock;
		case 2:
			return Resource::CyanBlock;
		case 3:
			return Resource::GreenBlock;
		case 4:
			return Resource::MagentaBlock;
		case 5:
			return Resource::RedBlock;
		case 6:
			return Resource::YellowBlock;
		case 7:
			return Resource::OrangeBlock;
		default: {
			assert(false);
			return Resource::GameMenuBackground;
		}
		}
	}

private:
	static std::random_device rd;
	const static PieceType pieces[7];
};