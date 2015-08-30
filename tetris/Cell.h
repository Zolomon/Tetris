#pragma once


class Cell
{
public:
	Cell() : type(0), isFilled(false) {}

	explicit Cell(int type) : type(type), isFilled(false)
	{

	}

	int type;
	bool isFilled;
};