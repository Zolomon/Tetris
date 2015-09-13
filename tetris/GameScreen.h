#pragma once
#include "Game.h"
#include "Application.h"
#include <chrono>
#include "GameScreenType.h"
#include <map>

class Game;
class Application;

class GameScreen
{
public:
	GameScreen(std::shared_ptr<Game> game, std::shared_ptr<Application> app) : restart(false), game(game), app(app)
	{
		
	}

	virtual ~GameScreen()
	{
	}

	virtual void update(const double deltaTime) = 0;
	virtual void render(const double interpolation) = 0; 
	
	bool restart;
protected:
	std::shared_ptr<Game> game;
	std::shared_ptr<Application> app;
};




