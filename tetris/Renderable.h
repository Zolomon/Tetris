#pragma once
#include "Bitmap.h"

struct Renderable {
	explicit Renderable(Bitmap shape) : shape(shape) {}

	Bitmap shape;
};
