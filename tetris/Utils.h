#pragma once

#include <random>

namespace Utils {

	inline float r(int a, float b = 0) {
		return static_cast<float>(std::rand() % (a * 1000) + b * 1000) / 1000.0;
	}

	inline int clamp(int v, int l, int h)
	{
		return v < l ? l : v > h ? h : v;
	}

}