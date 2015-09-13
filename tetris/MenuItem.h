#pragma once
#include "Game.h"

struct MenuItem
{
	MenuItem(const int index, const std::wstring& text, 
		const std::function<void(std::shared_ptr<Game>)> execute) 
		: text(text), index(index), execute(execute) {}

	std::wstring text;
	int index;
	std::function<void(std::shared_ptr<Game>)> execute;
};