#pragma once

#include <random>

float r(int a, float b = 0) {
	return static_cast<float>(std::rand() % (a * 1000) + b * 1000) / 1000.0;
}