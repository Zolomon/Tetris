#pragma once
#include <vector>
#include "Cell.h"
#include "Settings.h"

struct Board
{
	Board()
	{
		for (int y = 0; y < Settings::Game::Rows; y++)
		{
			for (int x = 0; x < Settings::Game::Columns; x++)
			{
				Cell test(0);
				cells.push_back(test);
			}
		}
	}
	std::vector<Cell> cells;
};