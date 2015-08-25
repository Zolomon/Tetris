#pragma once
#include "glm/glm.hpp"
#include <string>

struct MenuItem
{
	MenuItem(const std::wstring& text) : text(text) {}

	std::wstring text;
};
